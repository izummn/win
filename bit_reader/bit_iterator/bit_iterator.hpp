#include <iostream>
#include <fstream>
#include <array>
#include <iterator>
#include <vector>

class bit_iterator : public std::iterator <std::input_iterator_tag, int>
{
private:
	//std::ifstream &stream;
	int bitCount = 8;
	std::array <int, 8> byte;
	std::vector<double>::iterator iter;
	double* p;


public:
	//bit_iterator(std::ifstream &p) :stream(p) {}

	bit_iterator(std::vector<double>::iterator _iter) : iter(_iter) {}
	bit_iterator(double* x) : p(x) {}

	bit_iterator& operator++()
	{
		++p;
		return *this;
	}

	bit_iterator operator++(int)
	{
		bit_iterator tmp(*this);
		operator++();
		return tmp;
	}

	bool operator==(const bit_iterator& rhs) { return p == rhs.p; }
	bool operator!=(const bit_iterator& rhs) { return p != rhs.p; }
	double& operator*() { return *p; }
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
		/*  stream.get(ch);
		if (stream.eof()) byte[0] = -1;
		else
		{
		int charNumber = (int)ch;
		for (int j = 7; j >= 0; j--)
		{
		byte[j] = (charNumber & 0x1);
		charNumber >>= 1;
		}
		}*/
	}

};



