#include <C:\Users\Марат\Documents\GitHub\win\bit_reader\bit_iterator\bit_iterator.hpp>;
#include <iostream>

int main()
{
	bit_iterator b("1.txt");							//долго думал, что передавать. очень много искал начет передачи потока, хотел уточнить
	int result;
	do 
		{
			//result = b.readBitFast();
			//result = b.readBitFor();               
			result = b.readBitBitset();				//наверное, самый крутой.
			std::cout << result;
		} while (result != -1);

	std::cout << std::endl;
	return 0;
}


