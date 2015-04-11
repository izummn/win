#include <iostream>
#include <fstream>
#include <array>

using namespace std;

class bit_iterator
{
private:
	std::ifstream &stream;
	int bitCount = 8, flag = 0;
	array <int, 8> byte = {};

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


	void readBitFast()				//The conclusion from the lower bits
	{
		char ch;
		stream.get(ch);
		if (stream.eof()) flag = -1;
		else
		{
			int charNumber = abs((int)ch);
			for (int j = 7; j >= 0; j--)
			{
				byte[j] = (charNumber & 0x1);
				charNumber >>= 1;
			}
		}

	}

};