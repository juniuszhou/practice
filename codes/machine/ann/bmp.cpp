/*
 * public/bmp.c
 * 2004-01-13 by ShanLanshan
 */
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <public/bmp.h>


static int align(int n, int a);

namespace pub {

///////////////////////////////////////////////////////////////////////
//	class BmpFileHeader
///////////////////////////////////////////////////////////////////////
const char *BmpFileHeader::M_BMPFILE_FLAG = "BM";
BmpFileHeader::BmpFileHeader()
{
	memcpy(m_flag, M_BMPFILE_FLAG, M_BMPFILE_FLAG_LEN);
	m_size = 0;
	m_reserved = 0;
	m_off = 0;
}

BmpFileHeader::~BmpFileHeader() {}

bool BmpFileHeader::check_valid()
{
	if (memcmp(m_flag, M_BMPFILE_FLAG, M_BMPFILE_FLAG_LEN) != 0)
		return false;

	if (m_reserved != 0)
		return false;

	return true;
}

///////////////////////////////////////////////////////////////////////
//	class BmpInfoHeader
///////////////////////////////////////////////////////////////////////
BmpInfoHeader::BmpInfoHeader(int width, int height, short bitcount)
{
	m_size = sizeof(*this);
	m_planes = 1;
	m_compression = 0;
	m_perlspermeterx = 0x0ec4;
	m_perlspermetery = 0x0ec4;
	m_color_used = 0;
	m_color_important = 0;
	set_info(width, height, bitcount);
}

BmpInfoHeader::~BmpInfoHeader(){}

bool BmpInfoHeader::check_valid()
{
	if (m_size != sizeof(*this))
		return false;

	if (m_compression != 0)
		return false;

	if (m_bitcount != 1 && m_bitcount != 24)
		return false;

	return true;
}

void BmpInfoHeader::set_info(int width, int height, short bitcount)
{
	m_width = width;
	m_height = height;
	m_bitcount = bitcount;
	m_imagesize = height * get_line_bytes();
}

int BmpInfoHeader::get_line_bytes()
{
	int line_bytes;
	line_bytes = m_width * m_bitcount;
	line_bytes = align(line_bytes, 32);
	line_bytes /= 8;

	return line_bytes;
}

///////////////////////////////////////////////////////////////////////
//	class BmpPaletteSlot
///////////////////////////////////////////////////////////////////////
BmpPaletteSlot::BmpPaletteSlot(unsigned char r, unsigned char g, unsigned char b)
{
	set_rgb(r, g, b);
}
BmpPaletteSlot::~BmpPaletteSlot(){}
void BmpPaletteSlot::set_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	m_red = r;
	m_green = g;
	m_blue = b;
	m_reserved = 0;
}

///////////////////////////////////////////////////////////////////////
//	class BmpPalette
///////////////////////////////////////////////////////////////////////
BmpPalette::BmpPalette()
{
	m_slots = 0;
	m_palette_slot = NULL;
}

BmpPalette::~BmpPalette()
{
	clear();
}

void BmpPalette::clear()
{
	if (m_palette_slot == NULL)
		return;

	delete[] m_palette_slot;
	m_palette_slot = NULL;
}

void BmpPalette::set_bit(int bit, const unsigned char *data /* = NULL */)
{
	clear();

	if (bit >= 24) {
		m_slots = 0;
		return;
	}

	m_slots = 1 << bit;
	m_palette_slot = new BmpPaletteSlot[m_slots];

	if (bit == 1) {
		if (data == NULL) {
			m_palette_slot[0].set_rgb(0, 0, 0);
			m_palette_slot[1].set_rgb(0xff, 0xff, 0xff);
		}
	}

	if (data != NULL && bit < 24)
		memcpy(m_palette_slot, data, sizeof(BmpPaletteSlot) * m_slots);
}

unsigned char *BmpPalette::get_data()
{
	return reinterpret_cast<unsigned char*> (m_palette_slot);
}

unsigned int BmpPalette::get_data_len()
{
	return m_slots * sizeof(BmpPaletteSlot);
}

///////////////////////////////////////////////////////////////////////
//	class Bitmap
///////////////////////////////////////////////////////////////////////
Bitmap::Bitmap() 
{
	m_data = NULL;
}

Bitmap::~Bitmap()
{
	if (m_data == NULL)
		return;

	delete[] m_data;
	m_data = NULL;
}

bool Bitmap::create(int w, int h, short bit)
{
	m_infoheader.set_info(w, h, bit);
	m_line_bytes = m_infoheader.get_line_bytes();

	m_palette.set_bit(bit);

	m_fileheader.m_off = sizeof(m_fileheader) + sizeof(m_infoheader) + m_palette.get_data_len();
	m_fileheader.m_size = m_fileheader.m_off + m_infoheader.m_imagesize;

	m_data = new char[m_infoheader.m_imagesize];
	if (m_data == NULL)
		return false;

	return true;
}

