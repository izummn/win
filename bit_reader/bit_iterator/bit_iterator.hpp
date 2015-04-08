#include <iostream>
#include <bitset>
#include <fstream>
#include <sstream>

class bit_iterator
{
	std::ifstream thread;

public:

	bit_iterator(std::string fileName)					//конструктор, в нем открывается файл. 
	{
		thread.open(fileName, std::ios::binary);
	};

	~bit_iterator()							// Деструктор. Нужен ли? тут корректно закрываем файл.
	{
		thread.close();
	}									


	int readBitFast()						//здесь считывание через операцию & 0x1, вывод идет начиная со старших битов. Более производительна.
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


	int readBitFor()							//здесь происходит считывание через цикл for(;;), не могу проверить правильность.
												//также я не могу проверить как происходит вывод: со старших или с младших бит? 
	{												//(судя по реализации - обратный порядок тут не делал, поэтому как readBitFast(), со старших.)
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


	int readBitBitset()									//вывод идет со старших битов.
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





	int readByte()							//функция, котороя достает конкретный символ.
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
