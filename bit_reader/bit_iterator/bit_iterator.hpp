#include <iostream>
#include <bitset>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class bit_iterator
{
private:
	std::ifstream &stream;
	int bitCount = 8, countString = 1, flag = 0;
	int byte[8];

public:
	bit_iterator(std::ifstream &p) :stream(p) {}
	~bit_iterator(){}
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
			}

		}
	}


	void readBitFast()
	{
		char ch;
		stream.seekg(countString, ios::beg);
		stream.get(ch);

		if (stream.eof()) flag = -1;
		else
			{
				int charNumber = abs((int)ch);
				for (int j = 0; j <= 7; ++j)
				{
					byte[j] = (charNumber & 0x1);
					charNumber >>= 1;
				}
				countString++;
		        }
	
	}

};
