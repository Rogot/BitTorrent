#include <iostream>

#include "bencode.h"

char buffer[255];
int length;

namespace Core
{
	namespace Util
	{
		/*
		* Проверка того, что компьютер
		* работает на Little Endian, а не на Big Endian
		*/
		bool isLittleEndian()
		{
			// 0x00 0x00 0x00 0b0000 0101 - 5
			int8_t a = 5;
			std::string result = std::bitset<8>(a).to_string();
			if (result.back() == '1') return true;
		}
	}
}


//Discription

be_node::be_node()
	:
	type(be_type::BE_NAN) {}

be_node::~be_node()
{

}

#if 1
/*
* Func: convert ASCII value to int
* Patams: c - array of signs in ASCII format
		  size - number of digits
*/
int be_node::ASCII_to_int(char* c, int size)
{
	int l = 0;
	for (int i = 0; i < size; i++)
	{
		l += ((int)c[i] - 48) * (int)pow(10, size - (i + 1));
	}
	return l;
}

/*
* This function to let to know the length of next information
*
* It "read" file until it reaches sign ":" and convert ASCII sign to int value
*/
void be_node::size_of(char c, std::ifstream* file)
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
#endif

void be_node::decode(std::ifstream file)
{
	char c;
	c = (char)file.get();
	if (c == 'i')
	{

	}
	else if (c == 'd')
	{

	}

	else if ((int)c >= 48 && (int)c <= 57)
	{

	}
}
