#include <iostream>
#include <string>
#include <cctype>
#include <vector>
using namespace std;

bool isValidPollString(string pollData);
bool isValidChar(char testChar);
bool isValidUppercaseStateCode(string stateCode);
bool isValidStateResult(string results);
int countSeats(string pollData, char party, int& seatCount);

bool isValidPollString(string pollData) {
	std::vector<int> commas;
	commas.push_back(-1); // Adding -1 as "comma" tells loop to start at beginning rather than first actual comma
	
	if (pollData.size() == 0)
		return true;
	if (pollData.size() == 1)
		return false;

	for (unsigned int i=0; i < pollData.size(); i++){
		pollData[i] = toupper(pollData[i]);
		if (!isValidChar(pollData[i])) { // Check for spaces or non digit/letter characters
			cerr << "invalid char " << pollData[i] << " detected" << endl;
				return false;
		}
		else if (pollData[i] == ',') // Create list indexes of all commas
			// Check commas are at distance big enough for state code or not 4 characters apart or not too close to end/start (which is always invalid) 
			if ((i - (commas[commas.size() - 1]) < 3) || (i - (commas[commas.size() - 1]) == 4) || (pollData.size() - i < 3) || i < 2) {
				cerr << "comma spacing error " << endl;
				return false;
			}
			else {
				//cout << "comma added at index: " << i << endl;
				commas.push_back(i); // Record locations of commas, store indexes in vector
			}
	}
	/*cout << "commas" << endl;       //---------- Testing code for printing comma database -----------
	for (int i = 0; i < commas.size(); i++) {
		cout << commas[i] << endl;
	}*/
	
	for (unsigned int j = 0; j < commas.size(); j++) {
		// Checking for valid state code
		if (!isValidUppercaseStateCode(pollData.substr(commas[j] + 1, 2))) {
			cerr << "invalid state code: " << pollData.substr(commas[j] + 1, 2) << endl;
			return false;
		}
		//else
			//cout << "Valid state code: " << pollData.substr(commas[j] + 1, 2) << endl;

		// Checking for valid state results
		int last; // Index of last char of current state result
		if (j == commas.size() - 1) // If last comma end at last char in string
			last = pollData.size();
		else
			last = commas[j + 1];
		
		if (last - (commas[j] + 3) == 0) { // Skip result check if section just contains state code and no results
			//cout << "just state code: " << pollData.substr(commas[j] + 1, 2) << endl;
			continue;
		}

		// Check if state result is valid
		if (!isValidStateResult(pollData.substr(commas[j] + 3, last - (commas[j]+3)))) {
			cerr << "Invalid state result: " << pollData.substr(commas[j] + 3, last - (commas[j]+3)) << endl;
			return false;
		}
	}
	return true;
}


bool isValidStateResult(string results) { // Func takes results (everything after state code) and confirms correctness
	if (!isdigit(results[0])) {
		return false;
		cerr << "Invalid state result: " << results << endl;
	}

	int digCount = 1; // tracks num of digits, detects if more than 2 in a row to return false (set to 1 bc of if statement above)
	int letCount = 0; // Tracks num of letters to ensure no repeats
	for (unsigned int k = 1; k < results.size(); k++) {
		if (k == results.size() - 1 && !isalpha(results[k])) { // Invalid if last char not a letter
			return false;
			cerr << "Invalid state result: " << results << endl;
		}
		// Invalid if more than 2 digits or 1 letter in a row
		if ((isdigit(results[k]) && digCount > 1) || (isalpha(results[k]) && letCount > 0)) {
			return false;
			cerr << "Invalid state result: " << results << endl;
		}

		if (isalpha(results[k])) {
			letCount++;
			digCount = 0;
		}
		else if (isdigit(results[k])) {
			digCount++;
			letCount = 0;
		}
	}
	//cout << "Valid state result: " << results << endl;
	return true;
}

bool isValidChar(char testChar) { // Use ascii to see if char is not alphanumeric or a comma
	int ascii = int(testChar);
	return (ascii == 44 || (ascii > 64 && ascii < 91) || (ascii > 96 && ascii < 123) || (ascii > 47 && ascii < 58));
}

//*************************************
//  isValidUppercaseStateCode
//*************************************

// Return true if the argument is a two-uppercase-letter state code, or
// false otherwise.

//TODO implement capitalization

bool isValidUppercaseStateCode(string stateCode)
{
	const string codes =
		"AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
		"LA.ME.MA.MD.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
		"OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
	return (stateCode.size() == 2 &&
		stateCode.find('.') == string::npos &&  // no '.' in stateCode
		codes.find(stateCode) != string::npos);  // match found
}

int countSeats(string pollData, char party, int& seatCount) {
	if (!isValidPollString(pollData)) // Cover basic input errors
		return 1;
	if (!isalpha(party))
		return 2;
	seatCount = 0;
	// Start at 2 to avoid checking statecode. If first state is DE, D could be detected and
	// checking back for ints could cause index out of range.
	for (unsigned int i = 2; i < pollData.size(); i++) {
		pollData[i] = toupper(pollData[i]); // Set to all caps
		if (pollData[i] == toupper(party)) { // If party char found, check nums behind and add them to the count
			if (isdigit(pollData[i - 2])) {
				seatCount += stoi(pollData.substr(i - 2, 2));
				//cout << "added2 " << stoi(pollData.substr(i - 2, 2)) << endl;
			}
			else if (isdigit(pollData[i - 1])) {
				seatCount += int(pollData[i - 1] - '0');
				//cout << "added1 " << int(pollData[i - 1] - '0') << endl;
			}
		}
	}
	return 0;
}

int main(){
	int s = 0;
	cout << countSeats("VT,CA,DE,CA,NY5D", 'D', s) << endl;
	cout << s << endl;
}