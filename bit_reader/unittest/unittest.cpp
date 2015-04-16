#define CATCH_CONFIG_MAIN
#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include <bit_iterator.hpp>
#include <boost/filesystem.hpp>
#include <catch.hpp>



std::string getRandomLine();
std::string manualLine = "011100110110000111100100";
std::string oneString = "11111111111111111111111111111111";
std::string zeroString = "00000000000000000000000000000000";
std::string randomLine = getRandomLine();




std::string getRandomLine()
{
	std::string line;
	for (int i = 0; i <= 31; i++)
	{
		int t = std::rand() % 2;
		line = line + std::to_string(t);
	}
	//  std::cout << line;
	return line;
}
std::string convertBitsLineForTest(std::string line)
{
	while (line.length() < 32)
		line = '0' + line;
	std::string temp, result;
	for (int i = 31; i >= 0; i--)
	{
		temp = line[i] + temp;
		if (i % 8 == 0)
		{
			result = result + temp;
			temp = "";
		}
	}
	return result;
};
std::string testString(std::string bitsLine)
{
	std::string path = boost::filesystem::unique_path().string();

	while (bitsLine.length() < 32)
		bitsLine = '0' + bitsLine;

	std::bitset<32> b(bitsLine);
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

	result = bit_object.readBit();
	do
	{
		str = str + std::to_string(result);
		result = bit_object.readBit();
	} while (result != -1);
	file2.close();
	boost::filesystem::remove(path);
	return str;
}
std::string testFile()
{

	std::ifstream file("1.txt", std::ios::binary);
	file.seekg(0);
	bit_iterator bit_object(file);
	int result;
	std::string str;

	result = bit_object.readBit();
	do
	{
		str = str + std::to_string(result);
		result = bit_object.readBit();
	} while (result != -1);
	//  std::cout << str << std::endl;
	return str;
}

TEST_CASE(" Test Bit reader: ", "one")
{
	SECTION(" Manual string: ") {
		REQUIRE(testString(manualLine) == convertBitsLineForTest(manualLine));
	}

	SECTION(" String with 1: ") {
		REQUIRE(testString(oneString) == convertBitsLineForTest(oneString));
	}

	SECTION(" String with 0: ") {
		REQUIRE(testString(zeroString) == convertBitsLineForTest(zeroString));
	}

	SECTION(" Random string: ") {
		REQUIRE(testString(randomLine) == convertBitsLineForTest(randomLine));
	}

	SECTION(" Two reads of one file: ") {
		REQUIRE(testFile() == testFile());

	}
};









