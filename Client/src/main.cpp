#include "SkipJack.h"
#include "server.h"
#include "BinaryOperations.h"
#include <vector>
#include <stdlib.h>


int main()
{
	////////////////encryption
	std::string plaintext = "hello world! 123 1 2 3";
	std::string send_string=BinaryOperations::string_padding_8_byte(plaintext);
	send_string=BinaryOperations::char_string_to_binary_string(send_string);
	std::vector<std::string> vec_to_send = BinaryOperations::string_to_8_bytes_vector(send_string);
	std::vector<unsigned long long> vec_long = BinaryOperations::string_vector_to_long_long_vector(vec_to_send);
	std::vector<unsigned long long> encriptioned_vec;
	unsigned char key[10];


	BinaryOperations::generate_key(key,10);


	for (long long i : vec_long)
		encriptioned_vec.push_back((unsigned long long )(SkipJack::encrypt(i, key)));
	
	send_string = BinaryOperations::long_long_vector_to_string(encriptioned_vec);
	
	std::cout << "\n encrypted string : " <<send_string<<std::endl;


	////////////////decryption
	std::vector<unsigned long long> decryption_vector_long_long;
	std::vector<unsigned long long> decryption_vector_to_string;
	
	
	std::string binary_string_decrypt = BinaryOperations::char_string_to_binary_string(send_string);
	std::vector<std::string> temp_vec = BinaryOperations::string_to_8_bytes_vector(binary_string_decrypt);
	decryption_vector_to_string=BinaryOperations::string_vector_to_long_long_vector(temp_vec);

	for (unsigned long long i : decryption_vector_to_string)
		decryption_vector_long_long.push_back(SkipJack::decrypt(i, key));

	std::string decrypted=BinaryOperations::long_long_vector_to_string(decryption_vector_long_long);
	decrypted = BinaryOperations::string_depadding_8_byte(decrypted);
	std::cout << "\n decrypted : " << decrypted << std::endl;
	
	return 0;
}
