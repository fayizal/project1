#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;
string test(string b);

int main()
{	
	string a;
	cin>>a;
	cout<<test(a);
	return 0;
}

string test(string b)
{
if(b=="hello")return "world";
else return "nope";
}
