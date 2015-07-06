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
	std::vector<int> v{ { 45, -12, 33, -48, 23, 58, 89 } };
	std::copy(make_bit_iterator(v.begin()), make_bit_iterator(v.end()), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	std::vector<int> p;
	obit_iterator<decltype(back_inserter(p))>  b(back_inserter(p));

	//proxy p(b); // это возвращает *b
	//p = false;
	//*b++ = false;
	 *b = true;
	 std::cout << "  " << *b;
	 b++;
	 *b = false;
	 std::cout << " " << *b;

	/* for (int i = 0; i < p.size(); i++)
		 std::cout << p[i] << " p ";*/

	/*vector<int> l{ { 0, 7 } };
	auto it = l.begin() + 1;
	*it = 9;
	obit_iterator<decltype(back_inserter(l))>  x(back_inserter(l));
	// l == {{ 0, 9 }}
	x++;
	for (int i = 0; i < l.size(); i++)
		std::cout << l[i] << " l ";*/
	 
	return 0;
}

