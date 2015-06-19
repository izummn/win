#include <iostream>
#include <fstream>
#include <array>
#include <iterator>
#include <vector>

template <class oIterator>
class obit_iterator : public std::iterator <typename std::output_iterator_tag, bool>

{
private:
	oIterator iter;
public:
	obit_iterator(oIterator it) : iter(it) {}
	obit_iterator(bool it) { *iter = it; }
	obit_iterator() {}
	~obit_iterator() {}

	obit_iterator& operator++() 
	{
		++iter;
		return *this;
	}

	obit_iterator operator++(int)
	{
		obit_iterator temp(*this);
		iter++;
		return temp;
	}

	bool operator==(const obit_iterator& rhs) const { return (iter == rhs.iter); }

	bool operator!=(const obit_iterator& rhs) const { return !(*this == rhs); }

	obit_iterator operator*() const
	{
		return *this;
	};

	obit_iterator& operator = (bool it)
	{
		*iter = it;
		return *this;
	}

};