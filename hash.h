#ifndef HASH_H_
#define HASH_H_

#include <iostream>
#include <cstdlib>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

struct itemA {
	std::string patA;     //PATTERN
	std::string encA;     //ENCODED TEXT
	itemA *next;
};

struct itemB {
	std::string patB;     //PATTERN
	std::string encB;     //ENCODED TEXT
	itemB *next;
};

class hash {
	static const int tableSize = 10;				//HASH TABLE SIZE CAN BE CHANGED
	itemA *HashTableA[tableSize];     				//STORE PATTERN TO ENCODED TEXT
	itemB *HashTableB[tableSize];     				//STORE ENCODED TO PATTERN

public:
	hash();											//CONSTRUCTOR for HASHTABLE
	virtual ~hash();								//DESTRUCTOR for HASHTABLE
	void addAll(std::string text);					//ADDS THE GIVEN STRING TO BOTH HASHTABLEA & HASHTABLEB
	void AddItemA(string pattern, string encoded);	//ADDS ITEMS TO HASHTABLE A
	void AddItemB(string pattern, string encoded);	//ADDS ITEMS TO HASHTABLE B
	void printAllIndex();							//PRINTS ALL HASH TABLE & CREATES OUTPUT FILE
	int Hash(std::string key);						//CREATES HASH FOR THE KEY
	string Patn_TO_Enct(string pattern);			//CONVERT PATTERN TO ENCODED TEXT
	string Enct_TO_Patn(string encoded);			//CONVERT ENCODED TEXT TO PATTERN
	string decoder(string text);					//DECODES ENCODED TEXT TO PATTERN
	string encoder(string text);					//ENCODES PATTERN TO ENCODED TEXT.
	string input();									//SELECT A METHOD OF INPUT
	bool FindENCT(std::string PATN);				//CHECK DUPLICATES (If found dont add to hash table)
	//string createTable();
};

#endif
