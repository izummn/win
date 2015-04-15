#define CATCH_CONFIG_MAIN
#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include <bit_iterator.hpp>
#include <boost/filesystem.hpp>
#include <catch.hpp>

const std::string bitsLine = "11001101011100110110000111100100";
 // const std::string bitsLine = "11111111111111111111111111111111";
 // const std::string bitsLine = "00000000000000000000000000000000";

TEST_CASE(" Expected result: bits are equals! ", "one") {
	std::string path = boost::filesystem::unique_path().string();
	std::bitset<32> b(bitsLine);
	auto t = b.to_ulong();
	std::cout << " 11001101 01110011 01100001 11100100 " << std::endl;	
	std::ofstream file1(path, std::ios::binary);

	if (file1.is_open())
	{
		file1.write(reinterpret_cast<char*>(&t), sizeof(t));
		file1.close();
	}

	std::ifstream file2(path, std::ios::binary);
	bit_iterator bit_object(file2);
	int result;
	std::string str;
	
	result = bit_object.readBit();	
	do
	{	
		str = str + std::to_string(result);
		result = bit_object.readBit();	
	} while (result != -1);
	file2.close();
	boost::filesystem::remove(path);

	REQUIRE(str == bitsLine);
};