bool Bitmap::load_from_file(const char *filename)
{
	FILE *fp;
	size_t reads;
	bool ret = false;

	fp = fopen(filename, "rb");
	if (fp == NULL)
		return false;

	/* 读取位图文件头部 */
	reads = fread(&m_fileheader, sizeof(m_fileheader), 1, fp);
	if (reads != 1) {
		goto lbl_ret;
	}
	if (!m_fileheader.check_valid()) {
		goto lbl_ret;
	}

	/* 读取位图文件信息部 */
	reads = fread(&m_infoheader, sizeof(m_infoheader), 1, fp);
	if (reads != 1) {
		goto lbl_ret;
	}
	if (!m_infoheader.check_valid()) {
		goto lbl_ret;
	}

	/* 读取调色板 */
	if (m_infoheader.m_bitcount < 24) {
		unsigned char buf[1024];
		int len;
		len = sizeof(BmpPaletteSlot) * (1 << m_infoheader.m_bitcount);
		if (len > sizeof(buf))
			goto lbl_ret;
		reads = fread(buf, 1, sizeof(buf), fp);
		if (reads != sizeof(buf))
			goto lbl_ret;
		m_palette.set_bit(m_infoheader.m_bitcount, buf);	
	}

	/* 读取图形数据 */
	m_data = new char[m_infoheader.m_imagesize];
	if (m_data == NULL)
		goto lbl_ret;
	reads = fread(m_data, 1, m_infoheader.m_imagesize, fp);
	if (reads != m_infoheader.m_imagesize)
		goto lbl_ret;

	/* 成功！ */
	m_line_bytes = m_infoheader.get_line_bytes();
	ret = true;

lbl_ret:
	fclose(fp);
	return ret;
}

bool Bitmap::save_to_file(const char *filename)
{
	FILE *fp;
	bool ret = false;

	fp = fopen(filename, "wb");
	if (fp == NULL)
		return false;

	/* 写位图文件头部 */
	if (!m_fileheader.check_valid()) {
		goto lbl_ret;
	}
	if (fwrite(&m_fileheader, sizeof(m_fileheader), 1, fp) != 1) {
		goto lbl_ret;
	}

	/* 写取位图文件信息部 */
	if (!m_infoheader.check_valid()) {
		goto lbl_ret;
	}
	if (fwrite(&m_infoheader, sizeof(m_infoheader), 1, fp) != 1) {
		goto lbl_ret;
	}

	/* 写调色板 */
	if (m_infoheader.m_bitcount < 24) {
		if (fwrite(m_palette.get_data(), 1, m_palette.get_data_len(), fp)
		!= m_palette.get_data_len())
			goto lbl_ret;
	}

	/* 写取图形数据 */
	if (m_data == NULL)
		goto lbl_ret;
	if (fwrite(m_data, 1, m_infoheader.m_imagesize, fp) != m_infoheader.m_imagesize)
		goto lbl_ret;

	/* 成功！ */
	ret = true;

lbl_ret:
	fclose(fp);
	return ret;
}

unsigned long Bitmap::get_pixel(int x, int y, int ci)
{
	unsigned long c, d[3];
	c = get_pixel(x, y);

	if (get_bitcount() == 1)
		return c;


	assert(ci > 0 && ci < 4);

	if (ci == 3) {
		return sqrt(static_cast<double>(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]));
	}
	get_rgb(c, d, d + 1, d + 2);

	return d[ci];
}

unsigned long Bitmap::get_pixel(int x, int y)
{
	int bytex, bitx;
	unsigned long ret = 0;
	int bc, off;

	assert(x >= 0);
	assert(y >= 0);
	assert(x < get_width());
	assert(y < get_height());

	bc = get_bitcount();
	bytex = bc * x;
	bitx = (7 - (bytex % 8));
	bytex /= 8;

	off = m_line_bytes * y + bytex;

	if (bc == 24) {
		memcpy(&ret, m_data + off, 3);
	} else if (bc == 1) {
		ret = m_data[off];
		ret >>= bitx;
		ret &= 0x00000001;
	}

	return ret;
}

void Bitmap::set_pixel(int x, int y, unsigned long c)
{
	int bytex, bitx;
	int bc, off;

	assert(x >= 0);
	assert(y >= 0);
	assert(x < get_width());
	assert(y < get_height());

	bc = get_bitcount();
	bytex = bc * x;
	bitx = (7 - (bytex % 8));
	bytex /= 8;

	off = m_line_bytes * y + bytex;

	if (bc == 24) {
		memcpy(m_data + off, &c, 3);
	} else if (bc == 1) {
		m_data[off] &= ~(1<<bitx);
		m_data[off] |= (c<<bitx);
	}
}

	extern void get_rgb(unsigned long c, unsigned long *r, unsigned long *g, unsigned long *b)
	{
		const unsigned char *p;

		p = reinterpret_cast<const unsigned char*> (&c);

		if (b != NULL)
			*b = p[2];
		if (g != NULL)
			*g = p[1];
		if (r != NULL)
			*r = p[0];
	}

	extern unsigned long gen_rgb(unsigned long r, unsigned long g, unsigned long b)
	{
		unsigned long c;
		unsigned char *p;

		p = reinterpret_cast<unsigned char*> (&c);
		p[0] = r;
		p[1] = g;
		p[2] = b;
		p[3] = 0;

		return c;
	}

} // namespace pub

static int align(int n, int a)
{
	if (n % a) {
		n -= n % a;
		n += a;
	}

	return n;
}
