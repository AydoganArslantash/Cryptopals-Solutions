/*
 * Challange 1.4: Detect single-character XOR
 * Description:
 * One of the 60 character strings in the file "4.txt" has been encrypted by
 * single-character XOR. Find it.
 *
 * (Your code from #3 should help.)
 *
 * Thought process: I will mostly copy paste from the #3 and just write a
 * fileread thing that will read 60 characters one by one and apply the key. So:
 * Disect the file 60-char by 60-char -> Feed each 60 char chunk into HexDecoder
 * to get raw bytes -> try the key finding thing -> if found keep the key,
 * plaintext and cyphertext and stop executing -> if not, feed the next chunk.


 * Solved by: Aydogan Arslantash
 * Date: <2026-02-10 Tue 23:45>
 */

#include <climits>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#include <cryptopp/base64.h>

#include <cstring>
#include <iostream>
#include <fstream>

using namespace CryptoPP;

int score_calc(const std::string &text);

struct best_result {
	std::string best_cyphertext;
	std::string best_plaintext;
	int best_score;
	char best_key;

	void printInternalData()
	{
		std::cout << "Ciphertext (hex): " << best_cyphertext << "\n";
		std::cout << "Plaintext: " << best_plaintext << "\n";
		std::cout << "Score: " << best_score << "\n";
		std::cout << "Key: " << (int)best_key << " ('" << best_key
			  << "')\n";
	}
};

int main()
{
	std::ifstream file("4.txt");
	if (!file) {
		std::cout << "Something wrong with the file";
		return -1;
	}

	// Tracking the best result across all iterations.
	int global_best_score = 0;
	char global_best_key = 0;
	std::string global_best_plaintext;
	std::string global_best_cyphertext;

	// Need it to read the file line by line.
	std::string line;
	int line_number = 0;

	while (std::getline(file, line)) {
		line_number++;

		// Edge case: Skipping if empty line.
		if (line.empty())
			continue;

		// Decoding hex line to raw bytes for XOR operation.
		std::string cyphertext;
		StringSource ss1(line, true,
				 new HexDecoder(new StringSink(cyphertext)));

		// Trying all 256 possible keys (ASCII) for the current line;
		int best_score_cur_line = 0;
		char best_key_cur_line = 0;
		std::string best_plaintext_cur_line;

		for (int key = 0; key < 256; key++) {
			// XOR with current key.
			std::string temp_plaintext;
			for (size_t i = 0; i < cyphertext.size(); i++) {
				temp_plaintext += cyphertext[i] ^ key;
			}

			// Score the result.
			int current_score = score_calc(temp_plaintext);

			// Different from Chal #3, we now need to check if its
			// best for this line and global one.

			// Best for current line?
			if (current_score > best_score_cur_line) {
				best_score_cur_line = current_score;
				best_plaintext_cur_line = temp_plaintext;
				best_key_cur_line = key;
			}
		}
		// Better than global?
		if (best_score_cur_line > global_best_score) {
			global_best_score = best_score_cur_line;
			global_best_key = best_key_cur_line;
			global_best_plaintext = best_plaintext_cur_line;
			global_best_cyphertext = line;

			std::cout << "NEW best found at line " << line_number
				  << " (score: " << global_best_score << ")\n";
		}
	}
	file.close();
	std::cout << "******* Final Result *******\n";
	best_result result{global_best_cyphertext, global_best_plaintext,
			   global_best_score, global_best_key};
	result.printInternalData();
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
