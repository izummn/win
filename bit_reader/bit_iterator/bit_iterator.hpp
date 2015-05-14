#include <iostream>
#include <fstream>
#include <array>
#include <iterator>
#include <vector>


template<class Iterator>
class bit_iterator :
	public std::iterator<
	typename std::input_iterator_tag,
	int>
{
private:
	
	int bitCount = 0;
	Iterator iter;

public:
	bit_iterator(Iterator it) : iter(it) {}
	bit_iterator() {}
	bit_iterator& operator++()
	{
		bitCount++;
		if (bitCount == (std::numeric_limits<unsigned int>::digits) * sizeof(decltype(*iter)))
		{
			++iter;
			bitCount = 0;
			std::cout << std::endl;
		}		
		return *this;
	}	
	bool operator==(const bit_iterator& rhs) const { return iter == rhs.iter; }
	bool operator!=(const bit_iterator& rhs) const { return !(iter == rhs.iter); }
	Iterator *operator=(Iterator *rsh) { return iter(rsh); }
	typename bit_iterator::value_type operator * () const
	{ 
		return (*iter >> bitCount) & 0x1 ;
	};

	~bit_iterator(){}	
};



