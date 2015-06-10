#include <bit_iterator.hpp>
#include <fstream>
#include <iostream>
#include <bitset>
#include <stdint.h>
#include <vector>

using namespace std;
const int nBits = 64;

int main()
{
	std::vector<int> v{ { 45, -12, 33, -48, 23, 58, 89 } };
	std::copy(make_bit_iterator(v.begin()), make_bit_iterator(v.end()), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
	return 0;
}

