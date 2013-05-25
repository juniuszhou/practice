/*
 * public/ann/utils/bmpvec.h
 * 2004-05-17 by ShanLanshan
 *
 * 位图向量, 从位图中提取可供网络训练的向量
 */

#include "bmpvec.h"

namespace ann {

	/////////////////////////////////////////////////////////////
	//	class BmpVec
	/////////////////////////////////////////////////////////////
	BmpVec::BmpVec(): m_flag(0) { }

	BmpVec::~BmpVec() { }

	BmpVec::BmpVec(ann_int w, ann_int h, ann_int bitcount, ann_uint32 flag)
	{
		set_type(w, h, bitcount, flag);
	}

	bool BmpVec::set_type(ann_int w, ann_int h, ann_int bitcount, ann_uint32 flag)
	{
		ann_int size;
		bool triple = bitcount == 24 && !is_bw();

		size = w * h;

		if (is_abs()) {
			size += w * (h - 1);
			size += h * (w - 1);
		}

		if (triple)
			size += size << 1;	// size *= 3;

		m_vector.set_size(size);

		return true;
	}

	bool BmpVec::set_type(Bitmap *bmp, ann_uint32 flag)
	{
		assert(bmp != NULL);
		return set_type(
			bmp->get_width(),
			bmp->get_height(),
			bmp->get_bitcount(),
			flag);
	}

	IAnnVector *BmpVec::abstract_vector(Bitmap *bmp)
	{
		return abstract_vector(bmp, m_flag);
	}

	IAnnVector *BmpVec::abstract_vector(Bitmap *bmp, ann_uint32 flag)
	{
		assert(bmp != NULL);

		if (!set_type(bmp, flag))
			return NULL;

		ann_int w, h, b, cd, from, to, divlen, cv, uv, lv;
		ann_float v;
		w = bmp->get_width();
		h = bmp->get_height();
		b = bmp->get_bitcount();
		cd = bmp->get_color_division();
		if (flag & BMPVEC_FLAG_BW) {
			from = 3;
			to = 3;
		} else {
			from = 0;
			to = cd - 1;
		}

		i = 0;
		for (ann_int d=form; d<=to; ++d) {
			divlen = bmp->get_division_len(d);
			for (ann_int x=0; x<w; ++x) {
				for (ann_int y=0; y<h; ++y) {
					/* 取得图片像素值 */
					cv = bmp->get_pixel(x, y, d);
					v = ann_float(cv) / divlen;
					m_vector.set_element(i++, v);

					/* 取得图片相邻像素相对值 */
					if ((flag & BMPVEC_FLAG_ABS) && x && y) {
						lv = bmp->get_pixel(x - 1, y, d);
						uv = bmp->get_pixel(x, y - 1, d);
						v = ann_float(lv -cv) / divlen
						m_vector.set_element(i++, v);
						v = ann_float(uv -cv) / divlen
						m_vector.set_element(i++, v);
					}
				}
			}
		}
	}

	IAnnVector *BmpVec::abstract_vector(const char *file)
	{
		return abstract_vector(file, m_flag);
	}

	IAnnVector *BmpVec::abstract_vector(const char *file, ann_uint32 flag)
	{
		Bitmap bmp;
		if (!bmp.load_from_file(file))
			return NULL;

		return abstract_vector(&bmp, flag);
	}

} // namespace ann
