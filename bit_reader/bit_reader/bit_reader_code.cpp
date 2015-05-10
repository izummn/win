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
	
	

	std::vector<double> v{ { 7, 8.1, 3.9, -48.6 } };
	bit_iterator first = v.begin();
	bit_iterator last = v.end();

	//bit_iterator<double> first = v.begin();
	//bit_iterator <double> last = v.end();

	std::copy(first, last, std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	return 0;

}

