#ifndef GROUP_PARSELET_H
#define GROUP_PARSELET_H

#include <bantam/Parser.h>
#include <bantam/Token.h>
#include <bantam/TokenType.h>
#include <bantam/expressions/Expression.h>

namespace bantam
{
namespace parselets
{

/**
 * Parses parentheses used to group an expression, like "a * (b + c)".
 */
class GroupParselet: public PrefixParselet {
	virtual std::unique_ptr<expressions::Expression> parse(
			Parser& parser, Token /*token*/) const override {
		std::unique_ptr<expressions::Expression> expression = parser.parseExpression();
		parser.consume(TokenType::RIGHT_PAREN);
		return expression;
	}
};

}
}

#endif
