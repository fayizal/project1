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

	fstream fin("Dictionary1-2.txt", fstream::in);
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
	}



	// Some more variables need for the next phase
	// temp and max for difference calculation for Pattern2 and cipher_flag to make sure we got the right string

	int temp,max,cipher_flag=0;


	// Loop which starts from zero till it reaches the length of dictionary
	for(k=0;k<i;k++)
	if(k<(i-keylength))
	{
		// Same like cipher , here also we cannot generate the pattern for the last portion

			// ASCII calculation in progress
			first=dictionary[k]%96;
			second=dictionary[k+keylength]%96;


		// Rounding of for letters which crosses z
			if(first>26)first=first%26;
			if(second>26)second=second%26;


		// Calculate difference , this will be used for Pattern1
			if(first>=second)
				diff=first-second;
			else
				diff=second-first;


		// Store the results for Pattern1
			dictionary_pattern[k]=diff;


		// Sometimes there are scenarios to redo the above process so that we get Pattern2
		// Before doing that lets calulate maximum, i.e. which is greater first or second ?
			max=first;
			if(second>max)max=second;

		// Again ASCII calculation
			first=dictionary[k]%96;
			second=dictionary[k+keylength]%96;

		// This is interesting, now we are just trying to find a value temp such that one of the value either "first" or "second" will cross the letter z and 
		// will be eventually rounded off. This is the secret to generate Pattern2
			
			temp=(27-max);
			first=first+temp;
			second=second+temp;

		// OK, now we are ready to calculate Pattern2 and store it to diff
			if(first>26)first=first%26;
			if(second>26)second=second%26;
			if(first>=second)
				diff=first-second;
			else
				diff=second-first;



		// Just to check before doing anything , cipher_flag which keeps track of the letter recovered so far and 
		// cipher_length which is the length of cipher text
		// If both are equal then no need to continue we found the text
		// Remember that we dont take the last portion "keylength" since we wont be able to generate the pattern, so we subtract it

			if(cipher_flag==(cipher_length-keylength))break;

		// If cipher text pattern matches either Pattern1 or Pattern2 of dictionary then it is positive match

			if(cipher_pattern[cipher_flag]==dictionary_pattern[k] || cipher_pattern[cipher_flag]==diff)
			{
				// Save this to plain array
					plain[cipher_flag]=dictionary[k];
				// Keep your pointer updated
					cipher_flag++;
				// And save your last position
					last_position=k;
			}
			else
			{

				// Hmm , there is a mismatch, What is the current string in the dictionary is the start of original text ?
				// Just to be sure , we need to compare the current pattern with the first cipher pattern
					cipher_flag=0;

				// Comparison for the first cipher pattern with the existing dictionary pattern
				if(cipher_pattern[cipher_flag]==dictionary_pattern[k] || cipher_pattern[cipher_flag]==diff)
				{
					plain[cipher_flag]=dictionary[k];
					cipher_flag++;
					last_position=k;
				}

}


}

				// Now that we have finished the loop, remember the portion which we skipped before ? ( i.e. keylength part )
				// time to add them to the plain text variable

					for(k=last_position+1;k<=last_position+keylength;k++)
						plain[cipher_flag++]=dictionary[k];

				// Also add a termination character for the string to end
					plain[cipher_flag]='\0';

				// If the plain array matches the length of cipher text then it is a match else print error
					if(strlen(plain)==cipher_length)
						cout<<endl<<plain;
					else
						cout<<"String Not Found";


				// That's all !
cout<<endl;
return 0;
}
