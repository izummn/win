#include <C:\Users\�����\Documents\GitHub\win\bit_reader\bit_iterator\bit_iterator.hpp>;
#include <iostream>

int main()
{
	int cache, i;
	std::ifstream f("1.txt");
	bit_iterator b(f);							//����� �����, ��� ����������. ����� ����� ����� ����� �������� ������, ����� ��������
	int result;
	do 
		{
			
			//result = b.readBitFast();
			//result = b.readBitFor();               
			result = b.readBit();				//��������, ����� ������.
			std::cout << result;
		} while (result != -1);

	std::cout << std::endl;
	return 0;
}


