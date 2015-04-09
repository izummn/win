#include <iostream>
#include <bitset>
#include <fstream>
#include <sstream>

using namespace std;
int bitCount = 8;
int byte[8] {0, 0, 0, 0, 0, 0, 0, 0};
int flag = 0;

class bit_iterator
{
	std::ifstream s;
	int charNumber;

public:
	bit_iterator(std::ifstream &stream) 
	{
		s = stream;   //copy stream!
	};

	~bit_iterator()				
	{
	};

	int readBit()
	{
		if (flag == -1) return -1;

		else
		{
			
			if (bitCount <= 7)
			{
				return byte[bitCount];
				bitCount++;
			}
			else
			{
				readBitFast();
				bitCount = 0;
			};

		};
	};

	void readBitFast()						
	{
		char ch;
		while (!s.eof())
		{
			s.get(ch);
			charNumber = abs((int)ch);
			for (int j = 0; j < 8; ++j)
			{
				byte[j] = (charNumber & 0x1);
				charNumber >>= 1;
			}
		}
		flag = -1;
	};

};
