#include <iostream>
#include <algorithm>
#include <auto>

using namespace std;

int c;
int main()	
{  
   char s[]="Hello World!";  
   int Uppercase = 0; //modified by the lambda	
   for_each(s, s+sizeof(s), [&Uppercase] (char c) {
  
   
        cout << 100 << endl;
	    }
   );  
 //cout<< Uppercase<<" uppercase letters in: "<< s<<endl;

 //auto func = [] () { cout << "Hello world JJJJJJJJJunius"; };  
 //   func(); // now call the function  

 cin >> c;
 return c;
} 


