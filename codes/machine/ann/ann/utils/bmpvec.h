#ifndef _PUBLIC_ANN_UTILS_BMPVEC_H
#define _PUBLIC_ANN_UTILS_BMPVEC_H
/*
 * public/ann/utils/bmpvec.h
 * 2004-05-17 by ShanLanshan
 *
 * 位图向量, 从位图中提取可供网络训练的向量
 */

#include "public/bmp.h"
#include "public/ann/interface.h"

namespace ann {

	class BmpVec {
	private:
		AnnVector	m_vector;
		ann_uint32	m_flag;
	public:
		static const ann_uint32 BMPVEC_FLAG_BW = 0x00000001;	// 当作黑白图片
		static const ann_uint32 BMPVEC_FLAG_ABS = 0x00000002;	// 计算相邻象素的相对值
	public:
		BmpVec();
		BmpVec(ann_int w, ann_int h, ann_int bitcount, ann_uint32 flag);
		~BmpVec();
		bool is_bw() {return m_flag & BMPVEC_FLAG_BW;};
		bool is_abs() {return m_flag & BMPVEC_FLAG_ABS;};
		bool set_type(ann_int w, ann_int h, ann_int bitcount, ann_uint32 flag);
		bool set_type(Bitmap *bmp, ann_uint32 flag);
		IAnnVector *abstract_vector(Bitmap *bmp);
		IAnnVector *abstract_vector(Bitmap *bmp, ann_uint32 flag);
		IAnnVector *abstract_vector(const char *file);
		IAnnVector *abstract_vector(const char *file, ann_uint32 flag);
	};

} // namespace ann

#endif /* !_PUBLIC_ANN_BMPVEC_H */
