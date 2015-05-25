#define CATCH_CONFIG_MAIN
#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include <bit_iterator.hpp>
#include <boost/dynamic_bitset.hpp>
#include <catch.hpp>
#include <algorithm>
#include <iterator>
#include <vector>
#include <stdint.h>
#include <list>
#include <array>
#include <iomanip>






const int nBits = 64;

const std::bitset < nBits > manual("1011100110110000101100100");
const std::bitset < nBits > ones(std::numeric_limits<uint32_t>::max());
const std::bitset < nBits > zeros;
const std::bitset < nBits > randoms(std::rand());
const std::bitset < 0 >  empty;



template<class InputIterator>
bit_iterator<decltype(InputIterator)> make_bit_iterator(InputIterator iter)
{
	bit_iterator<decltype(iter)> obj(iter);
	return obj;
};




boost::dynamic_bitset<uint8_t> test(std::bitset<nBits> bitsLine)
   {
	boost::dynamic_bitset<uint8_t> expected(bitsLine.to_string());
	std::vector<uint8_t> v;
	boost::to_block_range(expected, back_inserter(v));
	boost::dynamic_bitset<uint8_t> output;

	bit_iterator<decltype(v.begin())> first(v.begin());
	bit_iterator<decltype(v.end())> last(v.end());
    std::for_each(first, last, [&output](bool x) { output.push_back(x); });

	//std::for_each(make_bit_iterator(v.begin()), make_bit_iterator(v.end()), [&output](bool x) { output.push_back(x); });
	return output;
	}

boost::dynamic_bitset<uint8_t> test_preparation(std::bitset<nBits> bitsLine)
	{
	boost::dynamic_bitset<uint8_t> expected(bitsLine.to_string());
	return expected;
	}


TEST_CASE(" Test Bit reader: ", "one")
{

	SECTION(" Manual string: ") {
		REQUIRE(test(manual) == test_preparation(manual));
	}

	SECTION(" String with 0: ") {
		REQUIRE(test(zeros) == test_preparation(zeros));
	}

	SECTION(" Random string: ") {
		REQUIRE(test(randoms) == test_preparation(randoms));
	}

	SECTION("  Ones file: ") {
		REQUIRE(test(ones) == test_preparation(ones));

	}

	/*SECTION("  Empty file: ") {
		REQUIRE(test(empty) == test_preparation(empty));
		
	}*/

};








