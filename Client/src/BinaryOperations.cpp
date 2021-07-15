#include "BinaryOperations.h"


std::string BinaryOperations::char_string_to_binary_string(std::string str)
{
	std::vector<std::string> binary_vector;
	std::string binary_string="";
	char i = 0;
	for (char& _char : str)
	{
		binary_string+=std::bitset<8>(_char).to_string();
	}
	return binary_string;
}



std::string BinaryOperations::binary_string_to_ascii_string(std::string str)
{
	std::string output="";
	std::stringstream sstream(str);
	while (sstream.good())
	{
		std::bitset<8> bit;
		sstream >> bit;
		if (!sstream.good())
			break;
		char c = char(bit.to_ullong());
		output = output + c;
	}
	return output;
}

std::string BinaryOperations::string_padding_8_byte(std::string str)
{
	int i,string_size = str.size();
	if (string_size == 0 || string_size % 64 == 0)
		return str;

		int padding_length = 64 - (string_size % 64);
		for (i = 0; i < padding_length; ++i)
		{
			str += '0';
		}
		str[string_size] = padding_length;
		str[string_size+padding_length-1] = padding_length;

	return str;

}
std::string BinaryOperations::string_depadding_8_byte(std::string str)
{
	int str_size = str.size();
	int padding_length = str[str_size - 1];
	int padding_counter = 0;
	for (int i = str_size; i > str_size - padding_length; --i)
	{
		if (str[i] == '0')
			padding_counter += 1;
	}
	int check_if_the_same = str[str_size - padding_length];
	if (padding_length == (padding_counter + 2) && check_if_the_same == padding_length)
		return str.substr(0, str_size - padding_length);
	return str;
}
std::vector<std::string> BinaryOperations::string_to_8_bytes_vector(std::string str)
{
	int number_of_substrings = str.size() / 64;
	std::vector<std::string> output;
	if (!(str.size() % 64))
	{
		std::cout << "\n number of substrings: " << number_of_substrings << std::endl;
		for (int i = 0; i < number_of_substrings; ++i)
		{
			std::string temp = str.substr(i * 64, 64);

			output.push_back(temp);
			temp = "";
		}
		return output;
	}
	std::vector<std::string> a;
	return a;
}
 
std::vector<unsigned long long> BinaryOperations::string_vector_to_long_long_vector(std::vector<std::string> vec)
{
	std::vector<unsigned long long> output;
	for (std::string i : vec)
	{
		output.push_back(std::bitset<64>(i).to_ullong());
	}
	return output;
}
std::vector<unsigned long long> BinaryOperations::decimal_string_vector_to_long_long_vector(std::vector<std::string> vec)
{
	std::vector<unsigned long long> output;
	for (std::string i : vec)
	{
		std::cout << "\n inside : " << i.length() << std::endl;
		output.push_back(stol(i,nullptr,10));
	}
	return output;
}
std::string BinaryOperations::string_vector_to_string(std::vector<std::string> vec)
{
	std::string output = "";
	for (std::string i : vec)
	{
		output += i;
	}
	return output;
}

std::string BinaryOperations::long_long_vector_to_string(std::vector<unsigned long long> vec)
{
	std::vector<std::string> temp_vect;
	std::string output="";
	std::string output_temp="";
	for (long long i : vec)
	{
		temp_vect.push_back(std::bitset<64>(i).to_string());
	}

	for (std::string i : temp_vect)
	{
		std::stringstream sstream(i);
		while (sstream.good())
		{
			std::bitset<8> bits;
			sstream >> bits;
			if (!sstream.good())
				break;
			output += char(bits.to_ullong());
		}
	}
	return output;
}
unsigned char BinaryOperations::random_number(unsigned char maximum, unsigned char minimum)
{
	static bool flag = true;
	if (flag)
	{
		srand(std::time(NULL));
		flag = false;
	}
	return minimum + rand() % ((maximum + 1) - minimum);
}
void BinaryOperations::generate_key(unsigned char key[], unsigned char length_in_bytes)
{
	for (unsigned char i = 0; i < length_in_bytes; i++)
	{
		//key[i]=BinaryOperations::random_number(255, 0);
		key[i] = 'a';
	}
}
