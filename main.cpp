#include <fstream>
#include <iostream>
#include <cmath>
#include <map>
#include <list>


#include "bencode.h"

char buffer[255];
int length;


/*//////////////////////*/
std::map<std::string, std::string> dict;
std::list<std::string> lst;
int integer;
char* byte_array;

char* key;
char* value;
char c;
int size = 0;
/*//////////////////////*/


int ASCII_to_int(char* c, int i);
void size_of(char* c, std::ifstream* file);
void decode(std::ifstream& file);
void check(char* c, std::ifstream* file);
//void find_field(char*);


int main()
{
	std::ifstream file("Torrent_test.torrent");
	decode(file);

	delete[] byte_array;
	return 0;
}

void decode(std::ifstream& file)
{
	while (!file.eof())
	{
		//integer
		if (c == 'i')
		{
			c = (char)file.get();
			check(&c, &file);
			while (c != 'e')
			{
				size_of(&c, &file);
				value = new char[length + 1];

				//Element of dictionary(key)
				for (uint16_t i = 0; i < length; i++)
				{
					value[i] = (char)file.get();
				}
				value[length] = 0;/*we set the terminating zero*/
				integer = ASCII_to_int(value, length);
				delete[] value;
				c = (char)file.get();
				decode(file);
			}
		}
		//list
		else if (c == 'l')
		{
			c = (char)file.get();
			check(&c, &file);
			while (c != 'e')
			{
				size_of(&c, &file);
				value = new char[length + 1];

				//Element of dictionary(key)
				for (uint16_t i = 0; i < length; i++)
				{
					value[i] = (char)file.get();
				}
				value[length] = 0;/*we set the terminating zero*/
				lst.push_back((const char*)value);

				delete[] value;
				c = (char)file.get();
				decode(file);
			}
		}
		//dictionary
		else if (c == 'd')
		{
			c = (char)file.get();
			check(&c, &file);
			while (c != 'e')
			{
				//Length of dict elem			/**************************/
				size_of(&c, &file);
				key = new char[length + 1];

				//Element of dictionary(key)
				for (uint16_t i = 0; i < length; i++)
				{
					key[i] = (char)file.get();
				}
				key[length] = 0;/*we set the terminating zero*/	/**************************/

				c = (char)file.get();
				size_of(&c, &file);
				value = new char[length + 1];

				//Element of dictionary(value)
				for (uint16_t i = 0; i < length; i++)
				{
					value[i] = (char)file.get();
				}
				value[length] = 0;/*we set the terminating zero*/

				dict[(const char*)key] = (const char*)value;

				delete[] key;
				delete[] value;
				
				c = (char)file.get();
				
				decode(file);
			}
		}
		//byte array
		if ((int)c >= 48 && (int)c <= 57)
		{
			while (c != 'e')
			{
				size_of(&c, &file);
				value = new char[length + 1];

				//Element of dictionary(key)
				for (uint16_t i = 0; i < length; i++)
				{
					value[i] = (char)file.get();
				}
				value[length] = 0;/*we set the terminating zero*/
				byte_array = value;
				delete[] value;
				c = (char)file.get();
				decode(file);
			}
		}
		if (c == 'e')
		{
			c = (char)file.get();
			return;
		}
		c = (char)file.get();
	}
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
void size_of(char* c, std::ifstream* file)
{
	int size = 0;
	while (*c != ':')
	{
		check(c, file);
		buffer[size] = *c;
		size++;
		*c = (char)(*file).get();
	}
	length = ASCII_to_int(buffer, size);
}

void check(char* c, std::ifstream* file)
{
	if (*c == 'l' ||
		*c == 'd' ||
		*c == 'i')
	{
		decode(*file);
	}
}