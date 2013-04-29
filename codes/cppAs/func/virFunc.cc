// g++ -S virFunc.cc

class a
{
public:
    virtual void fun();
    virtual void fun2();
    virtual void fun3();
    virtual void fun4();
};

int main()
{
a * pa = new a();
pa->fun();
int i = 9;
pa->fun2();
pa->fun3();
pa->fun4();    
return i;
}
