#include <bit_iterator.hpp>
#include <fstream>
#include <iostream>
#include <bitset>
#include <stdint.h>

using namespace std;

const int nBits = 32;



uint32_t swapEndianness(uint32_t bits)
{
	uint32_t resultBits = 0;
	std::bitset<nBits> temp(bits);
	std::bitset<nBits> result(resultBits);
	int k = 0;
	for (int i = 31; i >= 0; i--)
	{
		result[i % 8 + k] = temp[i];
		//std::cout << result[i] << " ddd ";
		if (i % 8 == 0)
		{
			k += 8;
			
		}
	}
	for (int i = 31; i >= 0; i--)
		std::cout << result[i] << "";
	std::cout << " ddd ";
	return resultBits;
}

int main(int argc, char *argv[])
{
	const std::bitset < nBits > manual("01001101011100110110000101100100");
	uint32_t d;
	d = 589966;


	if (argc < 2)
	{
		std::cout << "Enter file name!" << std::endl;
		exit(1);
	}
	string name(argv[1]);

	std::bitset < nBits > mm(d);
	std::cout << " bitset \n";
	std::cout << mm << " ones " << std::endl;
	std::cout << " bitset swwap \n";
	std::cout << swapEndianness(d) << " sss " << std::endl;
	



	ifstream f(name, ios::binary);
	f.exceptions(std::ifstream::badbit);
	try {
		bit_iterator b(f);
		int result;
		do
		{
			result = b.readBit();
			if (result == -1) break;
			cout << result;
		} while (result != -1);

		cout << endl;
		return 0;
	}

	catch (std::ifstream::failure &e)
	{
		std::cout << "Exception opening/reading/closing file\n";
	}


	

}