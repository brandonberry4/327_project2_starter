/*
 * array_functions.cpp
 *
 *  Created on: Sept 16, 2019
 *      Author: Brandon Berry
 */

//============================================================================
//	TODO add necessary includes here
#include "utilities.h"
#include "array_functions.h"
#include "constants.h"
#include <array>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
using std::vector;

//============================================================================

//============================================================================
//	stuff you will need
//============================================================================

//============================================================================
//	TODO add necessary includes here
//============================================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>

#include "utilities.h"
#include "array_functions.h"
#include "constants.h"

using namespace std;
using namespace constants;

//============================================================================
//	stuff you will need
//============================================================================
//TODO define a structure to track words and number of times they occur
struct entry
{
	string word = "";
	int number_occurences = 0;
};

//TODO add a global array of entry structs (global to this file)
entry gArray[MAX_WORDS];

//TODO add variable to keep track of next available slot in array
	//entry nextVar = gArray[0];
int trackNextSlot = 0;

//TODO define all functions in header file

//TODO look in utilities.h for useful functions, particularly strip_unwanted_chars!
const int NOT_DONE = -9;
const bool FALSE_NOT_DONE = false;
const std::string STR_NOT_DONE = "not done";


//zero out array that tracks words and their occurrences
void clearArray(){
	trackNextSlot = 0;
}


//how many unique words are in array
int getArraySize(){
	return trackNextSlot;
}


//get data at a particular location
std::string getArrayWordAt(int i){
	return gArray[i].word;

}

int getArrayWord_NumbOccur_At(int i){
	if (i > trackNextSlot or i < 0){
		return FAIL_NO_ARRAY_DATA;
	}
	else{
		return gArray[i].number_occurences;
	}
}

/*loop through whole file, one line at a time
 * call processLine on each line
 * returns false: myfstream is not open
 *         true: otherwise*/
bool processFile(std::fstream &myfstream){
	bool fileOpen = myfstream.is_open();
	if (!fileOpen){
		return fileOpen;
	}

	string line;

	while (!myfstream.eof()){
		getline(myfstream, line);
		processLine(line);
	}

	return fileOpen;
}


/*take 1 line and extract all the tokens from it
feed each token to processToken for recording*/
void processLine(std::string &myString){
	stringstream ss(myString);
	string tempToken;

	while (getline(ss, tempToken, CHAR_TO_SEARCH_FOR)){
		processToken(tempToken);
	}
}


/*Keep track of how many times each token seen*/
void processToken(std::string &token){

	if (strip_unwanted_chars(token)){
		string upToken = token;
		toUpper(upToken); //uppercase a string, useful for confirming that To==TO==to==tO
		for (int i = 0; i < trackNextSlot; i++){
			string upWord = gArray[i].word;
			toUpper(upWord);
			if (upToken == upWord){
				gArray[i].number_occurences += 1;
				return;
			}
		}

		entry newEntry;
		newEntry.word = token;
		newEntry.number_occurences = 1;
		gArray[trackNextSlot] = newEntry;
		trackNextSlot++;
	}
	else{ //not a valid token, only unwanted chars, do nothing
		return;
	}
}


/*if you are debugging the file must be in the project parent directory
  in this case Project2 with the .project and .cProject files*/
bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode ){ //= std::ios_base::in

	myfile.open(myFileName.c_str(), mode);
	if (myfile.is_open()){
		return true;
	}
	else{
		return false;
	}
}

/*iff myfile is open then close it*/
void closeFile(std::fstream& myfile){
	if (myfile.is_open()){
	myfile.close();
	}

}


/* serializes all content in myEntryArray to file outputfilename
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in myEntryArray
 * 			SUCCESS if all data is written and outputfilename closes OK
 * */
int writeArraytoFile(const std::string &outputfilename){
	fstream outputFile;

	bool attemptOpen = openFile(outputFile, outputfilename, fstream::out);
	if (!attemptOpen){
		return FAIL_FILE_DID_NOT_OPEN;
	}

	if (getArraySize() == 0){
		return FAIL_NO_ARRAY_DATA;
	}

	for (int i = 0; i < trackNextSlot; i++){
		outputFile << gArray[i].word << " " << gArray[i].number_occurences << endl;
	}

	return SUCCESS;

}


/*
 * Sort myEntryArray based on so enum value.
 * You must provide a solution that handles alphabetic sorting (A-Z)
 * The presence of the enum implies a switch statement based on its value
 */
void sortArray(constants::sortOrder so){ //taking the sort order enums
	entry trackEntry;

	switch(so){
		case NONE:{break;}

		case ASCENDING:{
			bool swap = true;
			while(swap){
				swap = false;
				for (int i = 0; i < trackNextSlot - 1; i++){
					string mainWord = gArray[i].word;
					string compWord = gArray[i+1].word;

					toUpper(mainWord); //uppercase a string
					toUpper(compWord); //uppercase a string
					if(mainWord > compWord){
						swap = true;
						entry placeHolder = gArray[i];
						gArray[i] = gArray[i+1];
						gArray[i+1] = placeHolder;
					}
				}
			}
		break;
		}
	case DESCENDING:{
		bool swap = true;
					while(swap){
						swap = false;
						for (int i = 0; i < trackNextSlot - 1; i++){
							string mainWord = gArray[i].word;
							string compWord = gArray[i+1].word;

							toUpper(mainWord);
							toUpper(compWord);
							if(mainWord < compWord){
								swap = true;
								entry placeHolder = gArray[i];
								gArray[i] = gArray[i+1];
								gArray[i+1] = placeHolder;
							}
						}
					}
		break;
	}
	case NUMBER_OCCURRENCES:{
		bool swap = true;
					while(swap){
						swap = false;
						for (int i = 0; i < trackNextSlot - 1; i++){

							if(gArray[i].number_occurences > gArray[i+1].number_occurences){
								swap = true;
								entry placeHolder = gArray[i];
								gArray[i] = gArray[i+1];
								gArray[i+1] = placeHolder;
							}
						}
					}
		break;
	}
	}

}
