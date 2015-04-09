#include <C:\Users\Марат\Documents\GitHub\win\bit_reader\bit_iterator\bit_iterator.hpp>;
#include <iostream>

int main()
{
	int cache, i;
	std::ifstream f("1.txt");
	bit_iterator b(f);							//долго думал, что передавать. очень много искал начет передачи потока, хотел уточнить
	int result;
	do 
		{
			
			//result = b.readBitFast();
			//result = b.readBitFor();               
			result = b.readBit();				//наверное, самый крутой.
			std::cout << result;
		} while (result != -1);

	std::cout << std::endl;
	return 0;
}


