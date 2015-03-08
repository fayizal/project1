#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

int main() {

char ch;int keylength;
int first,second,diff,cipher_length;
long int i,k;
int cipher_pattern[200];
int dictionary_pattern[21000];
char plain[200];
int last_position;
string cipher,dictionary;
i=0;

cout<<"Enter Cipher Text:";
getline(cin, cipher);

cout<<"Enter Key Length:";
cin>>keylength;

fstream fin("Dictionary1-2.txt", fstream::in);
while (fin >> noskipws >> ch) 
dictionary[i++]=ch;

//cout<<"dictionary size"<<i;

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
//cout<<k<<" : "<<cipher[k]<<":"<<first<<cipher[k+keylength]<<":"<<second<<" Diff : "<<diff<<endl;
}


//cout<<endl<<"Magic Pattern for the Dictionary"<<endl;

int temp,max,cipher_flag=0;

//cout<<"dictionary size"<<i<<endl;
//i=190;
//cout<<"dictionary size"<<i;

for(k=0;k<i;k++)
if(k<(i-keylength))
{


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

first=dictionary[k]%96;
second=dictionary[k+keylength]%96;


temp=(27-max);
first=first+temp;
second=second+temp;


if(first>26)first=first%26;
if(second>26)second=second%26;
if(first>=second)
diff=first-second;
else
diff=second-first;



//cout<<dictionary[k]<<":"<<first<<dictionary[k+keylength]<<":"<<second<<endl;

if(cipher_flag==(cipher_length-keylength))break;

if(cipher_pattern[cipher_flag]==dictionary_pattern[k] || cipher_pattern[cipher_flag]==diff)
{
//cout<<(cipher_length-keylength)<<" : "<<cipher_flag<<" : "<<dictionary[k]<<":"<<first<<dictionary[k+keylength]<<":"<<second<<" :Diff1: "<<dictionary_pattern[k]<<" : Diff2: "<<diff<<endl;
plain[cipher_flag]=dictionary[k];
cipher_flag++;
last_position=k;
//cout<<dictionary[k];
}
else
{

cipher_flag=0;

	if(cipher_pattern[cipher_flag]==dictionary_pattern[k] || cipher_pattern[cipher_flag]==diff)
	{
	plain[cipher_flag]=dictionary[k];
	cipher_flag++;
	last_position=k;
	}

}


//cout<<endl<<"------------------------"<<endl;
}


for(k=last_position+1;k<=last_position+keylength;k++)
plain[cipher_flag++]=dictionary[k];

plain[cipher_flag]='\0';
cout<<endl<<plain;

cout<<endl;
return 0;
}
