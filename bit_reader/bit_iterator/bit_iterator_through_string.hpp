#include <iostream>
#include <bitset>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
int bitCount = 8, countString = 0;
int byte[8] {0, 0, 0, 0, 0, 0, 0, 0};
int flag = 0;
string str;

class bit_iterator
{
	std::ifstream s;
	int charNumber;

public:
	
	bit_iterator(std::ifstream &stream) 
	{
		char ch;
		while (!stream.eof())
		{
			stream.get(ch);
			str = str + ch;
		};
	};

	~bit_iterator(){};

	int readBit()
	{
		if (flag == -1) return -1;

		else
		{
			
			if (bitCount <= 6)
			{
				bitCount++;
				return byte[bitCount];
				
			}
			else
			{
				readBitFast();
				bitCount = 0;
				return byte[0];
			};

		};
	};

	void readBitFast()						
	{
		if (countString == str.length()) flag = -1;
		charNumber = abs((int)str[countString]);
			for (int j = 0; j <= 7; ++j)
			{
				byte[j] = (charNumber & 0x1);
				charNumber >>= 1;
			}
		countString++;

	};

};
