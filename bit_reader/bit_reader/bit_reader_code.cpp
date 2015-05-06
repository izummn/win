//#include <bit_iterator.hpp>
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


template < typename T >
void reverseT(T first, T last)
{
	while (first != last)
	{
		last--;
		if (first == last) break;
		swap(*first, *last);	
		first++;
				
	}
}


template < class T, class ShowType = typename iterator_traits<T>::value_type >
void showT(T first, T last)
{
	std::copy(first, last, std::ostream_iterator<ShowType>(std::cout, " "));
}


template<class T, class ShowType = typename iterator_traits<T>::value_type>
ostream &operator<<(ostream &out, const pair<T, T>& p)
{
	copy(p.first, p.second, std::ostream_iterator<ShowType>(out, " "));
	return out;
}

template<class T>
void show(T first, T last)
{
	while (first != last)
	{
		cout << *first << " ";
		first++;
	}
}
//***********************************************************************************

/*template<class show_container_t> class show_container1 {
private:

public:
	friend ostream& operator<<(ostream&, const show_container1<show_container_t>&);
};


template<class ContainerType>
ostream& operator<<(ostream& out, const show_container1<ContainerType>& sc)
	{
		copy(sc.first, sc.second, std::ostream_iterator<double>(out, " "));
		return out;
	}


template<class show_container_t, class T>
pair<T, T> show_container(show_container_t container)
{
	return make_pair(container.begin(), container.end());
}
*/
//***************************************************************


int main()
{
	cout << endl;

	std::vector<int> i{ 1, 2, 3, 4, 5};
	std::vector<double> d{ 7, 8.1, 3.9, -48.6, 8.5};
	std::vector<char> c{ 'j', 'f', 'g', 'h', 'k' };
	std::array<int, 9> a = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::list<int> l{ 20, 50, 5, 4, 3, 9 };
	std::vector<int> empty{};


	cout << "Empty vector: " << endl;
	reverseT(empty.begin(), empty.end());
	cout << make_pair(empty.begin(), empty.end()) << endl;
	show(empty.begin(), empty.end());


	cout << " Reverse and show int string: " << endl;
	showT(i.begin(), i.end());
	cout << "\n After: " << endl;
	reverseT(i.begin(), i.end());
	showT(i.begin(), i.end());
	cout << endl;
	cout << make_pair(i.begin(), i.end()) << endl;
	cout << " *****************************************************" << endl;
	cout << endl;
	show(i.begin(), i.end());



	


	cout << " Reverse and show double string: " << endl;
	showT(d.begin(), d.end());
	cout << "\n After: " << endl;
	reverseT(d.begin(), d.end());
	showT(d.begin(), d.end());
	cout << endl;
	cout << make_pair(d.begin(), d.end()) << endl;
	cout << " *****************************************************" << endl;
	cout << endl;


	cout << " Reverse and show char string: " << endl;
	showT(c.begin(), c.end());
	cout << "\n After: " << endl;
	reverseT(c.begin(), c.end());
	showT(c.begin(), c.end());
	cout << endl;
	cout << make_pair(c.begin(), c.end()) << endl;

	cout << " *****************************************************" << endl;
	cout << endl;

	

	cout << " Reverse and show array: " << endl;
	showT(a.begin(), a.end());
	cout << "\n After: " << endl;
	reverseT(a.begin(), a.end());
	showT(a.begin(), a.end());
	cout << endl;
	cout << make_pair(a.begin(), a.end()) << endl;

	cout << " *****************************************************" << endl;
	cout << endl;



	cout << " Reverse and show list container: " << endl;
	showT(l.begin(), l.end());
	cout << "\n After: " << endl;
	reverseT(l.begin(), l.end());
	showT(l.begin(), l.end());
	cout << endl;
	cout << make_pair(l.begin(), l.end()) << endl;
	show(l.begin(), l.end());
	cout << " *****************************************************" << endl;
	cout << endl;

	

	/*std::vector<double> v{ { 7, 8.1, 3.9, -48.6 } };
	bit_iterator first = v.begin();
	bit_iterator last = v.end();
	std::copy(first, last, std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;*/

	return 0;

}

