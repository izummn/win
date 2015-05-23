#define CATCH_CONFIG_MAIN
#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include <bit_iterator.hpp>
#include <boost/filesystem.hpp>
#include <catch.hpp>
#include <algorithm>



const int nBits = 64;

const std::bitset < nBits > manual("1011100110110000101100100");
const std::bitset < nBits > ones(std::numeric_limits<uint32_t>::max());
const std::bitset < nBits > zeros;
const std::bitset < nBits > randoms(std::rand());

class temprorary_filename
{
private:
	std::string path;
public:
	temprorary_filename()
	{
		path = boost::filesystem::unique_path().string();
	}
	~temprorary_filename()
	{
		boost::filesystem::remove(path);
	}
	std::string getFilename()
	{
		return path;
	}
};




uint32_t swapEndianness(uint32_t bits)
{
	return  ((bits >> 24) & 0xff) |    // move byte 3 to byte 0
		((bits << 8) & 0xff0000) |    // move byte 1 to byte 2
		((bits >> 8) & 0xff00) |     // move byte 2 to byte 1
		((bits << 24) & 0xff000000);    // byte 0 to byte 3
}




std::bitset<nBits> testBits(std::bitset<nBits> bitsLine)
{
	std::bitset<nBits> b(bitsLine);
	//uint32_t t = swapEndianness(static_cast <uint32_t>(b.to_ulong()));
	uint64_t t = b.to_ulong();

	temprorary_filename fileName;
	std::ofstream file1(fileName.getFilename(), std::ios::binary);

	if (file1.is_open())
	{
		file1.write(reinterpret_cast<char*>(&t), sizeof(t));
		file1.close();
	}

	std::ifstream file2(fileName.getFilename(), std::ios::binary);
	bit_iterator<std::istreambuf_iterator<char>> first((std::istreambuf_iterator<char>(file2)));
	bit_iterator<std::istreambuf_iterator<char>> last((std::istreambuf_iterator<char>()));
	std::bitset<nBits> temp;
	std::stringstream s;


	std::copy(first, last, std::ostream_iterator<int>(s));

	for (int result = (int)s.get(); !s.eof(); result = (int)s.get())
	{
		temp <<= 1;
		temp |= result & 0x1;

	}

	std::bitset<nBits> reverse_temp;
	for (int i = 0; i < nBits; i++)
		reverse_temp[i] = temp[nBits - i - 1];
	file2.close();

	return reverse_temp;
}



TEST_CASE(" Test Bit reader: ", "one")
{

	SECTION(" Manual string: ") {
		REQUIRE(testBits(manual) == manual);
	}

	SECTION(" String with 0: ") {
		REQUIRE(testBits(zeros) == zeros);
	}

	SECTION(" Random string: ") {
		REQUIRE(testBits(randoms) == randoms);
	}

	SECTION("  Ones file: ") {
		REQUIRE(testBits(ones) == ones);

	}

	SECTION("  Test file with seekg: ") {

		std::bitset<nBits> b(randoms);
		//uint32_t t = swapEndianness(static_cast <uint32_t>(b.to_ulong()));
		uint64_t t = b.to_ulong();
		temprorary_filename fileName;
		std::ofstream file1(fileName.getFilename(), std::ios::binary);
		if (file1.is_open())
		{
			file1.write(reinterpret_cast<char*>(&t), sizeof(t));
			file1.close();
		}

		std::ifstream file2(fileName.getFilename(), std::ios::binary);
		bit_iterator<std::istreambuf_iterator<char>> first((std::istreambuf_iterator<char>(file2)));
		bit_iterator<std::istreambuf_iterator<char>> last((std::istreambuf_iterator<char>()));
		std::bitset<nBits> temp1;
		std::bitset<nBits> temp2;
		std::stringstream s1;


		std::copy(first, last, std::ostream_iterator<int>(s1));

		for (int result = (int)s1.get(); !s1.eof(); result = (int)s1.get())
		{
			temp1 <<= 1;
			temp1 |= result & 0x1;

		}

		std::bitset<nBits> reverse_temp1;
		for (int i = 0; i < nBits; i++)
			reverse_temp1[i] = temp1[nBits - i - 1];

		file2.clear();
		file2.seekg(0);

		bit_iterator<std::istreambuf_iterator<char>> first2((std::istreambuf_iterator<char>(file2)));
		bit_iterator<std::istreambuf_iterator<char>> last2((std::istreambuf_iterator<char>()));
		std::stringstream s2;


		std::copy(first2, last2, std::ostream_iterator<int>(s2));

		for (int result = (int)s2.get(); !s2.eof(); result = (int)s2.get())
		{
			temp2 <<= 1;
			temp2 |= result & 0x1;

		}

		std::bitset<nBits> reverse_temp2;
		for (int i = 0; i < nBits; i++)
			reverse_temp2[i] = temp2[nBits - i - 1];
		REQUIRE(reverse_temp1 == reverse_temp2);

	}

	/*SECTION("  Empty file: ") {

		temprorary_filename fileName;
		std::ofstream file1(fileName.getFilename());						// this line creates file
		std::ifstream file2(fileName.getFilename(), std::ios::binary);
		bit_iterator bit_object(file2);

		REQUIRE(bit_object.readBit() == -1);

	}*/
};








