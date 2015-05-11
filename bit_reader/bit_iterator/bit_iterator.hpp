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
	
	int bitCount = 0;
	Iterator iter;

public:
	bit_iterator(Iterator it) : iter(it) {}
	bit_iterator& operator++()
	{
		if (bitCount == 8)
		{
			++iter;
			bitCount = 0;
		//	std::cout << std::endl;
		}
		return *this;
	}	
	bool operator==(const bit_iterator& rhs) { return iter == rhs.iter; }
	bool operator!=(const bit_iterator& rhs) { return iter != rhs.iter; }
	bool operator<(const bit_iterator& rsh)  { return iter < rsh.iter; }
	typename bit_iterator::value_type operator * ()
	{ 
		return (*iter >> (bitCount++)) & 0x1 ;
	};
	~bit_iterator(){}	
};



