
#include "SkipJack.h"
#include <iostream>



byte const SkipJack::f_table[16][16] ={ 
0xa3,0xd7,0x09,0x83,0xf8,0x48,0xf6,0xf4,0xb3,0x21,0x15,0x78,0x99,0xb1,0xaf,0xf9,
0xe7,0x2d,0x4d,0x8a,0xce,0x4c,0xca,0x2e,0x52,0x95,0xd9,0x1e,0x4e,0x38,0x44,0x28,
0x0a,0xdf,0x02,0xa0,0x17,0xf1,0x60,0x68,0x12,0xb7,0x7a,0xc3,0xe9,0xfa,0x3d,0x53,
0x96,0x84,0x6b,0xba,0xf2,0x63,0x9a,0x19,0x7c,0xae,0xe5,0xf5,0xf7,0x16,0x6a,0xa2,
0x39,0xb6,0x7b,0x0f,0xc1,0x93,0x81,0x1b,0xee,0xb4,0x1a,0xea,0xd0,0x91,0x2f,0xb8,
0x55,0xb9,0xda,0x85,0x3f,0x41,0xbf,0xe0,0x5a,0x58,0x80,0x5f,0x66,0x0b,0xd8,0x90,
0x35,0xd5,0xc0,0xa7,0x33,0x06,0x65,0x69,0x45,0x00,0x94,0x56,0x6d,0x98,0x9b,0x76,
0x97,0xfc,0xb2,0xc2,0xb0,0xfe,0xdb,0x20,0xe1,0xeb,0xd6,0xe4,0xdd,0x47,0x4a,0x1d,
0x42,0xed,0x9e,0x6e,0x49,0x3c,0xcd,0x43,0x27,0xd2,0x07,0xd4,0xde,0xc7,0x67,0x18,
0x89,0xcb,0x30,0x1f,0x8d,0xc6,0x8f,0xaa,0xc8,0x74,0xdc,0xc9,0x5d,0x5c,0x31,0xa4,
0x70,0x88,0x61,0x2c,0x9f,0x0d,0x2b,0x87,0x50,0x82,0x54,0x64,0x26,0x7d,0x03,0x40,
0x34,0x4b,0x1c,0x73,0xd1,0xc4,0xfd,0x3b,0xcc,0xfb,0x7f,0xab,0xe6,0x3e,0x5b,0xa5,
0xad,0x04,0x23,0x9c,0x14,0x51,0x22,0xf0,0x29,0x79,0x71,0x7e,0xff,0x8c,0x0e,0xe2,
0x0c,0xef,0xbc,0x72,0x75,0x6f,0x37,0xa1,0xec,0xd3,0x8e,0x62,0x8b,0x86,0x10,0xe8,
0x08,0x77,0x11,0xbe,0x92,0x4f,0x24,0xc5,0x32,0x36,0x9d,0xcf,0xf3,0xa6,0xbb,0xac,
0x5e,0x6c,0xa9,0x13,0x57,0x25,0xb5,0xe3,0xbd,0xa8,0x3a,0x01,0x05,0x59,0x2a,0x46 };


