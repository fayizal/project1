#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;


int* pattern1_generate(string input,int keylength);
int* pattern2_generate(string input,int keylength);

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

	}
	
	// This variable is used to calculate value for each letter
	int value;
	// Array used to store words from dictionary2
	char words[200][100];

	// Pointers used to track each word and the corresponding character
	int strptr=0,ltrptr=0;

	// This process will extract word by word from dictionary and will store them to our multidimensional array 

	for(k=0;k<i;k++)
        {
        value=int(dictionary[k]);
                if(value == 13 || value == 10)
                {
			if(value==10)
				{
				words[strptr++][ltrptr]='\0';
				ltrptr=0;
				}
                }
                else
                {
			words[strptr][ltrptr++]=dictionary[k];
                }

        }
	
	// Array which will store value for Pattern1	
	int *pattern1=new int[200];
	// Array which will store value for Pattern2
        int *pattern2=new int[200];

	// We need to track if it matches and also if there are multiple matches then match_max is used for accuracy
	int match=0,match_max=0;

	// The seed value and seed string is used to store the word corresponding to the match
	int seed=0;
	char seed_string[200];	

	// Again if there are multiple matches and no clear winner using match_max then lets store all of them and 
	// proceed to phase 2 where we combine each of them to the remaining words
	int similar_seed_count=0;
	int similar_seed_index[200];
	char similar_seed[200][100];

	// Initialize seed string to null value
	strcpy(seed_string,"");


	// Time to calculate the pattern for each word in the dictionary
	for(k=0;k<=strptr;k++)
	{
		match=0;
		pattern1=pattern1_generate(words[k],keylength);
		pattern2=pattern2_generate(words[k],keylength);
		for(int z=0;z<(strlen(words[k])-keylength);z++)
			{
			if(pattern1[z]==cipher_pattern[z] || pattern2[z]==cipher_pattern[z])
				match++;
			else break;
			}
		if(match>match_max)
                {
                        match_max=match;
                        seed=k;
                        strcpy(seed_string,words[k]);

                }
		if(match==match_max and match!=0 )
		{
			similar_seed_index[similar_seed_count]=k;
			strcpy(similar_seed[similar_seed_count++],words[k]);
		}

	}

	// OK, now we have matched pattern for each word and if there are similar matches then all of them are stored to array similar_seed

	// We will store the new string input to array words2, the new input will be a combination of the above text plus space and all the other words
	char words2[100];

	// While calculating length of each pattern , we need a variable to store the minimum
	int pattern_min;

	// Array to store the final result
	char final_text[100];

	// Reset the match maximum to zero
	match_max=0;

	
	// Time for loop to start for phase2, get the base string and start comparing by adding all other words to this

	for(int z=0;z<similar_seed_count;z++)
	{
		for(k=0;k<=strptr;k++)
			{

				// Keep adding all words and exclude if it is own
				if( similar_seed_index[z] != k )
					{
						strcpy(words2,"");
						// Take the base string
						strcat(words2,similar_seed[z]);

						// Add space in between
						strcat(words2," ");

						// Add the next word
						strcat(words2,words[k]);

						// Reset match for each try
						match=0;

						// We need to have both pattern, this is the z round off issue
						pattern1=pattern1_generate(words2,keylength);
						pattern2=pattern2_generate(words2,keylength);
						
						// We need to find the pattern minimum, this will be number of times the loop will be executed
						pattern_min=strlen(words2)-keylength;

						if(pattern_min>cipher_length ) pattern_min = cipher_length;
						
						// Loop for comparing the pattern, either pattern1 or pattern2 should match
							for(int y=0;y<pattern_min;y++)
							{
							if(pattern1[y]==cipher_pattern[y] || pattern2[y]==cipher_pattern[y] )
								match++;
							else break;
							}

						// Remember to keep track of maximum value of match, to select the string which matches exactly with the cipher
						 if(match>match_max)
        				        {
							match_max=match;
							strcpy(final_text,words2);
						}
	
					}
			}
	}
		

	// If everything goes fine and if the length of input cipher matches the combination of phase1 and phase 2 then output the results
	if(strlen(final_text)==cipher_length)
		cout<<final_text;	

cout<<endl;
return 0;
}



int* pattern2_generate(string input,int keylength)
{

	int *temp= new int[200];
	int first,second,length,diff;
	length=input.size();
	int jump,max;



	for(int k=0;k<length;k++)
	{
		if(k<(length-keylength))
		{
		        first=input[k]%96;
		        second=input[k+keylength]%96;
			max=first;
			if(second>max)max=second;

			jump=(27-max);
			first=first+jump;
			second=second+jump;

			if(first>26)first=first%26;
			if(second>26)second=second%26;

			if(first>=second)
			    diff=first-second;
			else
			    diff=second-first;

			temp[k]=diff;

		}
	}

return temp;
}





int* pattern1_generate(string input,int keylength)
{

	int *temp= new int[200];
	int first,second,length,diff;
	length=input.size();
	for(int k=0;k<length;k++)
	{
		if(k<(length-keylength))
		{
			first=input[k]%96;
			second=input[k+keylength]%96;

			if(first>26)first=first%26;
			if(second>26)second=second%26;

			if(first>=second)
			    diff=first-second;
			else
			    diff=second-first;

			temp[k]=diff;

		}
	}

return temp;
}
