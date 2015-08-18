#include <iostream>
#include <fstream>
#include <array>
#include <iterator>
#include <vector>
#include <string>




template <class T>
class proxy {
	friend T;
private:
	T& p;
	proxy(T& v) : p(v) {}
	proxy(const proxy& v) :p(v.p) {}

public:
	proxy& operator = (const proxy&) = default;
	proxy& operator = (bool x)
	{	
		p.set_current_bit(x);
		return *this; 
	}
	~proxy(){};

};

	template <class oIterator>
	  class obit_iterator : public std::iterator < typename std::output_iterator_tag, proxy<obit_iterator<oIterator>> >
	{
	private:
		oIterator iter;

		int bitCount = 0;
		typename oIterator::value_type cached;
	//	oIterator* cached;
	

	public:
		obit_iterator(oIterator it) : iter(it) {}
		obit_iterator(const obit_iterator& obj) : iter(obj.iter), bitCount(obj.bitCount){}			//, cached(obj.cached) {}
		obit_iterator() {}
		~obit_iterator() {}

		obit_iterator& operator++()
		{
			bitCount++;
			
			if (bitCount == CHAR_BIT * sizeof(decltype(*iter)))
			{
			
				*iter++ = cached;
				
				//	cached = 0;          //clear cache
				//  old 
				//++iter;
			
				//std::cout << " bitCount " << bitCount << std::endl;
				bitCount = 0;

			

			}
			return *this;

		}

		obit_iterator operator++(int)
		{
			obit_iterator temp(*this);
			++(*this);
			return temp;
		}

		bool operator==(const obit_iterator& rhs) const { return (iter == rhs.iter) || (cached == rsh.cached); }
		bool operator!=(const obit_iterator& rhs) const { return !(*this == rhs); }
		bool operator|=(obit_iterator& rhs) { return  (iter |= rsh.iter) || (cached |= rsh.cached); }
	    
		void set_current_bit(bool b)
		{
			
			cached |= ( b << bitCount);		
			 
			//  old  //  
			//*iter |= b << bitCount;

			//std::cout << " cached = " << cached;// << std::endl;
		};

		bool get_current_bit() const
		{
			return *iter;
		};

		obit_iterator operator+=(int v)
		{
			for (int i(0); i < v; i++)
				(*this)++;
			return *this;
		}
	
		typename obit_iterator::value_type operator*() //const
		{
			return *this;
		}

		obit_iterator& operator = (const obit_iterator& obj)
		{
			iter = obj.iter;
			bitCount = obj.bitCount;
			cached = obj.cached;
			return *this;
		}

	};

