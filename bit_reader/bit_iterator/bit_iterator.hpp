#include <iostream>
#include <fstream>
#include <array>
#include <iterator>
#include <vector>

template<class Iterator>
class bit_iterator :
	public std::iterator<
	typename std::iterator_traits<Iterator>::iterator_category,
	int>
{
private:
	
	int bitCount = 8;
	std::array <int, 8> byte;
	Iterator iter;


public:

	bit_iterator& operator++()
	{
		if (bit_count == 8 * sizeof(iter))
		++iter;
		return *this;
	}
	
	bool operator==(const bit_iterator& rhs) { return iter == rhs.iter; }
	bool operator!=(const bit_iterator& rhs) { return iter != rhs.iter; }
	int operator*() const { return (*iter >> bit_count) & 0x1; }
	~bit_iterator(){}

	template <class Container>
	bit_iterator operator=(Container p) { return iter = p.begin(); }



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



