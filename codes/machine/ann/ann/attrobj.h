#ifndef _PUBLIC_ANN_ATTROBJ_H
#define _PUBLIC_ANN_ATTROBJ_H
/*
 * public/ann/attrobj.h
 * 2004-02-16 by ShanLanshan
 */
#include "public/ann/anndef.h"
namespace ann {

class LifeObj;
class PositionObj;
class GridObj;

class LifeObj {
protected:
	ann_float	m_life;
public:
	LifeObj();
};

class GridObj {
protected:
	ann_int m_grid_flag;
public:
	GridObj();
};

class PositionObj {
protected:
	ann_int x, y, z;
public:
	PositionObj();
};

class SharedObj {
private:
	ann_int m_use_count;
public:
	SharedObj();
	ann_int addref();
	ann_int release();
};

/*
class IDObj {
public:
	IDObj();
};
*/

} //namespace ann

#endif /* !_PUBLIC_ANN_ATTROBJ_H */
