#include "Excpt.h"
#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>  

using namespace std;

 class Sum {
   int val;
  public:
   Sum(int i) :val(i) {
   cout<<"construct is called"<<endl;}
   operator int() const 
   {
	   cout<<"operator int is called"<<endl;

		   return val; }  // extract value

   int operator()(int i) { 
	   cout<<"operator sum is called"<<endl;
	   return val+=i; } // application
  };

int main(int argc, char* argv[])
{

	vector<int> v;
	v.push_back(1);
	v.push_back(2);


	Sum s = 0; // this type also call construct since its variable def
cout<<"init value is given"<<endl;

	s(8);//this type call construct function
    cout<< s << endl;

		s(19);//this type call construct function
    cout<< s << endl;

		s = s(8);
    cout<< s << endl;

	s = for_each(v.begin(),v.end(),s);
	

      cout << "the sum is " << s << "\n";

   	return 0;
}

