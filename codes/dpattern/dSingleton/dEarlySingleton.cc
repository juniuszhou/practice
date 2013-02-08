#include <iostream>
class single
{
public:
    static single* instance();
protected:
    single();
private:
    static single* onlyInstance;
};

single* single::onlyInstance = new single();
single::single()
{
}

single* single::instance()
{
	return onlyInstance;
}

int main()
{
	single * aSingle = single::instance();
  return 1;
}

