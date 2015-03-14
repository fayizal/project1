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
	int cipher_pattern_match=0;

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
			if(first==32)first=0;
			if(second==32)second=0;

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

			cipher_pattern_match++;

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

	int a,b,c,d,e;
	char words3[200];
	int words3_length;
	int max_of_strptr=0;

	int pattern_temp[200];

	for(a=0;a<=strptr;a++)
	{
		for(b=0;b<=strptr;b++)
		{
			 for(c=0;c<=strptr;c++)
			 {	

				
				strcpy(words3,"");
				// Combining two words as initial pattern
				strcat(words3,words[a]);
				strcat(words3," ");
				strcat(words3,words[b]);
				strcat(words3," ");
				strcat(words3,words[c]);



				
				// Resetting counter match to zero before calculation
				match=0;

				pattern1=pattern1_generate(words3,keylength);
				pattern2=pattern2_generate(words3,keylength);

		
				words3_length=strlen(words3);
				words3_length=words3_length-keylength;
				// Generate pattern for the combined word and compare, find out which combination is having the maximum value
				for(e=0;e<words3_length;e++)
	                        {
		
					if(pattern1[e]==cipher_pattern[e] || pattern2[e]==cipher_pattern[e])
					{
                                	match++;
					pattern_temp[e]=cipher_pattern[e];
					}


                        	}
			

			
				
				// OK, so there is a match which is more than match_max.. time to replace that
				if(match>match_max)
	        	        {
                        	match_max=match;
				similar_seed_count=0;
        	        	}

			
				// We need to store similar results to an array
        	                 if(match==match_max and match!=0 )
                	        {
                       		 strcpy(similar_seed[similar_seed_count++],words3);
                        	}


			
			}// End of loop C
		} // End of loop B
	}// End of loop A


	


	char source_string[200];
	char par_source_string[200];
	char source_string_match[200];
	match_max=0;
	int seed_max=0;
	char final_text[200];

	for(a=0;a<similar_seed_count;a++)

	{
	strcpy(par_source_string,similar_seed[a]);
	match_max=0;
	
	while(strlen(par_source_string)<cipher_length && strlen(par_source_string)<100)
	{
	
	for(k=0;k<=strptr;k++)
	{
		strcpy(source_string,par_source_string);
		strcat(source_string," ");
		strcat(source_string,words[k]);
		
		// Resetting counter match to zero before calculation
                        match=0;

                        pattern1=pattern1_generate(source_string,keylength);
                        pattern2=pattern2_generate(source_string,keylength);


                        // Generate pattern for the combined word and compare, find out which combination is having the maximum value
                        for(c=0;c<(strlen(source_string)-keylength);c++)
                        {

                                if(pattern1[c]==cipher_pattern[c] || pattern2[c]==cipher_pattern[c])
                                {
                                match++;
                                }

                        }

			 // OK, so there is a match which is more than match_max.. time to replace that
                        if(match>match_max)
                        {
                        match_max=match;
			strcpy(source_string_match,source_string);
                        }

	}

	strcpy(par_source_string,source_string_match);
	

	}

	if(seed_max<match_max)
	{
	strcpy(final_text,par_source_string);
	seed_max=match_max;
	}	

	}// End of seed_string loop

	cout<<"seed max is "<<seed_max<<endl;

	if(cipher_length>100)
	{
	cipher_length=100;
	}
	if(cipher_pattern_match==seed_max)
	{
	for(k=0;k<cipher_length;k++)
		cout<<final_text[k];
	}
	else
	{
	cout<<"Not Found";
	}
	

//BREAK
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

			if(first==32)first=0;
			if(second==32)second=0;
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
			if(first==32)first=0;
			if(second==32)second=0;

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
