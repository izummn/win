#define CATCH_CONFIG_MAIN
#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include <bit_iterator.hpp>
#include <boost/filesystem.hpp>
#include <catch.hpp>


TEST_CASE(" Expected result: bits are equals! ", "one") {
	std::string path = boost::filesystem::unique_path().string();
	std::bitset<32> b("11001101011100110110000101100100");
	auto t = b.to_ulong();
	
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
	
	do
	{
		result = bit_object.readBit();
		if (result == -1) break;
		str = str + std::to_string(result);
	} while (result != -1);
	file2.close();
	boost::filesystem::remove(path);

	REQUIRE(str == "11001101011100110110000101100100");	
};









