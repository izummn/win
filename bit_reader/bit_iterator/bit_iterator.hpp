#include <iostream>
#include <fstream>
#include <array>

class bit_iterator
{
private:
	std::ifstream &stream;
	int bitCount = 8, flag = 0;
	std::array <int, 8> byte = {};

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
				if (flag == -1) return -1;
				bitCount = 0;
				return byte[0];
			}
	}


	void readBitFast()				//The conclusion from the lower bits
	{
		char ch;
		stream.get(ch);
		
		//std::cout << "  ch: " << ch << "   int: " << abs((int)ch);

		if (stream.eof()) flag = -1;
		else
		{
			int charNumber = (int)ch;
			for (int j = 7; j >= 0; j--)
			{
				byte[j] = (charNumber & 0x1);
			//	std::cout << "  charNumber= " << charNumber << "  " << " j= " << j;
				charNumber >>= 1;
			}
			std::cout << std::endl;

		//	std::cout << "   byte: ";
		//	for (int j = 0; j <= 7; j++)
		//		std::cout << byte[j];
			std::cout << std::endl;
		}

	}

};