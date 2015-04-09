#include <iostream>
#include <bitset>
#include <fstream>
#include <sstream>

using namespace std;
int bitCount = 0;
int byte[8] {0, 0, 0, 0, 0, 0, 0, 0};
int flag = 0;
class bit_iterator
{
	//std::ifstream thread;
	int charNumber;



public:

	bit_iterator(std::ifstream &stream)					//�����������, � ��� ����������� ����. 
	{
		char ch;
		/*stream.get(ch);
		charNumber = (int)ch;*/
		
		while (!stream.eof())
		{
			stream.get(ch);
			
			charNumber = (int)ch;
			readBitFast();

			cout << " flagg " << (int)ch;
		}
		// flag = -1;



	};

	~bit_iterator()							// ����������. ����� ��? ��� ��������� ��������� ����.
	{
	}



	int readBit()
	{
		//cout << " flagg ";
		if (flag == -1) return -1;

		else 
		{
			bitCount++;
			if (bitCount <= 7) return byte[bitCount];
			else readBitFast();
		};

	}

	
	int readBitFast()						//����� ���������� ����� �������� & 0x1, ����� ���� ������� �� ������� �����. ����� ���������������.
	{
		if (flag == -1) return -1;
		else
			for (int j = 0; j < 8; ++j)
			{
				byte[j] = (charNumber & 0x1);
				charNumber >>= 1;
			}
	};

};



/*	int readBitFor()							//����� ���������� ���������� ����� ���� for(;;), �� ���� ��������� ������������.
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

	*/
/*	int readBitBitset()									//����� ���� �� ������� �����.
	{
		int k = 0;
		if (charNumber == -1) return -1;
		else
		{
			std::bitset<8> byte(charNumber);
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
*/