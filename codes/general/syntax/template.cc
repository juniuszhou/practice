/*
case to show how to use template and specilization of a template.
*/
template<class T> class a
{
	public:
	void f1() const {cout << "const" << endl;}
	void f1()  {cout << "not const" << endl;}
};

template<> class a<int>
{
public:
	void f1() const {cout << "const" << endl;}
	void f1()  {cout << "not const" << endl;}
};

int main()
{
	const a<float> * ap = new a<float>;
	ap->f1();
	return 0;
}

