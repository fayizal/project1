#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
  ifstream inputFile;
  string filename;

  cout << "Please enter the name of your input file: ";
  cin >> filename;

  inputFile.open(filename.c_str());

  if (inputFile.fail())
  {
      cout << "Input file could not be opened. Try again." << endl;
      return 1;
  }

  int headerNum = 0;
  inputFile >> headerNum;
  if(inputFile.eof()) {
      cout << "Error reading input file contents." << endl;
      return 1;
  }

  string *names = new string[headerNum];
  for(int i = 0; i < headerNum; i++)
    inputFile >> names[i];

  for(int i = 0; i < headerNum; i++)
    cout << names[i] << endl;

}
