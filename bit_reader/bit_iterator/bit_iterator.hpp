#include <iostream>
#include <fstream>
#include <array>
#include <iterator>
#include <vector>

template<class Iterator>
class bit_iterator :
	public std::iterator<typename std::iterator_traits<Iterator>::iterator_category, int>
{
private:
	int bitCount = 8;
	std::array <int, 8> byte;
	Iterator iter;


public:


	

	bit_iterator& operator++()
	{
		
		++iter;
		return *this;
	}

	/*bit_iterator operator++(iter)
	{
		bit_iterator tmp(*this);
		operator++();
		return tmp;
	}*/

	bool operator==(const bit_iterator& rhs) { return iter == rhs.iter; }
	bool operator!=(const bit_iterator& rhs) { return iter != rhs.iter; }
	int operator*() const { return (*iter » bit_count) & 0x1; }
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



