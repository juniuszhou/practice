#ifndef _PUBLIC_ANN_ANNLIB_H
#define _PUBLIC_ANN_ANNLIB_H
/*
 * public/ann/annlib.h
 * 2004-05-11 by ShanLanshan
 */

namespace ann {

	class AnnLib {
		bool m_inited;
	public:
		AnnLib();
		~AnnLib();
		bool init();
		void finalize();
	};

} // namespace ann

#endif /* _PUBLIC_ANN_ANNLIB_H */
