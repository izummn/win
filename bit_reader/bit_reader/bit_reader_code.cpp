#include <bit_iterator.hpp>
#include <fstream>
#include <iostream>
#include <bitset>
#include <stdint.h>
#include <vector>
#include <list>
#include <array>
#include <iterator>
#include <iomanip>

using namespace std;
const int nBits = 32;

int main()
{
	std::vector<int> v{ { 45, -12, 33, 48, 23, 58, -89 } };
	 bit_iterator<decltype(v.begin())> first(v.begin());
	 bit_iterator<decltype(v.end())> last(v.end());
	std::copy(first, last, std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
	return 0;

}

