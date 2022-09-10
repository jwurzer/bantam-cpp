#ifndef PARSER_H
#define PARSER_H

#include <bantam/TokenIterator.h>
#include <bantam/ParseException.h>
#include <bantam/expressions/Expression.h>
#include <bantam/parselets/InfixParselet.h>
#include <bantam/parselets/PrefixParselet.h>

#include <vector>
#include <map>

namespace bantam
{

class Parser {
public:
	Parser(std::unique_ptr<TokenIterator> tokens)
		:mTokens(std::move(tokens))
	{
	}

	virtual ~Parser() = default;

	void registerParselet(TokenType token, std::unique_ptr<parselets::PrefixParselet> parselet) {
		mPrefixParselets[token] = std::move(parselet);
	}

	void registerParselet(TokenType token, std::unique_ptr<parselets::InfixParselet> parselet) {
		mInfixParselets[token] = std::move(parselet);
	}

	std::unique_ptr<expressions::Expression> parseExpression(int precedence) {
		Token token = consume();
		auto it = mPrefixParselets.find(token.getType());

		if (it == mPrefixParselets.end())
			throw ParseException("Could not parse \"" + token.getText() + "\".");

		parselets::PrefixParselet* prefix = it->second.get();

		std::unique_ptr<expressions::Expression> left = prefix->parse(*this, token);

		while (precedence < getPrecedence()) {
			token = consume();

			parselets::InfixParselet* infix = mInfixParselets[token.getType()].get();
			left = infix->parse(*this, std::move(left), token);
		}

		return left;
	}

	std::unique_ptr<expressions::Expression> parseExpression() {
		return parseExpression(0);
	}

	bool match(TokenType expected) {
		Token token = lookAhead(0);
		if (token.getType() != expected) {
			return false;
		}

		consume();
		return true;
	}

	Token consume(TokenType expected) {
		Token token = lookAhead(0);
		if (token.getType() != expected) {
			throw ParseException("Expected token " + tokentype::toString(expected) +
					" and found " + tokentype::toString(token.getType()));
		}

		return consume();
	}

	Token consume() {
		// Make sure we've read the token.
		lookAhead(0);

		Token front = mRead.front();
		mRead.erase(mRead.begin());
		return front;
	}

private:
	Token lookAhead(unsigned int distance) {
		// Read in as many as needed.
		while (distance >= mRead.size()) {
			mRead.push_back(mTokens->next());
		}

		// Get the queued token.
		return mRead[distance];
	}

	int getPrecedence() {
		auto itParser = mInfixParselets.find(lookAhead(0).getType());
		if (itParser != mInfixParselets.end()) return itParser->second->getPrecedence();

		return 0;
	}

	const std::unique_ptr<TokenIterator> mTokens;
	std::vector<Token> mRead;
	std::map<TokenType, std::unique_ptr<parselets::PrefixParselet>> mPrefixParselets;
	std::map<TokenType, std::unique_ptr<parselets::InfixParselet>> mInfixParselets;
};

}

#endif
