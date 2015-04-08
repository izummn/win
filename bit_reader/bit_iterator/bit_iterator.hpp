#include <iostream>
#include <bitset>
#include <fstream>
#include <sstream>

class bit_iterator
{
	std::ifstream thread;

public:

	bit_iterator(std::string fileName)					//�����������, � ��� ����������� ����. 
	{
		thread.open(fileName, std::ios::binary);
	};

	~bit_iterator()							// ����������. ����� ��? ��� ��������� ��������� ����.
	{
		thread.close();
	}									


	int readBitFast()						//����� ���������� ����� �������� & 0x1, ����� ���� ������� �� ������� �����. ����� ���������������.
	{
		int dec = readByte();
		if (dec == -1) return -1;
		else
			for (int j = 0; j < 8; ++j)
			{
				return (dec & 0x1);
				dec >>= 1;
			}
	};


	int readBitFor()							//����� ���������� ���������� ����� ���� for(;;), �� ���� ��������� ������������.
												//����� � �� ���� ��������� ��� ���������� �����: �� ������� ��� � ������� ���? 
	{												//(���� �� ���������� - �������� ������� ��� �� �����, ������� ��� readBitFast(), �� �������.)
		int byte[8] = { 0, 0, 0, 0, 0, 0, 0, 0 }; 
		int dec = readByte();
		if (dec == -1) return -1;
		else
			for (int j = 7; j >= 0; j--)
			{
				byte[j] = dec % 2;
				return byte[j];
				dec >>= 1;
			}
	}


	int readBitBitset()									//����� ���� �� ������� �����.
	{
		int dec = readByte();
		int k = 0;
		if (dec == -1) return -1;
		else
		{
			std::bitset<8> byte(dec);
			for (int i = 0; i < 8; i++)
				return byte[i];
		
		};
	}





	int readByte()							//�������, ������� ������� ���������� ������.
	{
		char ch;
		thread.exceptions(std::ifstream::badbit);
		try {
			while (!thread.eof())
			{
				thread.get(ch);
				return abs((int)ch);
			}
			return -1;
		}
		catch (std::ifstream::failure &e)
		{
			std::cout << "Exception opening/reading/closing file\n";
		}
	};
};
