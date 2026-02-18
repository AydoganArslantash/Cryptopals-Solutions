/*
  Challenge 1.1: Convert hex to base64
  Description:

  The string:
  49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d

  Should Produce:
  SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t

 So go ahead and make that happen. You'll need to use this code for the rest of
 the exercises.

 Cryptopals Rule: Always operate on raw bytes, never on encoded strings. Only
 use hex and base64 for pretty-printing.

 Solved by: Aydogan Arslantash
 Time: <2026-02-10 Tue 00:12>
*/

#include <cryptopp/filters.h>
#include <iostream>
#include <cryptopp/base64.h>
#include <cryptopp/hex.h>

using namespace CryptoPP;
int main()
{
	std::string usr_input =
	    "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69"
	    "736f6e6f7573206d757368726f6f6d";

	// Hex to raw bytes
	std::string raw_bytes;
	StringSource ss1(usr_input, true,
			 new HexDecoder(new StringSink(raw_bytes)));

	// Raw Bytes to Base64
	std::string base64_output;
	StringSource ss2(raw_bytes, true,
			 new Base64Encoder(new StringSink(base64_output)));

	std::cout << "User Input: " << usr_input << "\n";
	std::cout << "Raw Bytes: " << raw_bytes << "\n";
	std::cout << "Base64: " << base64_output << "\n";

	return 0;
}
