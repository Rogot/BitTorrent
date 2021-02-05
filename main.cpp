#include <fstream>
#include <iostream>
#include <cmath>
#include <map>

#include "bencode.h"

char buffer[255];
int length;
char* name;

int ASCII_to_int(char* c, int i);
void size_of(char c, std::ifstream* file);
//void find_field(char*);


int main()
{
	std::ifstream file("Torrent_test.torrent");
	std::map<char, char> dict;
	char* key;
	char* value;
	
	char c;
	int size = 0;
	while (!file.eof())
	{
		c = (char)file.get();
		if (c == 'i')
		{

		}

		else if (c == 'd')
		{
			c = (char)file.get();
			while (c != 'e')
			{
				//Length of dict elem
				size_of(c, &file);
				key = new char[length];

				//Element of dictionary(key)
				for (uint16_t i = 0; i < length; i++)
				{
					key[i] = (char)file.get();
				}

				c = (char)file.get();
				size_of(c, &file);
				value = new char[length];

				//Element of dictionary(value)
				for (uint16_t i = 0; i < length; i++)
				{
					value[i] = (char)file.get();
				}

				dict[*key] = *value;

				delete[] key;
				delete[] value;
				
				c = (char)file.get();
			}
		}

		if ((int)c >= 48 && (int)c <= 57)
		{
			size_of(c, &file);
		}
	}
	return 0;
}

/*
void find_field(char* buffer)
{
	for (uint8_t i = 0; i < Bencode::size_list; i++)
	{
		for (uint8_t j = 0; j < length; j++)
		{
			if (Bencode::param_list[i][j] == buffer[j])
			{
				if (Bencode::param_list[i].size() == j + 1)
				{
					printf("Ok!");
					Bencode::TorrentFile::set_num_field(i);
					return;
				}
			}

		}
	}
}
*/


int ASCII_to_int(char* c, int s)
{
	int l = 0;
	for (int i = 0; i < s; i++)
	{
		l += ((int)c[i] - 48) * (int)pow(10, s - (i + 1));
	}
	return l;
}


/*
* This function to let to know the length of next information
* 
* It "read" file until it reaches sign ":" and convert ASCII sign to int value
*/
void size_of(char c, std::ifstream* file)
{
	int size = 0;
	while (c != ':')
	{
		buffer[size] = c;
		size++;
		c = (char)(*file).get();
	}
	length = ASCII_to_int(buffer, size);
}