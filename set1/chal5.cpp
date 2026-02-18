/*
 * Challenge 1.5: Implement repeating-key XOR
 * Description:
 Here is the opening stanza of an important work of the English language:
'''
Burning 'em, if you ain't quick and nimble
I go crazy when I hear a cymbal
'''
Encrypt it, under key "ICE", using repeating-key XOR.
In repeating-key XOR, you'll sequentially apply each byte of the key; the first
byte of plaintext will be XOR'd against I, the next C,the next E, then I again
for the 4th byte, and so on.

It should come out to:

0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272
a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f

Encrypt a bunch of stuff using your repeating-key XOR function. Encrypt your
mail. Encrypt your password file. Your .sig file. Get a feel for it. I promise,
we aren't wasting your time with this.

Solution Idea:
I ordered the way of solving this problem.
   1. we are going to take the input(either by hardcoding for this example alone
or by reading a file),

   2. I will create an array of pointers(I think this is basically string) with
three elements ("I"    "C"  "E"),

   3. Turn these into raw bytes with some decoder from cryptopals.
   3.1. If there is no decoder for ASCII strings like we have, turn the text
into hex(encode) and then decode the hex. 3.2. We might need to create three
seperate raw bytes(ICE) for key...

   4. Write a while loop that checks if the input(plaintext)'s each byte has
   been read or not, inside the loop:
   4.1. Have an iterator that counts to 3 and
   has if case when the i == 3 that sets i=0
   4.2. Have a case statement which takes this i as parameter.
   4.2.a. If i == 0, do xor with the first hex_key, iterate to
   the next byte, set i,j += 1;{store the result in result[j]}.
   4.2.b. If i == 1, do xor with the second hex_key, iterate to the next byte,
set i,j += 1; {store the result in result[j]}. 4.2.c. If i == 2, do xor with the
third hex_key, iterate to the next byte, set i,j +=1; {store the result in
result[j]}.
   5. When the input is fully read (and encrypted), loop to print result[].

   Potential considerations:
   - To ensure there is no array overflow for result[], count how many bytes are
there for plaintext after hexDecode.
   - We might use some sort of flag(bool) for when the system reaches the last
byte during xor.

   FIXES:
   - When taking key (ICE) as a string, it's already in raw bytes, so no need
for any extra stuff.
   - No need for switch cases and the for loop, we can use modulo to simplify.
   - No need for flag, strings automatically grow so its not an issue.
*/
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#include <cryptopp/base64.h>

#include <cstring>
#include <iostream>
#include <fstream>

using namespace CryptoPP;

int main()
{
	std::string plaintext = "Burning 'em, if you ain't quick and nimble I "
				"go crazy when I hear a cymbal";

	std::string key = "ICE";
	std::string result;

	for (size_t i = 0; i < plaintext.size();
	     i++) { // We use size_t because size() returns size_t.
		result += plaintext[i] ^ key[i % key.size()];
	}

	std::string hex_output;
	StringSource ss(result, true,
			new HexEncoder(new StringSink(hex_output), false));

	std::cout << "Plaintext: " << plaintext << "\n";
	std::cout << "Key: " << key << "\n";
	std::cout << "Cyphertext: " << hex_output << "\n";

	return 0;
}
