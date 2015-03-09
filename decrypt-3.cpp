#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

int main() {

	//Declaring all Variables

	//Decalre variable ch which will be used to store Dictionary 1 to array
	char ch;

	//Decalre variable keylength
	int keylength;

	//Variable First to store value of character in the first group and second used to store value of character in second group
	// Variable diff is used to calculate the difference between first and second which is used to generate the pattern
	// Variable cipher_length is used to store the string length of the cipher text
	int first,second,diff,cipher_length;

	// Variable to store loop variables
	long int i,k;

	// Variable to store the pattern for the cipher text, value of 200, As per instructions maximum length of cipher text will be only 100
	int cipher_pattern[200];

	// Array to store the dictionary pattern
	int dictionary_pattern[21000];

	// Array to store the final plain text
	char plain[200];

	// Variable to find out the last position of the plain text during calculation, 
	// this is useful to add the remaining characters and to add termination character \0
	int last_position;

	// Variable to store cipher text and dictionary
	string cipher,dictionary;

	//Initialize increment variable to zero, will be used to calculate the total dictionary size
	i=0;

	// Lets get the input from console
	cout<<"Enter Cipher Text:";
	getline(cin, cipher);

	// What if the input cipher text contain CAPS ? , our code needs the cipher to be in small case, so convert 
	transform(cipher.begin(), cipher.end(), cipher.begin(),(int (*)(int))tolower);


	cout<<"Enter Key Length:";
	cin>>keylength;

	// Read the dictionary file and store it into string variable dictionary

	fstream fin("Dictionary2-1.txt", fstream::in);
	while (fin >> noskipws >> ch) 
	dictionary[i++]=ch;



	// Calculate length of the cipher text and store it into variable

	cipher_length=cipher.size();

	// Loop which goes through the entire cipher text and calculates the pattern, remember this pattern will be matched with the dictionary
	
	for(k=0;k<cipher_length;k++)
	if(k<(cipher_length-keylength))
	{
		// This part will be executed only if the loop variable is less than length of cipher minus the keylength, 
		// Remember we cannot generate pattern for the last portion

		// OK, time to calculate the values for each letter , 
		// for the first group and the second group, this is done by getting the ascii value and dividing by 96
		// The remainder after division is used as index

			first=cipher[k]%96;
			second=cipher[k+keylength]%96;

		// Sometime the character will spill after the letter 'z', need to round off and take care of that
			if(first>26)first=first%26;
			if(second>26)second=second%26;

		// Finally ready to calculate the difference and remember to store it to variable diff
			if(first>=second)
				diff=first-second;
			else
				diff=second-first;

		// The result should be regularly updated to an array , we need this later on for comparison
			cipher_pattern[k]=diff;

			//cout<<diff<<",";
	}
	
	
	int start[100],start_position[100],l,max,min;
	int position[30][100];
	int counter[30];
	cout<<endl<<endl;
	int value,ptr=0;
	start_position[ptr]=0;
	start[ptr++]=int(dictionary[0])%96;
	for(l=0;l<30;l++)
		counter[l]=0;
	for(k=0;k<i;k++)
	{
	value=int(dictionary[k]);
		if(value == 13 || value == 10)
		{
			if(value == 10 )
			{
			//cout<<int(dictionary[k+1])%96<<",";
			start_position[ptr]=k+1;
			start[ptr++]=int(dictionary[k+1])%96;
			
			}
		}
		else
		{
			//cout<<value%96<<",";
			position[value%96][counter[value%96]++]=k;
			
		}

	}
	cout<<endl;
//	for(int a=0;a<30;a++)
//		for(int b=0;b<counter[a];b++)
//			cout<<"Position[ "<<a<<" ][ "<<b<<" ]= "<<position[a][b]<<endl;


	int match_flag=0,temp;
	for(i=0;i<1;i++)
		{
		max=cipher_pattern[0];min=start[i];
		if(max<start[i])
			{
			max=start[i];min=cipher_pattern[0];
			}
		value=max-min;
		cout<<cipher_pattern[0]<<"--"<<start[i]<<"--"<<value<<endl;		
		for(int b=0;b<counter[value];b++)
			{
			cout<<position[value][b]<<endl;
			cout<<"Expecting "<<position[value][b]+1 <<" and "<< start_position[i]+1<<endl;
			first=int(dictionary[position[value][b]+1])%96;
			second=int(dictionary[start_position[i]+1])%96;
			max=first;
			min=second;
			if(max<second)
				{
				max=second;
				min=first;
				}
			cout<<"max= "<<max<<" min= "<<min<<" difference= "<<max-min<<endl;
			temp=max-min;
			if(temp==cipher_pattern[1])
			}
		}

cout<<endl;
return 0;
}
