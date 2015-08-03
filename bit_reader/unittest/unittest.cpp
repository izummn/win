#define CATCH_CONFIG_MAIN
#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include <bit_iterator.hpp>
#include <obit_iterator.hpp>
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
const std::bitset < nBits > ones(std::numeric_limits<uint64_t>::max());
const std::bitset < nBits > zeros;
const std::bitset < nBits > randoms(std::rand());
const std::bitset < nBits >  empty;


template<class Container>
boost::dynamic_bitset<uint8_t> to_dynamic_bitset(std::bitset<nBits> bitsLine)
{
	Container v;
	boost::dynamic_bitset<uint8_t> expected(bitsLine.to_string());
	
	boost::to_block_range(expected, back_inserter(v));
	boost::dynamic_bitset<uint8_t> output;
	std::for_each(make_bit_iterator(v.begin()), make_bit_iterator(v.end()), [&output](bool x) { output.push_back(x); });
	return output;

	}

template<>
boost::dynamic_bitset<uint8_t> to_dynamic_bitset<std::forward_list<uint8_t>>(std::bitset<nBits> bitsLine)
{
	std::string s = bitsLine.to_string();	
	for (int i = 0; i <= nBits - CHAR_BIT; i += CHAR_BIT)
	std::reverse(std::begin(s) + i, std::begin(s) + i + CHAR_BIT);
	std::reverse(std::begin(s), std::end(s));
	

	std::forward_list<uint8_t> l;
	boost::dynamic_bitset<uint8_t> expected(s);

	boost::to_block_range(expected, front_inserter(l));
	boost::dynamic_bitset<uint8_t> output;
	std::for_each(make_bit_iterator(l.begin()), make_bit_iterator(l.end()), [&output](bool x) { output.push_back(x); });
	return output;
}

template<>
boost::dynamic_bitset<uint8_t> to_dynamic_bitset<std::istreambuf_iterator<char>>(std::bitset<nBits> bitsLine)
{
	boost::dynamic_bitset<uint8_t> output;

	std::stringstream s;

	boost::dynamic_bitset<unsigned char> b(bitsLine.to_string());
	boost::to_block_range(b, std::ostreambuf_iterator<char>(s));
	bit_iterator<std::istreambuf_iterator<char>> first((std::istreambuf_iterator<char>(s)));
	bit_iterator<std::istreambuf_iterator<char>> last((std::istreambuf_iterator<char>()));
	std::for_each(first, last, [&output](bool x) { output.push_back(x); });
	return output;
}
boost::dynamic_bitset<uint8_t> expected_string(std::bitset<nBits> bitsLine)
	{
	boost::dynamic_bitset<uint8_t> expected(bitsLine.to_string());
	return expected;
	}



std::bitset<nBits> to_output_iterator(std::bitset<nBits> bitsLine)
{
	boost::dynamic_bitset<uint8_t> l(to_dynamic_bitset<std::vector<uint8_t>>(manual));
	std::bitset<nBits> temp(l.to_ulong());
	return temp;
}


boost::dynamic_bitset<uint8_t> for_vector_test(std::bitset<nBits> bitsLine)
{
	boost::dynamic_bitset<uint8_t> result(bitsLine.to_string());
	return result;
}


/*   ////////  work correct, but not effective
std::vector<uint8_t> to_obit_iterator_vector(std::bitset<nBits> bitsLine)
{
	std::vector<uint8_t> p(nBits / CHAR_BIT);
	std::vector<uint8_t>::iterator it(p.begin());
	obit_iterator<std::vector<uint8_t>::iterator>  b(it);
	for (int i(0); i < nBits; i++)
		if (bitsLine[i] == 1) *b++ = true;
		else *b++ = false;
		return p;
};*/

boost::dynamic_bitset<uint8_t> to_obit_iterator_vector(std::bitset<nBits> bitsLine)
{
	std::vector<uint8_t> p(nBits / CHAR_BIT);
	std::vector<uint8_t>::iterator it(p.begin());
	obit_iterator<std::vector<uint8_t>::iterator>  b(it);

	boost::dynamic_bitset<uint8_t> output;
	//std::for_each(b, b += nBits, [&output](bool x) { output.push_back(x); });

	for (int i(0); i < nBits; i++)
		if (bitsLine[i] == 1)
		{
		*b++ = true;
//		output.push_back(true);
		}

		else
		{
			*b++ = false;
//			output.push_back(false);
		}

//	boost::dynamic_bitset<uint8_t> expected(bitsLine.to_string());

	//boost::from_block_range(p.begin(), p.end() - 1, output );
	/*for (int i(0); i < (nBits / CHAR_BIT); i++)
		to_block_
		output.push_back(p[i]);*/
	//std::for_each(p.begin(), p.end(), [&output](uint8_t x) { output.push_back(x); });
	return output;
};


