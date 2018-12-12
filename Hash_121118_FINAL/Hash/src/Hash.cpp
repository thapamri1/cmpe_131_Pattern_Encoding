#include <iostream>
#include <ctime>
#include <cstdlib>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include "hash.h"

using namespace std;

//DESTRUCTOR for HASHTABLE
hash::~hash() {
	itemA* temp;
	itemA* temp_next;
	for (int i = 0; i < tableSize; i++) {
		temp = HashTableA[i];
		while (NULL != temp) {
			temp_next = temp->next;
			delete temp;
			temp = temp_next;
		}
		HashTableA[i] = NULL;
	}

	itemB* temp2;
	itemB* temp2_next;
	for (int i = 0; i < tableSize; i++) {
		temp2 = HashTableB[i];
		while (NULL != temp2) {
			temp2_next = temp2->next;
			delete temp2;
			temp2 = temp2_next;
		}
		HashTableB[i] = NULL;
	}
}

//CONSTRUCTOR for HASHTABLE
hash::hash() {
	for (int i = 0; i < tableSize; i++) {
		HashTableA[i] = new itemA;
		HashTableA[i]->patA = "empty";
		HashTableA[i]->encA = "empty";
		HashTableA[i]->next = NULL;
	}

	for (int i = 0; i < tableSize; i++) {
		HashTableB[i] = new itemB;
		HashTableB[i]->patB= "empty";
		HashTableB[i]->encB = "empty";
		HashTableB[i]->next = NULL;
	}
}

//ADDS THE GIVEN STRING TO BOTH HASHTABLEA & HASHTABLEB
//@param text is the string to be added to the hashtables
//@return N/A
void hash::addAll(string text) {
	string strPair = "";
	string rr = "";
	int x = 255;
	for (unsigned i = 0; i < text.length(); i = i + 2) {
		strPair = text.substr(i, 2);
		char r;
		bool findET = FindENCT(strPair);
		if (!findET) {
			r = (char) x;
			string rr(&r, 1);
			AddItemA(strPair, rr);
			AddItemB(strPair, rr);
		}
		x--;
	}
}

//ADDS ITEMS TO HASHTABLE A
//@param PATN and ENCT are pattern and encoded text to be added to the hashtable
//@return N/A
void hash::AddItemA(string pattern, string encoded) {
	int index = Hash(pattern);
	if (HashTableA[index]->patA == "empty") {
		HashTableA[index]->patA = pattern;
		HashTableA[index]->encA = encoded;
	}

	else {
		itemA* Ptr = HashTableA[index];
		itemA* newItem = new itemA;
		newItem->patA = pattern;
		newItem->encA = encoded;
		newItem->next = NULL;
		while (Ptr->next != NULL) {
			Ptr = Ptr->next;
		}
		Ptr->next = newItem; //Links the last item in the list to the newly created item that n is pointing to
	}
}

//ADDS ITEMS TO HASHTABLE B
//@param PATN and ENCT are pattern and encoded text to be added to the hashtable2
//@return N/A
void hash::AddItemB(string pattern, string encoded) {
	int index = Hash(encoded);

	if (HashTableB[index]->encB == "empty") {
		HashTableB[index]->patB = pattern;
		HashTableB[index]->encB = encoded;
	}

	else {
		itemB* Ptr = HashTableB[index];
		itemB* newItem = new itemB;
		newItem->patB = pattern;
		newItem->encB = encoded;
		newItem->next = NULL;
		while (Ptr->next != NULL) {
			Ptr = Ptr->next;
		}
		Ptr->next = newItem; //Links the last item in the list to the newly created item that n is pointing to
	}
}

//PRINTS ALL HASH TABLE & CREATES OUTPUT FILE
//@param N/A
//@return N/A
void hash::printAllIndex() {
	ofstream file_; //file declaration
	file_.open("fullTable.txt", ios::out); //file name

	for (int i = 0; i < tableSize; i++) {
		itemA *Ptr = HashTableA[i];
		if (Ptr->patA == "empty") {
			//cout << "index: " << i << " is Empty!" << endl;
		}
		else {
			while (Ptr != NULL) {

				//***
				//cout << Ptr->patA << " " << Ptr->encA<< endl;
				file_ << Ptr->patA << " " << Ptr->encA << endl;
				Ptr = Ptr->next;
			}
		}
	}
	file_.close(); //open and file, then CLOSE it
}

//CREATES HASH FOR THE KEY
//@param key is the value to be hashed
//@return the index in the hash table.
int hash::Hash(string key) {
	int hash = 0;
	int index;

	for (unsigned i = 0; i < key.length(); i++) {
		hash = hash + (int) key[i];
	}
	index = hash % tableSize;
	return index;
}

//CONVERT PATTERN TO ENCODED TEXT
//@param pattern is a single pattern to be checked on the table
//@return encoded is a single pattern encoded text returned from the hashtable
string hash::Patn_TO_Enct(string pattern) {
	int index = Hash(pattern);
	bool foundPATN = false;
	string encoded = "";

	itemA *Ptr = HashTableA[index];
	while (Ptr != NULL) {		//POINTING TO SOME ITEM
		if (Ptr->patA == pattern) {
			foundPATN = true;
			encoded = Ptr->encA;
		}
		Ptr = Ptr->next;
	}
	if (foundPATN) {
		return encoded;
	}
	return 0;
}

