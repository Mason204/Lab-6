/*
Mason Henry
C++
November 14, 2019
Write a program that takes in a base two binary input from a file and tranlates it into base ten and outputs it to the screen.
*/

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//preconditions:Stream must be valid and program executed properly up to this point.
//postconditions:Determines if the two ifstreams are valid, if they are not returns true which returns one in the main.
//				 If streams are valid outputs the header and performs a priming read for each stream.
bool initialize(ifstream& inFile, ifstream& inFile2, char& Bnum, char& reader, string BinaryIn, string BinaryIn2);
//preconditions:Stream must be valid, initialize must have returned false, and inFile must be valid.
//postconditions:Sets output to either false or to remain true depending on if the current line from the file is valid. Updates
//				 spacing variable to the correct number required for the spacing.
void Bcheck(char& Bnum, char& reader, int& spacing, ifstream& infFile, ifstream& inFile2, bool& output);
//preconditions:Stream must be valid, intialize must have returned false, output must be true, and inFile must be valid.
//postconditions:Sets proper spacing and outputs the binary number to the screen. Determines the value of the decimal number
//				 and the proper spacing needed to output that number and outputs it. Sets three variables back to their original
//				 values to be used later.
void displaytrue(bool& output, int& spacing, char& Bnum, unsigned int& DnumDigits, unsigned int& Dnum, int& DnumCounter, ifstream& inFile);
//preconditions:Stream must be valid, intialize must have returned false, inFile must be valid.
//postconditions:If output is false, informs the user that there has been a bad didgit on input. Makes sure that Bnum is at the end
//				 of the current line and then inputs the next line. Sets two more variables back to their starting values.
void displayfalse(bool& output, ifstream& inFile, ifstream& inFile2, char& Bnum, char& reader, int& spacing, int& DnumCounter);

int main()
{
	//Binary number read in from the main file.
	char Bnum = 0;
	//Decimal number that is to be calculated.
	unsigned int Dnum = 0;
	//Is used to read in from the second ifstream to make sure the line is valid.
	char reader = 0;
	//Is used to determine what is outputed to the screen.
	bool output = true;
	//Used for the spacing of the binary numbers.
	int spacing = -3;
	//Next two are used for the spacing of the decimal numbers. (Out of every problem to be solved in this program I hated this the most :D )
	unsigned int DnumDigits = 0;
	int DnumCounter = 0;
	//The next four are the two ifstreams from the same file location.
	string BinaryIn = "C:/Users/jhphoto/Desktop/Mason Scripts/Lab 6/BinaryIn.DAT";
	ifstream inFile;
	string BinaryIn2 = "C:/Users/jhphoto/Desktop/Mason Scripts/Lab 6/BinaryIn.DAT";
	ifstream inFile2;

	//Checks to make sure the files are valid and are in the correct locations. If they are not informs user and returns 1.
	if (initialize(inFile, inFile2, Bnum, reader, BinaryIn, BinaryIn2))
		return 1;
	//runs the program as long as the file is valid.
	while (inFile)
	{
		Bcheck(Bnum, reader, spacing, inFile, inFile2, output);
		displaytrue(output, spacing, Bnum, DnumDigits, Dnum, DnumCounter, inFile);
		displayfalse(output, inFile, inFile2, Bnum, reader, spacing, DnumCounter);
	}
	return 0;
}

bool initialize(ifstream& inFile, ifstream& inFile2, char& Bnum, char& reader, string BinaryIn, string BinaryIn2)
{
	//Opens the two streams to the same file.
	inFile.open(BinaryIn);
	inFile2.open(BinaryIn2);

	//If either file is invalid it returns true which will return 1 in the main function.
	if (!inFile || !inFile2)
	{
		cout << "Can't find the file";
		return true;
	}

	//Outputs the header.
	cout << setw(22) << "Binary Number" << setw(36) << "Decimal Equivalent\n";

	//The two priming reads for each stream.
	inFile.get(Bnum);
	inFile2.get(reader);

	return false;
}
void Bcheck(char& Bnum, char& reader, int& spacing, ifstream& inFile, ifstream& inFile2, bool& output)
{
	//removes all characters in front of the first one and checks if they are valid characters. If they are not makes output false.
	while (Bnum != '1')
	{
		if (reader != '0' && reader != ' ' && reader != '\n')
			output = false;
		inFile.get(Bnum);
		inFile2.get(reader);
	}
	//The second inFile checks to make sure that the line is valid by checking to make sure it only contains 1's and 0's. 
	//With each iteration the spacing goes up so that the proper spacing can be used for the output of the decimal number.
	while (reader != '\n' && inFile2)
	{
		if (reader != '1' && reader != '0')
			output = false;
		spacing++;
		inFile2.get(reader);
	}
}
void displaytrue(bool& output, int& spacing, char& Bnum, unsigned int& DnumDigits, unsigned int& Dnum, int& DnumCounter, ifstream& inFile)
{
	if (output == true)
	{
		//Outputs the proper width for the binary number.
		cout << setw(15 - spacing / 2);
		//Outputs the binary number one digit at a time and determines the decimal number twice, one to be outputted and one used
		//to determine how many digitis the decimal number has.
		while (Bnum != '\n' && inFile)
		{
			Dnum = (Dnum * 2) + (int(Bnum) - 48);
			DnumDigits = Dnum;
			cout << Bnum;
			inFile.get(Bnum);
		}
		//Determines the number of digits the decimal nuber has.
		while (DnumDigits >= 1)
		{
			DnumDigits /= 10;
			DnumCounter++;
		}
		//Sets the proper width and outputs the decimal number. Set variable equal to 0 so they can be used on the next input line.
		if (Bnum == '\n' || !inFile)
		{
			if (Dnum == 2 || Dnum == 3)
				spacing = -2;
			cout << setw(32 + (DnumCounter / 2) - (spacing+3) / 2);
			cout << Dnum << endl;
			Dnum = 0;
			DnumDigits = 0;
			DnumCounter = 0;

		}
	}
}
void displayfalse(bool& output, ifstream& inFile, ifstream& inFile2, char& Bnum, char& reader, int& spacing, int& DnumCounter)
{
	//Outputs that there was a bad digit and sets output back to true. Also makes sure that the Bnum value has reached the end of
	//the current line.
	if (output == false)
	{
		cout << setw(26) << "Bad digit on input\n";
		while (Bnum != '\n' && inFile)
			inFile.get(Bnum);
		output = true;
	}
	inFile.get(Bnum);
	inFile2.get(reader);
	//Resets the variables back to their starting values so they can be used again on the next line.
	spacing = -3;
	DnumCounter = 0;
}