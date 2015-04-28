#include <bit_iterator.hpp>
#include <fstream>
#include <iostream>
#include <bitset>
#include <stdint.h>
#include <vector>

using namespace std;

const int nBits = 32;

int main()
{

	std::vector<double> v{ { 7, 8.1, 3.9, -48.6 } };
	bit_iterator first = v.begin();
	bit_iterator last = v.end();
	std::copy(first, last, std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
	return 0;

}