//CONVERT ENCODED TEXT TO PATTERN
//@param encoded is a single encoded text to check on table
//@return pattern is a single pattern returned from the hashtable
string hash::Enct_TO_Patn(string encoded) {
	int index = Hash(encoded);
	bool foundENCT = false;
	string pattern= "";

	itemB *Ptr2 = HashTableB[index];
	while (Ptr2 != NULL) {		//POINTING TO SOME ITEM
		if (Ptr2->encB == encoded) {
			foundENCT = true;
			pattern = Ptr2->patB;
		}
		Ptr2 = Ptr2->next;
	}
	if (foundENCT) {
		return pattern;
	}
	return 0;
}

//DECODES ENCODED TEXT TO PATTERN
//@param text is the entire string to be decoded.
//@returns decoded  is the decoded string.
string hash::decoder(string text) {
	string decoded = "";
	for (unsigned i = 0; i < text.length(); i++) {
		string strPair = text.substr(i, 1);
		decoded = decoded + Enct_TO_Patn(strPair);
	}
	return decoded;
}

//ENCODES PATTERN TO ENCODED TEXT.
//@param text is the entire string to be encoded.
//@returns encoded  is the encoded string.
string hash::encoder(string text) {
	string encoded = "";
	for (unsigned i = 0; i < text.length(); i = i + 2) {
		string strPair = text.substr(i, 2);
		encoded = encoded + Patn_TO_Enct(strPair);
	}
	return encoded;
}

//string hash::createTable() {
//	ifstream file("fullTable.txt");
//	string text = "";
//	while (getline(file, text)) {
//	}
//	return text;
//}

//SELECT A METHOD OF INPUT
//@param N/A
//@returns string from a method of input
string hash::input() {
	int input_option = 0;
	string txt = "";
	cout << "ENTER METHOD OF INPUT: ";
	cout << "(1)KEYBOARD | (2) TEXT file | (3) SAVED SENTENCE | (4) EXIT || YOUR CHOICE: ";
	cin >> input_option;

	if (input_option == 1) {
		cin.ignore();
		cout << "Enter a string" << endl;
		getline(cin, txt);
		return txt;
	}

	else if (input_option == 2) {
		ifstream file("name.txt");
		string text = "";
		while (getline(file, text)) {
		}
		return text;
	}

	else if (input_option == 3) {
		txt = "6Lorem_Ipsum_is_simply_dummy_text_of_the_printing_and_type_setting_industry.";
		return txt;
	}

	else if (input_option == 4) {
		cout << "EXITING" << endl;
		exit(1);
	} else
		cout << "INVALID INPUT" << endl;
	input();
	return txt;
}

//CHECK DUPLICATES (If found dont add to hash table)
//@param pattern is the pattern to be checked to the hashtable A
//@return True if exist, False if doesn't
bool hash::FindENCT(string pattern) {
	int index = Hash(pattern);
	bool foundPATN = false;
	string encoded = "";

	itemA *Ptr = HashTableA[index];
	while (Ptr != NULL) {
		if (Ptr->patA == pattern) {
			foundPATN = true;
			encoded = Ptr->encA;
		}
		Ptr = Ptr->next;
	}
	if (foundPATN) {
		return true;
	} else {
		return false;
	}
}

int main() {
	cout << "THIS IS PATTERN ENCODING!" << endl;
	hash Hashy;

	int input_option = 0;
	string txt = "";
	cout << "WHAT DO YOU WANT TO DO?" << endl;
	cout << "(1)DEMO on THIS COMPUTER | (2) DECODE ON NEW COMPUTER"
			<< " || YOUR CHOICE: ";
	cin >> input_option;

	if (input_option == 1) {
		cout << "-------------" << endl;
		cout << "THIS IS DEMO!" << endl;
		string text = Hashy.input();
		Hashy.addAll(text);
		Hashy.printAllIndex();

		cout << "ORIGINAL STRING: " << text << endl;

		string returnString = Hashy.encoder(text);
		cout << " ENCODED STRING: " << returnString << endl;

		string returnString2 = Hashy.decoder(returnString);
		cout << " DECODED STRING: " << returnString2 << endl;
	}

	else if (input_option == 2) {
		cout << "-------------------------" << endl;
		cout << "DECODING IN NEW COMPUTER!" << endl;
		string decoding = "";
		cout << "Enter the message to be decoded: " << endl;
		cout << "ENCODED STRING: ";
		cin >> decoding;
		//Hashy.createTable();

		//string line_;
		ifstream file_("fullTable.txt");
		string encoded = "";
		string pattern = "";

		if (file_.is_open()) {
			while ((file_ >> pattern >> encoded)) {//reads file line by line, storing each variable values.
				Hashy.AddItemA(pattern, encoded);
				Hashy.AddItemB(pattern, encoded);
			}
			file_.close();
		} else
			std::cout << "File is not open. " << endl;

		Hashy.printAllIndex();	//NEEDED TO WRITE TO FILE.
		std::cin.get();
		string returnString2 = Hashy.decoder(decoding);
		cout << "DECODED STRING: " << returnString2 << endl;
		return 0;
	}

	else
		cout << "INVALID INPUT" << endl;

	return 0;

}

