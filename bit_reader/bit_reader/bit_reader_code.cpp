#include <C:\Users\�����\Documents\GitHub\win\bit_reader\bit_iterator\bit_iterator.hpp>;
#include <iostream>

int main()
{
	bit_iterator b("1.txt");							//����� �����, ��� ����������. ����� ����� ����� ����� �������� ������, ����� ��������
	int result;
	do 
		{
			//result = b.readBitFast();
			//result = b.readBitFor();               
			result = b.readBitBitset();				//��������, ����� ������.
			std::cout << result;
		} while (result != -1);

	std::cout << std::endl;
	return 0;
}


