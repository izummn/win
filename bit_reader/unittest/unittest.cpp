#define CATCH_CONFIG_MAIN
#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include <bit_iterator.hpp>
#include <boost\filesystem.hpp>
#include <catch.hpp>



const int nBits = 32;

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
			((bits << 8)  & 0xff0000) |    // move byte 1 to byte 2
			((bits >> 8)  & 0xff00) |     // move byte 2 to byte 1
			((bits << 24) & 0xff000000);    // byte 0 to byte 3
}


std::bitset<nBits> testBits(std::bitset<nBits> bitsLine)
{
	std::bitset<nBits> b(bitsLine);
	uint32_t t = swapEndianness(static_cast <uint32_t>(b.to_ulong()));

	temprorary_filename fileName;
	std::ofstream file1(fileName.getFilename(), std::ios::binary);

	if (file1.is_open())
	{
		file1.write(reinterpret_cast<char*>(&t), sizeof(t));
		file1.close();
	}

	std::ifstream file2(fileName.getFilename(), std::ios::binary);
	bit_iterator bit_object(file2);
	std::bitset<nBits> temp;

	for (int result = bit_object.readBit(); result != -1; result = bit_object.readBit())
	{
		temp <<= 1;
		temp |= result & 0x1;
	}

	file2.close();
	return temp;
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
		uint32_t t = swapEndianness(static_cast <uint32_t>(b.to_ulong()));

		temprorary_filename fileName;
		std::ofstream file1(fileName.getFilename(), std::ios::binary);
		if (file1.is_open())
		{
			file1.write(reinterpret_cast<char*>(&t), sizeof(t));
			file1.close();
		}

		std::ifstream file2(fileName.getFilename(), std::ios::binary);
		bit_iterator bit_object(file2);
		std::bitset<nBits> temp1;
		std::bitset<nBits> temp2;

		for (int result = bit_object.readBit(); result != -1; result = bit_object.readBit())
		{
			temp1 <<= 1;
			temp1 |= result & 0x1;
		}

		file2.clear();
		file2.seekg(0);

		for (int result = bit_object.readBit(); result != -1; result = bit_object.readBit())
		{
			temp2 <<= 1;
			temp2 |= result & 0x1;
		}
		REQUIRE(temp1 == temp2);

	}

	SECTION("  Empty file: ") {

		temprorary_filename fileName;
		std::ofstream file1(fileName.getFilename());						// this line creates file
		std::ifstream file2(fileName.getFilename(), std::ios::binary);
		bit_iterator bit_object(file2);

		REQUIRE(bit_object.readBit() == -1);

	}
};