TEST_CASE(" Test Bit reader: vector ", "�1")
{
	std::vector<uint8_t> v;

	SECTION(" Manual string: ") {
		REQUIRE(to_dynamic_bitset<std::vector<uint8_t>>(manual) == expected_string(manual));
	}

	SECTION(" String with 0: ") {
		REQUIRE(to_dynamic_bitset<std::vector<uint8_t>>(zeros) == expected_string(zeros));
	}

	SECTION(" Random string: ") {
		REQUIRE(to_dynamic_bitset<std::vector<uint8_t>>(randoms) == expected_string(randoms));
	}

	SECTION("  Ones file: ") {
		REQUIRE(to_dynamic_bitset<std::vector<uint8_t>>(ones) == expected_string(ones));

	}
};
TEST_CASE(" Test Bit reader: list ", "�2")
{
	SECTION(" Manual string: ") {
		REQUIRE(to_dynamic_bitset<std::list<uint8_t>>(manual) == expected_string(manual));
	}

	SECTION(" String with 0: ") {
		REQUIRE(to_dynamic_bitset<std::list<uint8_t>>(zeros) == expected_string(zeros));
	}

	SECTION(" Random string: ") {
		REQUIRE(to_dynamic_bitset<std::list<uint8_t>>(randoms) == expected_string(randoms));
	}

	SECTION("  Ones file: ") {
		REQUIRE(to_dynamic_bitset<std::list<uint8_t>>(ones) == expected_string(ones));

	}
};
TEST_CASE(" Test Bit reader: forward_list ", "�3")
{
		SECTION(" Manual string: ") {
			REQUIRE(to_dynamic_bitset<std::forward_list<uint8_t>>( manual) == expected_string(manual));
		}

		SECTION(" String with 0: ") {
			REQUIRE(to_dynamic_bitset<std::forward_list<uint8_t>>(zeros) == expected_string(zeros));
		}

		SECTION(" Random string: ") {
			REQUIRE(to_dynamic_bitset<std::forward_list<uint8_t>>(randoms) == expected_string(randoms));
		}

		SECTION("  Ones file: ") {
			REQUIRE(to_dynamic_bitset<std::forward_list<uint8_t>>(ones) == expected_string(ones));

		}

};
TEST_CASE(" Test Bit reader: istream ", "�4")
	{
		SECTION(" Manual string: ") {
			REQUIRE(to_dynamic_bitset<std::istreambuf_iterator<char>>(manual) == expected_string(manual));
		}

		SECTION(" String with 0: ") {
			REQUIRE(to_dynamic_bitset<std::istreambuf_iterator<char>>(zeros) == expected_string(zeros));
		}

		SECTION(" Random string: ") {
			REQUIRE(to_dynamic_bitset<std::istreambuf_iterator<char>>(randoms) == expected_string(randoms));
		}

		SECTION("  Ones file: ") {
			REQUIRE(to_dynamic_bitset<std::istreambuf_iterator<char>>(ones) == expected_string(ones));
		}

};
TEST_CASE(" Test Bit reader: additional ", "�5")
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
			auto second = first; 
			second++;
			auto p = second;
							
			REQUIRE(first != p);
			REQUIRE(distance(first, last) == CHAR_BIT * v.size());
			std::advance(first, 1);
			REQUIRE(first == second);
		}
		
	};
TEST_CASE(" Reverce task", "�6")
	{

		SECTION(" For manual string: ") {
			REQUIRE(to_output_iterator(manual) == manual);
		}
	};



TEST_CASE(" Test output bit reader: ", "�7")
	{
	SECTION("  Ones file: ") {
		REQUIRE(to_obit_iterator_vector(manual) == for_vector_test(manual));
	}

	//		REQUIRE(to_obit_iterator_list(manual) == to_list(manual));
	//	}
	

/*
		SECTION(" Manual string: ") {
			REQUIRE(to_obit_iterator(manual) == to_vector(manual));
		}

		SECTION(" String with 0: ") {
			REQUIRE(to_obit_iterator(zeros) == to_vector(zeros));
		}

		SECTION(" Random string: ") {
			REQUIRE(to_obit_iterator(randoms) == to_vector(randoms));
		}
		*/
	};