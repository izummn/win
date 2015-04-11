#include <C:\Users\Марат\Documents\GitHub\win\bit_reader\bit_iterator\bit_iterator.hpp>
#include <iostream>
using namespace std;


int main()
{
	std::ifstream f("1.txt", ios::binary);
	bit_iterator b(f);
	int result;
	do
	{
		result = b.readBit();
		cout << result;
	} while (result != -1);

	cout << endl;
	return 0;
}