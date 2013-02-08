#include <stdio.h> 
#include <string> 
using namespace std;

string&& test(const string& str) 
{ 
printf("1: 0x%08x\n", str.c_str()); string tmp(str);
printf("2: 0x%08x\n", tmp.c_str()); return std::move(tmp);
}

int main() { 
const std::string in("");
printf("0: 0x%08x\n", in.c_str()); 
printf("3: 0x%08x\n", test(in).c_str()); 
return 0; }


