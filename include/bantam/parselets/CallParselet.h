#ifndef CALL_PARSELET_H
#define CALL_PARSELET_H

#include <bantam/Parser.h>
#include <bantam/Precedence.h>
#include <bantam/Token.h>
#include <bantam/TokenType.h>
#include <bantam/expressions/CallExpression.h>
#include <bantam/expressions/Expression.h>
#include <list>

namespace bantam
{
namespace parselets
{

/**
 * Parselet to parse a function call like "a(b, c, d)".
 */
class CallParselet: public InfixParselet {
	virtual std::unique_ptr<expressions::Expression> parse(Parser& parser,
			std::unique_ptr<expressions::Expression> left, Token /*token*/) const override {
		// Parse the comma-separated arguments until we hit, ")".
		std::list<std::unique_ptr<expressions::Expression>> args;

		// There may be no arguments at all.
		if (!parser.match(TokenType::RIGHT_PAREN)) {
			do {
				args.push_back(parser.parseExpression());
			} while (parser.match(TokenType::COMMA));
			parser.consume(TokenType::RIGHT_PAREN);
		}

		return std::unique_ptr<expressions::CallExpression>(
				new expressions::CallExpression(std::move(left), args));
	}

	virtual int getPrecedence() const override {
		return precedence::CALL;
	}
};

}
}

#endif
