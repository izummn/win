#include <C:\Users\NADERSHIN\Documents\Visual Studio 2013\Projects\one\bit_iterator\bit_iterator.hpp>
#include <iostream>

int main()
{
	std::ifstream f("1.txt", ios::binary);
	bit_iterator b(f);						
	int result;
	do
	{            
		result = b.readBit();			
		std::cout << result;
	} while (result != -1);

	std::cout << std::endl;
	return 0;
}
