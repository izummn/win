#include <iostream>
#include <fstream>
#include <array>
#include <iterator>
#include <vector>


template<class Iterator>
class bit_iterator :
	public std::iterator <
	typename std::input_iterator_tag,
	int >
{
private:

	int bitCount = 0;
	Iterator iter;

public:
	bit_iterator(Iterator it) : iter(it) {}
	bit_iterator(){}

	bit_iterator(const bit_iterator& obj)	
	{	
		bitCount = obj.bitCount;
		iter = obj.iter; 
	}

	bit_iterator operator++(int)
	{
		bit_iterator result(*this);
		++(*this);
	//	iter++;
		return result;
	}


	bit_iterator& operator++()
	{
		bitCount++;
		if (bitCount == CHAR_BIT * sizeof(decltype(*iter)))
		{
			++iter;
			bitCount = 0;
		} 
		
		return *this;
	}


	bool operator==(const bit_iterator& rhs) const {return iter == rhs.iter;}

	bool operator!=(const bit_iterator& rhs) const {  return !(*this == rhs); }

	bit_iterator& operator=(const bit_iterator& obj)
	{
		bitCount = obj.bitCount;
		iter = obj.iter;
		return *this;
	}

	typename bit_iterator::value_type operator * () const
	{
		return (*iter >> bitCount) & 0x1;
	};

	~bit_iterator(){}

};

template<class iterator>
bit_iterator<iterator> make_bit_iterator(iterator it)
{
	bit_iterator<decltype(it)> obj(it);
	return obj;
};







