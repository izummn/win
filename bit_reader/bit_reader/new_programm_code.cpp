#include <iostream>
#include <bitset>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <time.h>



void decToBin(int dec)	// by for(;;)
{
	int byte[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	int j;

	for (j = 7; j >= 0; j--)
	{
		byte[j] = dec % 2;
		dec >>= 1;
	}

	for (j = 0; j <= 7; j++)
		std::cout << byte[j];
}

void decToBin2(int dec)    
{
	int j;

	for (j = 0; j < 8; j++)
	{
		std::cout << (dec & 0x1);
		dec >>= 1;
	}
}

void decToBinBitset(int dec)
{
	std::bitset<8> byte(dec);
	std::cout << byte << std::endl;
}



int main(int argc, char *argv[])
{
	int t = clock();
	char ch;

	if (argc < 2)
	{
		std::cout << "Enter file name!" << std::endl;
		exit(1);
	}
	std::string name(argv[1]);

	std::ifstream anyFile;
	anyFile.exceptions(std::ifstream::badbit);
	try {
		anyFile.open(name, std::ios::binary);
		
		while (!anyFile.eof())
		{
			anyFile.get(ch);
			std::cout << std::endl;
			std::cout << " char " << abs((int)ch) << std::endl;

			decToBin(abs((int)ch));       // by for(;;)

			std::cout << std::endl;
			decToBin2(abs((int)ch));     // by (dec & 0x1)

			std::cout << std::endl;
			std::cout << std::endl;
			
		}

	}
	catch (std::ifstream::failure &e)
	{
		std::cout << "Exception opening/reading/closing file\n";
	}

	std::cout << std::endl;
	std::cout << "Time " << clock() - t << std::endl;
	return 0;
}
