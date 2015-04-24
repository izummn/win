#include <iostream>
#include <fstream>
#include <array>
#include <iterator>

class bit_iterator : public std::iterator<std::input_iterator_tag, int>
{
private:
	std::ifstream &stream;
	int bitCount = 8;
	std::array <int, 8> byte;

public:

	bit_iterator(std::ifstream &p) :stream(p) {}
	~bit_iterator(){}

	int readBit()
	{
		if (bitCount <= 6)
		{
			bitCount++;
			return byte[bitCount];
		}
		else
		{
			readBitFast();
			if (byte[0] == -1)
			{
				return -1;
			}
			else
			{
				bitCount = 0;
				return byte[0];
			}
		}
	}


	void readBitFast()				//The conclusion from the lower bits
	{
		char ch;
		stream.get(ch);
		if (stream.eof()) byte[0] = -1;
		else
		{
			int charNumber = (int)ch;
			for (int j = 7; j >= 0; j--)
			{				
				byte[j] = (charNumber & 0x1);
				charNumber >>= 1;
			}
		}
	}

};