#pragma once
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <bitset>
#include<sstream>

class BinaryOperations
{
public:
	static std::string char_string_to_binary_string(std::string str);
	static std::string binary_string_to_ascii_string(std::string str);
	static std::string string_padding_8_byte(std::string str);
	static std::string string_depadding_8_byte(std::string str);
	static std::vector<std::string> string_to_8_bytes_vector(std::string str);
	static std::vector<unsigned long long> string_vector_to_long_long_vector(std::vector<std::string> vec);
	static std::string string_vector_to_string(std::vector<std::string> vec);
	static std::string long_long_vector_to_string(std::vector<unsigned long long> vec);
	static unsigned char random_number(unsigned char maximum, unsigned char minimum);
	static std::vector<unsigned long long> decimal_string_vector_to_long_long_vector(std::vector<std::string> vec);
	static void generate_key(unsigned char key[], unsigned char length_in_bytes);
};

