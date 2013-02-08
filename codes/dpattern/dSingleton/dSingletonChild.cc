#include <iostream>
class single
{
public:
    static single* instance();
protected:
    //must be protected for inheritance
    single();
private:	
  static single* onlyInstance;
};

single* single::onlyInstance = NULL;
single::single()
{
}
single* single::instance()
{
	if (onlyInstance == NULL)
		{
			onlyInstance = new single();
		}
		return onlyInstance;
}

class singleChild:public single
{
public:
    static singleChild* instance();
protected:
    singleChild();
private:
    static singleChild* onlyChildInstance;
};

singleChild* singleChild::onlyChildInstance = NULL;
singleChild::singleChild()
{
}

singleChild* singleChild::instance()
{
	if (onlyChildInstance == NULL)
		{
			onlyChildInstance = new singleChild();
		}
		return onlyChildInstance;
}

int main()
{
	single * aSingle = single::instance();
	singleChild * aSingleChild = singleChild::instance();
  return 1;
}

