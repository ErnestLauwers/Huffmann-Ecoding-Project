#ifdef TEST_BUILD

#include "data/frequency-table.h"
#include "catch.hpp"
#include <type_traits>

namespace
{

	void check_increment_value_and_operator(char a, int expected)
	{
		data::FrequencyTable<char> freqtable;

		freqtable.increment('a');
		freqtable.increment('b');
		freqtable.increment('b');
		freqtable.increment('c');
		freqtable.increment('c');
		freqtable.increment('c');

		CHECK(freqtable[a] == expected);
	}

	void check_values(char a, std::vector<char> expected_values)
	{
		data::FrequencyTable<char> freqtable;

		freqtable.increment('a');
		freqtable.increment('b');
		freqtable.increment('c');
		freqtable.increment(a);

		CHECK(freqtable.values() == expected_values);
	}

	void check_count_frequencies(std::vector<char> given_values, std::vector<int> expected_values)
	{
		auto frequency_table = data::count_frequencies(given_values);
		
		CHECK(frequency_table['a'] == expected_values[0]);
		CHECK(frequency_table['b'] == expected_values[1]);
		CHECK(frequency_table['c'] == expected_values[2]);
	}
}

TEST_CASE("Frequency table tests")
{
	check_increment_value_and_operator('a', 1);
	check_increment_value_and_operator('b', 2);
	check_increment_value_and_operator('c', 3);
	check_increment_value_and_operator('d', 0);

	check_values('a', { 'a', 'b', 'c' });
	check_values('d', { 'a', 'b', 'c', 'd' });

	check_count_frequencies({ 'a', 'a', 'b', 'a', 'c', 'b' }, { 3, 2, 1 });
	check_count_frequencies({ 'b', 'a', 'b', 'c', 'c', 'b' }, { 1, 3, 2 });
	check_count_frequencies({ 'a', 'a', 'b', 'a', 'c', 'a' }, { 4, 1, 1 });
}

#endif