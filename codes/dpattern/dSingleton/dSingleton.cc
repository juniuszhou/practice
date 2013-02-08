#include <iostream>
class single
{
public:
    static single* instance();
protected:// or set as private:
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

int main()
{
	single * aSingle = single::instance();
  return 1;
}

