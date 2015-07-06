#include <iostream>
#include <fstream>
#include <array>
#include <iterator>
#include <vector>

using std::boolalpha;
template <class T>
class proxy {
	friend T;
private:
	T& p;
	bool val;
	proxy(T& v) : p(v) {}
	proxy(const proxy& v) :p(v.p), val(v.val){}

public:
	proxy& operator = (const proxy&) = default;
	operator bool() const 
	{
		proxy obj(*this);
		return obj.val; 
	}

	proxy& operator = (bool x) 
	{
		val = x;
		return *this; 
	}

	//~proxy();
};

	template <class oIterator>
	  class obit_iterator : public std::iterator < typename std::output_iterator_tag, proxy<obit_iterator<oIterator>> >
	{
	private:
		oIterator iter;
	public:
		obit_iterator(oIterator it) : iter(it) {}
		obit_iterator(const obit_iterator& obj) : iter(obj.iter) {}
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

		/*proxy<oIterator> operator*() //const
		{
			return proxy<decltype(*this)>(*this);
		}*/
		
		typename obit_iterator::value_type operator*() //const
		{
			return *this;
		}

		obit_iterator& operator = (const obit_iterator& obj)
		{
			iter = obj.iter;
			return *this;
		}

	};

