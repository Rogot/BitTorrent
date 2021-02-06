#pragma once
/*
* It is a C++  implementation of a bencode decoder.
* This is the format defined by BitTorrent.
*/


#include <string>
#include <bitset> // std::bitset
#include <assert.h>
#include <list>
#include <fstream>// std::fstream
#include <map>

enum class be_type {
	BE_NAN,		//NaN
	BE_STR,		//byte array
	BE_INT,		//integer
	BE_LIST,	//list 
	BE_DICT		//dictionary
};


class be_node {
private:
	be_type type;
	virtual union val {
		char* s;
		long long i;
		be_node** l;
		std::map<char*, char*> d;
	};

public:
	be_node();
	~be_node();
	void decode(std::ifstream);
	int ASCII_to_int(char*, int);
	void size_of(char, std::ifstream*);
};
