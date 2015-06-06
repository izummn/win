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


const int nBits = 32;

const std::bitset < nBits > manual("1011100110110000101100100");
const std::bitset < nBits > ones(std::numeric_limits<uint32_t>::max());
const std::bitset < nBits > zeros;
const std::bitset < nBits > randoms(std::rand());
const std::bitset < nBits >  empty;
const std::bitset < 0 >  empty1;



template<class Container>
boost::dynamic_bitset<uint8_t> to_dynamic_bitset(Container v, std::bitset<nBits> bitsLine)
{
	boost::dynamic_bitset<uint8_t> expected(bitsLine.to_string());
	
	boost::to_block_range(expected, back_inserter(v));
	boost::dynamic_bitset<uint8_t> output;
	std::for_each(make_bit_iterator(v.begin()), make_bit_iterator(v.end()), [&output](bool x) { output.push_back(x); });
	return output;
	}


boost::dynamic_bitset<uint8_t> expected_string(std::bitset<nBits> bitsLine)
	{
	boost::dynamic_bitset<uint8_t> expected(bitsLine.to_string());
	return expected;
	}



uint32_t swapEndianness(uint32_t bits)
{
	return  ((bits >> 24) & 0xff) |    // move byte 3 to byte 0
		((bits << 8) & 0xff0000) |    // move byte 1 to byte 2
		((bits >> 8) & 0xff00) |     // move byte 2 to byte 1
		((bits << 24) & 0xff000000);    // byte 0 to byte 3
}


boost::dynamic_bitset<uint8_t> to_dynamic_bitset(std::bitset<nBits> bitsLine)
{
	std::bitset<nBits> temp(swapEndianness(bitsLine.to_ulong()));
	std::forward_list<uint8_t> l;
	boost::dynamic_bitset<uint8_t> expected(temp.to_string());
	
	boost::to_block_range(expected, front_inserter(l));
	boost::dynamic_bitset<uint8_t> output;
	std::for_each(make_bit_iterator(l.begin()), make_bit_iterator(l.end()), [&output](bool x) { output.push_back(x); });
	return output;
}

boost::dynamic_bitset<uint8_t> to_dynamic_bitset_istream(std::bitset<nBits> bitsLine)
{
	boost::dynamic_bitset<uint8_t> output;

	std::istringstream s(std::ios::binary);
	s.str(bitsLine.to_string());
	bit_iterator<std::istreambuf_iterator<char>> first((std::istreambuf_iterator<char>(s)));
	bit_iterator<std::istreambuf_iterator<char>> last((std::istreambuf_iterator<char>()));
	std::for_each(first, last, [&output](bool x) { output.push_back(x); });
	return output;
}


TEST_CASE(" Test Bit reader: vector ", "¹1")
{
	std::vector<uint8_t> v;

	SECTION(" Manual string: ") {
		REQUIRE(to_dynamic_bitset(v, manual) == expected_string(manual));
	}

	SECTION(" String with 0: ") {
		REQUIRE(to_dynamic_bitset(v, zeros) == expected_string(zeros));
	}

	SECTION(" Random string: ") {
		REQUIRE(to_dynamic_bitset(v, randoms) == expected_string(randoms));
	}

	SECTION("  Ones file: ") {
		REQUIRE(to_dynamic_bitset(v, ones) == expected_string(ones));

	}
};

TEST_CASE(" Test Bit reader: list ", "¹2")
{
	std::list<uint8_t> l;
	SECTION(" Manual string: ") {
		REQUIRE(to_dynamic_bitset(l, manual) == expected_string(manual));
	}

	SECTION(" String with 0: ") {
		REQUIRE(to_dynamic_bitset(l, zeros) == expected_string(zeros));
	}

	SECTION(" Random string: ") {
		REQUIRE(to_dynamic_bitset(l, randoms) == expected_string(randoms));
	}

	SECTION("  Ones file: ") {
		REQUIRE(to_dynamic_bitset(l, ones) == expected_string(ones));

	}
};

TEST_CASE(" Test Bit reader: forward_list ", "¹3")
{
		SECTION(" Manual string: ") {
			REQUIRE(to_dynamic_bitset( manual) == expected_string(manual));
		}

		SECTION(" String with 0: ") {
			REQUIRE(to_dynamic_bitset(zeros) == expected_string(zeros));
		}

		SECTION(" Random string: ") {
			REQUIRE(to_dynamic_bitset(randoms) == expected_string(randoms));
		}

		SECTION("  Ones file: ") {
			REQUIRE(to_dynamic_bitset(ones) == expected_string(ones));

		}

};


	TEST_CASE(" Test Bit reader: istream ", "¹4")
	{
		SECTION(" Manual string: ") {
			REQUIRE(to_dynamic_bitset_istream(manual) == expected_string(manual));
		}

		SECTION(" String with 0: ") {
			REQUIRE(to_dynamic_bitset_istream(zeros) == expected_string(zeros));
		}

		SECTION(" Random string: ") {
			REQUIRE(to_dynamic_bitset_istream(randoms) == expected_string(randoms));
		}

		SECTION("  Ones file: ") {
			REQUIRE(to_dynamic_bitset_istream(ones) == expected_string(ones));
		}

};


	TEST_CASE(" Test Bit reader: additional ", "¹5")
	{

		SECTION("  Empty container: ") {
			std::vector<uint8_t> v;
			auto f = make_bit_iterator(v.begin()),  l = make_bit_iterator(v.end());		
			REQUIRE(f == l);
		}

		SECTION("  Empty constructor: ") {
			bit_iterator<std::istreambuf_iterator<char>> first;
			bit_iterator<std::istreambuf_iterator<char>> last;
			REQUIRE(first == last);
		}

		SECTION("  operator = : ") {

			boost::dynamic_bitset<uint8_t> expected(manual.to_string());
			std::vector<uint8_t> v;
			boost::to_block_range(expected, back_inserter(v));
			auto f = make_bit_iterator(v.begin()), l = make_bit_iterator(v.end());
			f = l;
			REQUIRE(f == l);
		}

     	SECTION("  operator ++(int) : ") {
			std::vector<uint8_t> v{ { 1, 2, 0, 5 } };
			auto first = make_bit_iterator(v.begin());
			auto last = make_bit_iterator(v.end());
			//std::reverse(first, last);
			auto second = first; 
			second++;
			auto p = second;
				
			
			REQUIRE(first != p);
			REQUIRE(distance(first, last) == CHAR_BIT * v.size());
			std::advance(first, 1);
			REQUIRE(first == second);
		}
		
	};








