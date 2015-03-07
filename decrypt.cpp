#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

int main() {

char ch;int k,keylength;
int first,second,diff,i=0,cipher_length;
int cipher_pattern[100];
int dictionary_pattern[100];
int plain[100];
string cipher,dictionary;

cout<<"Enter Cipher Text:";
getline(cin, cipher);

cout<<"Enter Key Length:";
cin>>keylength;

fstream fin("Dictionary1-2.txt", fstream::in);
while (fin >> noskipws >> ch) 
dictionary[i++]=ch;

//cout<<"Magic Pattern for the Cipher Text"<<endl;

cipher_length=cipher.size();

for(k=0;k<cipher_length;k++)
if(k<(cipher_length-keylength))
{
first=cipher[k]%96;
second=cipher[k+keylength]%96;
if(first>26)first=first%26;
if(second>26)second=second%26;
if(first>=second)
diff=first-second;
else
diff=second-first;
//cout<<diff<<",";
cipher_pattern[k]=diff;
//cout<<cipher[k]<<":"<<first<<cipher[k+keylength]<<":"<<second<<endl;
}


//cout<<endl<<"Magic Paatern for the Dictionary"<<endl;

i=100;
int temp,max;

cout<<"dictionary size"<<i;

for(k=0;k<i;k++)
if(k<(i-keylength))
{
cout<<"...";
first=dictionary[k]%96;
second=dictionary[k+keylength]%96;
//cout<<"first="<<first<<endl;
if(first>26)first=first%26;
if(second>26)second=second%26;
if(first>=second)
diff=first-second;
else
diff=second-first;

dictionary_pattern[k]=diff;

max=first;
if(second>max)max=second;

//cout<<"Max="<<max<<" ";

first=dictionary[k]%96;
second=dictionary[k+keylength]%96;

//cout<<"First="<<first<<"Second= "<<second<<endl;

temp=(27-max);
first=first+temp;
second=second+temp;

//cout<<"Temp="<<temp<<" ";

//cout<<"First="<<first<<"Second= "<<second<<endl;

if(first>26)first=first%26;
if(second>26)second=second%26;
if(first>=second)
diff=first-second;
else
diff=second-first;

//cout<<diff<<",";
cout<<dictionary[k]<<":"<<first<<dictionary[k+keylength]<<":"<<second<<endl;
cout<<cipher[k]<<":"<<first<<cipher[k+keylength]<<":"<<second<<endl;
cout<<"-------------------------------"<<endl;

if(cipher_pattern[k]==dictionary_pattern[k] || cipher_pattern[k]==diff)
cout<<dictionary[k];


}

cout<<endl;
return 0;
}
