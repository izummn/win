#include <iostream>
#include <fstream>
#include <array>
#include <iterator>
#include <vector>



// template <class oIter>
class proxy {
private:
	//obit_iterator<??> p;
	proxy() {}
	//proxy(const obit_iterator& v) : proxy(v) {}
	proxy(const proxy& v) {}
public:
	
	proxy& operator = (const proxy&);
	operator bool() const;
	~proxy();
	proxy& operator = (bool x);
};




template <class oIterator>
class obit_iterator : public std::iterator <typename std::output_iterator_tag, proxy>

{
private:
	oIterator iter;
public:
	obit_iterator(oIterator it) : iter(it) {}
	obit_iterator(const obit_iterator& obj) { iter = obj.iter; }
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

	proxy operator*() //const
	{
		proxy p(*this);
		return p;
	}

	obit_iterator& operator = (const obit_iterator& obj)
	{
		iter = obj.iter;
		return *this;
	}

};


