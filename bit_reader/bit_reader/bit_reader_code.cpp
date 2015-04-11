#include <C:\Users\�����\Documents\GitHub\win\bit_reader\bit_iterator\bit_iterator.hpp>
#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "Enter file name!" << std::endl;
		exit(1);
	}
	string name(argv[1]);

	ifstream f(name, ios::binary);
	f.exceptions(std::ifstream::badbit);
	try {
		bit_iterator b(f);
		int result;
		do
		{
		    result = b.readBit();
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