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
#include <forward_list>
#include <sstream>


const int nBits = 64;

const std::bitset < nBits > manual("1011100110110000101100100");
const std::bitset < nBits > ones(std::numeric_limits<uint32_t>::max());
const std::bitset < nBits > zeros;
const std::bitset < nBits > randoms(std::rand());
const std::bitset < 0 >  empty;



boost::dynamic_bitset<uint8_t> to_dynamic_bitset_vector(std::bitset<nBits> bitsLine)
   {
	boost::dynamic_bitset<uint8_t> expected(bitsLine.to_string());
	std::vector<uint8_t> v;
	boost::to_block_range(expected, back_inserter(v));
	boost::dynamic_bitset<uint8_t> output;

	bit_iterator<decltype(v.begin())> first(v.begin());
	bit_iterator<decltype(v.end())> last(v.end());
    std::for_each(first, last, [&output](bool x) { output.push_back(x); });
	return output;
	}

boost::dynamic_bitset<uint8_t> expected_string(std::bitset<nBits> bitsLine)
	{
	boost::dynamic_bitset<uint8_t> expected(bitsLine.to_string());
	return expected;
	}


boost::dynamic_bitset<uint8_t> to_dynamic_bitset_list(std::bitset<nBits> bitsLine)
{
	boost::dynamic_bitset<uint8_t> expected(bitsLine.to_string());
	std::list<uint8_t> l;
	boost::to_block_range(expected, back_inserter(l));
	boost::dynamic_bitset<uint8_t> output;

	bit_iterator<decltype(l.begin())> first(l.begin());
	bit_iterator<decltype(l.end())> last(l.end());
	std::for_each(first, last, [&output](bool x) { output.push_back(x); });
	return output;
}

boost::dynamic_bitset<uint8_t> to_dynamic_bitset_empty()
{
	boost::dynamic_bitset<uint8_t> expected;
	std::vector<uint8_t> v;
	boost::dynamic_bitset<uint8_t> output;

	bit_iterator<decltype(v.begin())> first(v.begin());
	bit_iterator<decltype(v.end())> last(v.end());
	std::for_each(first, last, [&output](bool x) { output.push_back(x); });
	return output;
}

boost::dynamic_bitset<uint8_t> expected_string_empty()
{
	boost::dynamic_bitset<uint8_t> expected;
	return expected;
}


/*boost::dynamic_bitset<uint8_t> to_dynamic_bitset_forward_list(std::bitset<nBits> bitsLine)
{
	boost::dynamic_bitset<uint8_t> expected(bitsLine.to_string());
	std::forward_list<uint8_t> l;
	boost::to_block_range(expected, );
	boost::dynamic_bitset<uint8_t> output;

	bit_iterator<decltype(l.begin())> first(l.begin());
	bit_iterator<decltype(l.end())> last(l.end());
	std::for_each(first, last, [&output](bool x) { output.push_back(x); });
	return output;
}*/




TEST_CASE(" Test Bit reader: ", "one")
{

	SECTION(" Manual string: ") {
		REQUIRE(to_dynamic_bitset_vector(manual) == expected_string(manual));
	}

	SECTION(" String with 0: ") {
		REQUIRE(to_dynamic_bitset_vector(zeros) == expected_string(zeros));
	}

	SECTION(" Random string: ") {
		REQUIRE(to_dynamic_bitset_vector(randoms) == expected_string(randoms));
	}

	SECTION("  Ones file: ") {
		REQUIRE(to_dynamic_bitset_vector(ones) == expected_string(ones));

	}

	SECTION(" Manual string: ") {
		REQUIRE(to_dynamic_bitset_list(manual) == expected_string(manual));
	}

	SECTION(" String with 0: ") {
		REQUIRE(to_dynamic_bitset_list(zeros) == expected_string(zeros));
	}

	SECTION(" Random string: ") {
		REQUIRE(to_dynamic_bitset_list(randoms) == expected_string(randoms));
	}

	SECTION("  Ones file: ") {
		REQUIRE(to_dynamic_bitset_list(ones) == expected_string(ones));

	}

	SECTION("  Empty file: ") {
		REQUIRE(to_dynamic_bitset_empty() == expected_string_empty());


	/*SECTION(" Manual string: ") {
		REQUIRE(to_dynamic_bitset_forward_list(manual) == expected_string(manual));
	}

	SECTION(" String with 0: ") {
		REQUIRE(to_dynamic_bitset_forward_list(zeros) == expected_string(zeros));
	}

	SECTION(" Random string: ") {
		REQUIRE(to_dynamic_bitset_forward_list(randoms) == expected_string(randoms));
	}

	SECTION("  Ones file: ") {
		REQUIRE(to_dynamic_bitset_forward_list(ones) == expected_string(ones));

	}
	*/

	
		
	}

};








