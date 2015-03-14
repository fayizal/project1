#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

int main()
{

	// Declare variable to store string length
	int length;

	// Declare the array for storing key, Assume maximum length of the text to be entered is of length 100
	int key[21000];

	// Declare the integer to store key length to be used
	int keylength;

	// Declare loop variables
	int i;

	// Declare string to store encrypted text
	string encrypted_string;

	// Declare integer to store encrypted value
	int enc_value;

	// Print the message to Enter string
	string input_string;
	cout << "Enter Text : ";

	// To get the string even with white space
	getline(cin, input_string);
	
	// Initialize Encrypted string to the input string
	encrypted_string=input_string;

	// Print the message to Enter key length
	cout << "Enter Key Length : ";

	// Store the key length to the variable
	cin >> keylength;
	
	// To calculate the legth of the string
	length=input_string.size();

	// Loop which populates key array with the keylength intervals
	for(i=0;i<length;i++)
	{
	key[i]=(i%keylength)+1;
	}
	

	// To convert the whole string to lower case
	transform(input_string.begin(), input_string.end(), input_string.begin(),(int (*)(int))tolower);

	// To display numerical value of each letter of the string seperated by dot
	//for(i=0;i<length;i++)
	//cout << int(input_string[i])%96<<".";

	// End line to seperate the strings
	cout << endl;


	// To store encrypted string
	for(i=0;i<length;i++)
	{
	enc_value=int(input_string[i])%96;
	if(enc_value==32)enc_value=0;
	enc_value=enc_value + key[i];
	enc_value=enc_value+96;
	if(enc_value>122)
	enc_value=(enc_value%122)+96;
	encrypted_string[i]=char(enc_value);
	}
	encrypted_string[i]='\0';
	cout<<"Encrypted Cipher is "<<endl<<endl;
	cout<<encrypted_string<<endl;

	return 0;
}
