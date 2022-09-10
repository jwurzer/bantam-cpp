#ifndef LEXER_ITERATOR_H
#define LEXER_ITERATOR_H

#include <bantam/TokenIterator.h>
#include <map>
#include <string>

namespace bantam
{

/**
 * A very primitive lexer. Takes a string and splits it into a series of
 * Tokens. Operators and punctuation are mapped to unique keywords. Names,
 * which can be any series of letters, are turned into NAME tokens. All other
 * characters are ignored (except to separate names). Numbers and strings are
 * not supported. This is really just the bare minimum to give the parser
 * something to work with.
 */
class Lexer: public TokenIterator {
public:
	/**
	 * Creates a new Lexer to tokenize the given string.
	 * @param text String to tokenize.
	 */
	Lexer(const std::string& text)
		:mText(text),
		mIndex(0)
	{
		// Register all of the TokenTypes that are explicit punctuators.
		for (int tt = 0; tt <= static_cast<int>(TokenType::END_OF_FILE); ++tt) {
			TokenType type = static_cast<TokenType>(tt);
			char punctuator = tokentype::punctuator(type);
			if (punctuator != '\0') {
				mPunctuators[punctuator] = type;
			}
		}
	}

	virtual bool hasNext() const override {
		return true;
	}

	virtual Token next() override {
		while (mIndex < mText.length()) {
			char c = mText[mIndex++];

			if (mPunctuators.count(c) > 0) {
				// Handle punctuation.
				return Token(mPunctuators.at(c), std::string(1, c));
			} else if (isalpha(c)) {
				// Handle names.
				int start = mIndex - 1;
				while (mIndex < mText.length()) {
					if (!isalpha(mText[mIndex])) break;
					mIndex++;
				}

				std::string name = mText.substr(start, mIndex - start);
				return Token(TokenType::NAME, name);
			} else {
				// Ignore all other characters (whitespace, etc.)
			}
		}

		// Once we've reached the end of the string, just return EOF tokens. We'll
		// just keeping returning them as many times as we're asked so that the
		// parser's lookahead doesn't have to worry about running out of tokens.
		return Token(TokenType::END_OF_FILE, "");
	}

private:
	std::map<char, TokenType> mPunctuators;
	std::string mText;
	unsigned int mIndex = 0;
};

}

#endif
