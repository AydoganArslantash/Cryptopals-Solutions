/*
  Challenge 1.3: Single-Byte XOR Cipher
  Description:
  The hex encoded string:

  1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736

  ... has been XOR'd against a single character. Find the key, decrypt the
  message. You can do this by hand. But don't: write code to do it for you.

  How? Devise some method for "scoring" a piece of English plaintext. Character
  frequency is a good metric. Evaluate each output and choose the one with the
  best score.

  Solved by: Aydogan Arslantash
  Date: <2026-02-10 Tue 19:20>


  Solution Idea 1#: The first thing that comes to my mind is to create an ASCII
  map and XOR against this given encoded string (after turning both of these to
  raw bytes) and using a NLP library which will check how each output with
  different characters as keys and compare them by evaluating which one makes
  more sense as a sentence but this would be unnecessarily heavy.
 */

#include <iostream>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#include <cryptopp/base64.h>

using namespace CryptoPP;

int score_calc(const std::string &text);

int main()
{
	std::string usr_input = "1b37373331363f78151b7f2b783431333d78397828372d"
				"363c78373e783a393b3736";
	std::string cyphertext;

	StringSource ss1(usr_input, true,
			 new HexDecoder(new StringSink(cyphertext)));

	int best_score = 0;
	char best_key = 0;
	std::string best_plaintext;

	for (int key = 0; key < 256; key++) {
		// IDEA STEP 2: DO XOR.
		std::string temp_plaintext;
		for (size_t i = 0; i < cyphertext.size(); i++) {
			temp_plaintext += cyphertext[i] ^ key;
		}

		// Score the result.
		int current_score = score_calc(temp_plaintext);

		// If its the best:
		if (current_score > best_score) {
			best_score = current_score;
			best_key = key;
			best_plaintext = temp_plaintext;
		}
	}

	std::cout << "Best key: " << (int)best_key << " ('" << best_key
		  << "')\n";
	std::cout << "Best score: " << best_score << "\n";
	std::cout << "Message: " << best_plaintext << "\n";

	return 0;
}

int score_calc(const std::string &text)
{
	int score = 0;

	// Looping through every character in the text.
	for (char c : text) {
		// If there is space:
		if (c == ' ')
			score += 3;

		// Checking common letters (e t a o i n):
		else if (c == 'e' || c == 'E' || c == 't' || c == 'T' ||
			 c == 'a' || c == 'A' || c == 'o' || c == 'O' ||
			 c == 'i' || c == 'I' || c == 'n' || c == 'N')
			score += 2;

		// Less Common letters:
		else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
			score += 1;

		// Punctuation and digits:
		else if ((c >= '0' && c <= '9') || c == '.' || c == ',' ||
			 c == '!' || c == '?' || c == '\'' || c == '"' ||
			 c == ';' || c == ':')
			score += 1;

		// This part is to penalise unprintable characters (they are not
		// part of english alphabet)
		else if (c < 32 || c > 126)
			score -= 5;

		else
			score += 0;
	}
	return score;
}
