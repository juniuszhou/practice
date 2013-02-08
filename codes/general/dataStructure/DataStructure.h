#ifndef INTERFACE_H
#define INTERFACE_H

#include <vector>
using namespace std;

class myList
{
	public:
		myList();
		myList(const myList& oList);
		myList operator = (const myList& oList);
	       bool operator == (const myList& firList);
	//private:
		int length;
			
};


#endif
