
#ifndef PCH_H
#define PCH_H

#pragma once
#pragma once
#include <bitset>
#include <iostream>
using byte = unsigned char;
using word = unsigned short;
using key = byte[10];

class SkipJack
{
public:
	static word concatenat(byte x, byte y);
	static byte f(byte x);
	static word G_permutation(word x, byte k, key crypto_variable);
	static word G_permutation_inverse(word x, byte k, key crypto_variable);
	static void rule_a(word w[], byte counter, key crypto_variable);
	static void rule_b(word w[], byte counter, key crypto_variable);
	static void rule_a_inverse(word w[], byte counter, key crypto_variable);
	static void rule_b_inverse(word w[], byte counter, key crypto_variable);
	static long long encrypt(long long plaintext, key cv);
	static long long decrypt(long long plaintext, key cv);
	static byte const f_table[16][16];
};


#endif 
