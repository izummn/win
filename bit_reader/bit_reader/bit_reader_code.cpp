#include <bit_iterator.hpp>
#include <obit_iterator.hpp>
#include <fstream>
#include <iostream>
#include <bitset>
#include <stdint.h>
#include <vector>

using namespace std;
const int nBits = 64;

int main()
{
/*	std::vector<int> v{ { 45, -12, 33, -48, 23, 58, 89 } };
	std::copy(make_bit_iterator(v.begin()), make_bit_iterator(v.end()), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
	*/
	//std::vector<uint8_t> p;
	//obit_iterator<decltype(back_inserter(p))>  b(back_inserter(p));



	std::vector<uint8_t> p(4);
	std::vector<uint8_t>::iterator it(p.begin());

	obit_iterator<std::vector<uint8_t>::iterator>  b(it);

	*b = true;
	std::cout << " 1) " << *b << std::endl;
	b++;
	*b = false; 
	std::cout << " 2) " << *b << std::endl;
	b++;
	*b = true;
	std::cout << " 3) " << *b << std::endl;
	b++;
	*b = false;
	std::cout << " 4) " << *b << std::endl;

	/*for (int i = 0; i < 2; i++)
	{
		b++;
		*b = true;
		std::cout << i << ") " << *b << std::endl;;
	}*/
	

	 
	return 0;
}

