/*
 Challenge 1.2: Fixed XOR

 Description:
 Write a function that takes two equal-length buffers and produces their XOR
 combination.

 If your function works properly, then when you feed it the string:

 1c0111001f010100061a024b53535009181c

 ... after hex decoding, and when XOR'd against:

 686974207468652062756c6c277320657965

 ... should produce:

 746865206b696420646f6e277420706c6179

 Solved By: Aydogan Arslantash
 Date: <2026-02-10 Tue 17:55>

*/

#include <iostream>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>

using namespace CryptoPP;

int main()
{
	std::string intake = "1c0111001f010100061a024b53535009181c";
	std::string xor_key = "686974207468652062756c6c277320657965";

	std::string temp_1;
	StringSource ss1(intake, true, new HexDecoder(new StringSink(temp_1)));

	std::string temp_2;
	StringSource ss2(xor_key, true, new HexDecoder(new StringSink(temp_2)));

	if (temp_1.size() != temp_2.size()) {
		std::cerr << "Inputs are not in equal size.\n";
		return -1;
	}

	std::string result;
	for (size_t i = 0; i < temp_1.size(); i++) {
		result += temp_1[i] ^ temp_2[i];
	}

	std::string hex_output;
	StringSource ss3(
	    result, true,
	    new HexEncoder(new StringSink(hex_output),
			   false)); // the last false is for lowercase.

	std::cout << hex_output << "\n";
	return 0;
}

/*
int main()
{
	std::string intake = "1c0111001f010100061a024b53535009181c";
	std::string xor_key = "686974207468652062756c6c277320657965";

	while (sizeof(intake) == sizeof(xor_key)) {
	}
	do {
		std::string temp_1;
		StringSource ss1(intake, true,
				 new HexDecoder(new StringSink(temp_1)));

		std::string temp_2;
		StringSource ss2(xor_key, true,
				 new HexDecoder(new StringSink(temp_2)));

		std::string result = temp_1 ^ temp_2;
		std::cout << result;
		return 0;
	}

	return -1;
}
*/
