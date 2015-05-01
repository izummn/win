//#include <bit_iterator.hpp>
#include <fstream>
#include <iostream>
#include <bitset>
#include <stdint.h>
#include <vector>
#include <list>
#include <array>

using namespace std;
const int nBits = 32;


template < typename T >
void reverseT(T first, T last)
{
	last--;
	while (first < last)
	{
		swap(*first, *last);
		first++;
		last--;
	}
}


template < typename T >
void showT(T first, T last)
{
	while (first != last)
	{
		cout << " " << *first;
		first++;		
	}
}



int main()
{
	cout << endl;

	std::vector<int> i{ 1, 2, 3, 4, 5, 6 };
	std::vector<double> d{ 7, 8.1, 3.9, -48.6, 8.5};
	std::vector<char> c{ 'j', 'f', 'g', 'h', 'k' };
	std::array<int, 8> a = { 1, 2, 3, 4, 5, 6, 7, 8 };
	std::list<int> l{ 20, 50, 5, 4, 3, 2 };

	cout << " Reverse and show int string: " << endl;
	showT(i.begin(), i.end());
	cout << "\n After: " << endl;
	reverseT(i.begin(), i.end());
	showT(i.begin(), i.end());
	cout << endl;
	cout << " *****************************************************" << endl;
	cout << endl;
	


	cout << " Reverse and show double string: " << endl;
	showT(d.begin(), d.end());
	cout << "\n After: " << endl;
	reverseT(d.begin(), d.end());
	showT(d.begin(), d.end());
	cout << endl;
	cout << " *****************************************************" << endl;
	cout << endl;


	cout << " Reverse and show char string: " << endl;
	showT(c.begin(), c.end());
	cout << "\n After: " << endl;
	reverseT(c.begin(), c.end());
	showT(c.begin(), c.end());
	cout << endl;
	cout << " *****************************************************" << endl;
	cout << endl;

	

	cout << " Reverse and show array: " << endl;
	showT(a.begin(), a.end());
	cout << "\n After: " << endl;
	reverseT(a.begin(), a.end());
	showT(a.begin(), a.end());
	cout << endl;
	cout << " *****************************************************" << endl;
	cout << endl;



	cout << " Reverse and show list container: " << endl;
	showT(l.begin(), l.end());
	cout << "\n After: " << endl;
//	reverseT(l.begin(), l.end());
	showT(l.begin(), l.end());
	cout << endl;
	cout << " *****************************************************" << endl;
	cout << endl;

	

	/*std::vector<double> v{ { 7, 8.1, 3.9, -48.6 } };
	bit_iterator first = v.begin();
	bit_iterator last = v.end();
	std::copy(first, last, std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;*/

	return 0;

}

