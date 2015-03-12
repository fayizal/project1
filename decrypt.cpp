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

	// Array to store the final plain text
	char plain[200];

	// Variable to find out the last position of the plain text during calculation, 
	// this is useful to add the remaining characters and to add termination character \0
	int last_position;

	// Variable to store cipher text and dictionary
	string cipher,dictionary;

	  // Some more variables need for the next phase
        // temp and max for difference calculation for Pattern2 and cipher_flag to make sure we got the right string

        int temp,max,cipher_flag=0;

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



//----------------------------This is the code for checking from Dictionary1------------------------------------

	cout<<"-----------------------------Dictionary1 Phase--------------------------------------------------"<<endl;

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
						cout<<"String Not Found in Dictionary1"<<endl;

cout<<endl<<"-----------------------------------------------------------------------------------------"<<endl;



//-------------------End of code for checking from Dictionary1-----------------------------------


//------------------Code for checking from Dictionary2-------------------------------------------


cout<<endl<<"----------------------------------------Dictionary2 Phase--------------------------------------------------"<<endl;

 	i=0;	
	 // Read the dictionary file and store it into string variable dictionary

	        fstream fin1("Dictionary2-1.txt", fstream::in);
        	while (fin1 >> noskipws >> ch)
	        dictionary[i++]=ch;

	// Variable Declaration Section for the next phase

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
                cout<<final_text<<endl;
	else
		cout<<"String Not Found in Dictionary2"<<endl;

cout<<endl<<"---------------------------------------------------------------------------------------"<<endl;

//-------------------------End of Program---------------------------------------------------------
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