word SkipJack::concatenat(byte x, byte y)
{
	word temp = x;
	temp = temp << 8;
	temp = temp | y;
	return temp;
}
byte SkipJack::f(byte x)
{
	char row = 0, column = 0;
	column = x & 0xFF;
	row = x >> 8;
	return SkipJack::f_table[row][column];
}
word SkipJack::G_permutation(word x,byte k, key crypto_variable)
{
	byte g1, g2, g3, g4, g5, g6;
	word g5_g6 = 0;
	g1 = g2 = g3 = g4 = g5 = g6 = 0;
	g1 = x >> 8;
	g2 = x & 0xFF;

	g3 = (f(g2^crypto_variable[(4 * k)%10]) ^ g1);
	g4 = (f(g3^crypto_variable[(4 * k + 1)%10]) ^ g2);
	g5 = (f(g4^crypto_variable[(4 * k + 2)%10]) ^ g3);
	g6 = (f(g5^crypto_variable[(4 * k + 3)%10]) ^ g4);

	g5_g6 = g5;
	g5_g6 = (g5_g6 << 8);
	g5_g6 = (g5_g6 | g6);

	return g5_g6;
}
word SkipJack::G_permutation_inverse(word x, byte k, key crypto_variable)
{
	byte g1, g2, g3, g4, g5, g6;
	word g1_g2 = 0;
	g1 = g2 = g3 = g4 = g5 = g6 = 0;
	g5 = x >> 8;
	g6 = x & 0xFF;
	g4 = f(g5^crypto_variable[(4 * k + 3)%10]) ^ g6;
	g3 = f(g4^crypto_variable[(4 * k + 2)%10]) ^ g5;
	g2 = f(g3^crypto_variable[(4 * k + 1)%10]) ^ g4;
	g1 = f(g2^crypto_variable[(4 * k)%10]) ^ g3;
	g1_g2 = g1;
	g1_g2 = g1_g2 << 8;
	g1_g2 = g1_g2 | g2;
	
	return g1_g2;
}
void SkipJack::rule_a(word w[], byte counter, key crypto_variable)
{
	word w_k[4];
	w_k[0] = w[0];
	w_k[1] = w[1];
	w_k[2] = w[2];
	w_k[3] = w[3];
	w[0] = (word)(G_permutation(w_k[0], counter, crypto_variable) ^ w_k[3] ^ (counter));
	w[1] = (word)(G_permutation(w_k[0], counter, crypto_variable));
	w[2] = w_k[1];
	w[3] = w_k[2];
}
void SkipJack::rule_b(word w[], byte counter, key crypto_variable)
{
	word w_k[4];
	w_k[0] = w[0];
	w_k[1] = w[1];
	w_k[2] = w[2];
	w_k[3] = w[3];

	w[0] = w_k[3];
	w[1] = G_permutation(w_k[0], counter, crypto_variable);
	w[2] = w_k[0] ^ w_k[1] ^ counter;
	w[3] = w_k[2];
}
void SkipJack::rule_a_inverse(word w[], byte counter, key crypto_variable)
{
	word w_k[4];
	w_k[0] = w[0];
	w_k[1] = w[1];
	w_k[2] = w[2];
	w_k[3] = w[3];

	w[0] = (G_permutation_inverse(w_k[1], counter-1, crypto_variable));
	w[1] = w_k[2];
	w[2] = w_k[3];
	w[3] = w_k[0] ^ w_k[1] ^ (counter-1);

}
void SkipJack::rule_b_inverse(word w[], byte counter, key crypto_variable)
{
	word w_k[4];
	w_k[0] = w[0];
	w_k[1] = w[1];
	w_k[2] = w[2];
	w_k[3] = w[3];

	w[0] = (G_permutation_inverse(w_k[1], counter-1, crypto_variable));
	w[1] = (G_permutation_inverse(w_k[1], counter-1, crypto_variable) ^ w_k[2] ^ (counter-1));
	w[2] = w_k[3];
	w[3] = w_k[0];
}
long long SkipJack::encrypt(long long plaintext, key cv)
{
	byte counter = 0;
	word w[4];

	w[3] = (plaintext & 0xffff);
	w[2] = (plaintext >> 16) & 0xFFFF;
	w[1] = (plaintext >> 32) & 0xFFFF;
	w[0] = (plaintext >> 48) & 0xFFFF;

	for (int i = 0; i < 8; i++)
	{
		rule_a(w, counter, cv);
		counter++;
	}
	for (int i = 0; i < 8; i++)
	{
		rule_b(w, counter, cv);
		counter++;
	}
	for (int i = 0; i < 8; i++)
	{
		rule_a(w, counter, cv);
		counter++;
	}
	for (int i = 0; i < 8; i++)
	{
		rule_b(w, counter, cv);
		counter++;
	}


	plaintext = w[0];
	plaintext = plaintext << 16;
	plaintext = plaintext | w[1];
	plaintext = plaintext << 16;
	plaintext = plaintext | w[2];
	plaintext = plaintext << 16;
	plaintext = plaintext | w[3];
	
	return plaintext;
}
long long SkipJack::decrypt(long long plaintext, key cv)
{
	byte counter = 32;
	word w[4];

	w[3] = plaintext & 0xFFFF;
	w[2] = (plaintext >> 16) & 0xFFFF;
	w[1] = (plaintext >> 32) & 0xFFFF;
	w[0] = (plaintext >> 48) & 0xFFFF;


	for (int i = 0; i < 8; i++)
	{
		rule_b_inverse(w, counter, cv);
		counter --;
	}
	for (int i = 0; i < 8; i++)
	{
		rule_a_inverse(w, counter, cv);
		counter --;
	}
	for (int i = 0; i < 8; i++)
	{
		rule_b_inverse(w, counter, cv);
		counter --;
	}
	for (int i = 0; i < 8; i++)
	{
		rule_a_inverse(w, counter, cv);
		counter --;
	}

	plaintext = w[0];
	plaintext = plaintext << 16;
	plaintext = plaintext | w[1];
	plaintext = plaintext << 16;
	plaintext = plaintext | w[2];
	plaintext = plaintext << 16;
	plaintext = plaintext | w[3];
	return plaintext;
}
