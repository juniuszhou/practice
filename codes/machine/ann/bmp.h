#ifndef _PUBLIC_BMP_H
#define _PUBLIC_BMP_H
/*
 * public/bmp.h
 * 2004-01-12 by ShanLanshan
 */

#ifdef __cplusplus
	extern "C" {
#endif

namespace pub {

#pragma pack(1)


// ��ɫγ�ȶ���
#define COLOR_DIVISION_RED		0
#define COLOR_DIVISION_GREEN	1
#define COLOR_DIVISION_BLUE		2

// ����bmp�ļ�ͷ�ṹ
class BmpFileHeader {
public:
	static const char *M_BMPFILE_FLAG;
	static const int M_BMPFILE_FLAG_LEN = 2;
	char m_flag[M_BMPFILE_FLAG_LEN];// �ļ����ͣ�����Ϊ"BM"
	unsigned long m_size;			// �����ļ��Ĵ�С 
	unsigned long m_reserved;		// ����������Ϊ�� 
	unsigned long m_off;			// �Ӹýṹ��ͼ���ײ���ƫ����
public:
	bool check_valid();
	BmpFileHeader();
	~BmpFileHeader();
};

class BmpInfoHeader {
public:
	unsigned long m_size;			// ���ṹ�ֽ���	
	long m_width;					// λͼ���		
	long m_height;					// λͼ�߶�
	short m_planes;					// Ŀ���豸��λ����
	short m_bitcount;				// ÿ�����ص�λ��
	unsigned long m_compression;	// ѹ�����ͣ�����Ϊ��
	unsigned long m_imagesize;		// ָ��ͼ��Ĵ�С
	long m_perlspermeterx;			// ˮƽ�ֱ���
	long m_perlspermetery;			// ��ֱ�ֱ���
	unsigned long m_color_used;		// ʹ�õ���ɫ����	
	unsigned long m_color_important;// ָ����λͼ����ʾ����ҪӰ�����ɫ������
									// �����ֵΪ 0����������ɫ������Ҫ
public:
	BmpInfoHeader(int width = 64, int height = 64, short bitcout = 8);
	~BmpInfoHeader();
	bool check_valid();
	void set_info(int width, int height, short bitcount);
	int get_line_bytes();
};

class BmpPaletteSlot {
public:
	unsigned char m_red;
	unsigned char m_green;
	unsigned char m_blue;
	unsigned char m_reserved;
public:
	BmpPaletteSlot(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0);
	~BmpPaletteSlot();
	void set_rgb(unsigned char r, unsigned char g, unsigned char b);
};

class BmpPalette {
public:
	BmpPaletteSlot *m_palette_slot;
	int m_slots;
public:
	void set_bit(int bit, const unsigned char *data = NULL);
	unsigned int get_data_len();
	unsigned char *get_data();
	void clear();
	BmpPalette();
	~BmpPalette();
};

class Bitmap {
public:
	BmpFileHeader m_fileheader;
	BmpInfoHeader m_infoheader;
	BmpPalette m_palette;
	char *m_data;
	int m_line_bytes;
	long & get_width() {return m_infoheader.m_width;};
	long & get_height() {return m_infoheader.m_height;};
	short & get_bitcount() {return m_infoheader.m_bitcount;};
	int get_color_division() {return get_bitcount() == 1 ? 1 : 3;};
	int get_division_len(int division) {return get_bitcount() == 1 ? 1 : 256;};
public:
	Bitmap();
	~Bitmap();
	bool in_range(int x, int y) {
		return (x >= 0 && y >= 0 && x < get_width() && y < get_height());
	};

	bool create(int w, int h, short bit);
	bool load_from_file(const char *filename);
	bool save_to_file(const char *filename);
	unsigned long get_pixel(int x, int y);
	unsigned long get_pixel(int x, int y, int ci);	//ci: color index
	void set_pixel(int x, int y, unsigned long c);
	// ��˹��
	// �ڰ׻�
	// �������� �ݶ���ȡ
	// ��ɫ
	// ���ҶԳ�
	// ���¶Գ�
	// �����Գ�
	// �����Գ�
	// ��λͼ
	// ��¡
};

extern void get_rgb(unsigned long c, unsigned long *r, unsigned long *g, unsigned long *b);
extern unsigned long gen_rgb(unsigned long r, unsigned long g, unsigned long b);

#pragma pack()

} // namespace pub

#ifdef __cplusplus
	}
#endif

#endif // !_PUBLIC_BMP_H
