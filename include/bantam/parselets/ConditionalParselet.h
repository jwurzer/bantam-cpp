#ifndef CONDITIONAL_PARSELET_H
#define CONDITIONAL_PARSELET_H

#include <bantam/Parser.h>
#include <bantam/Precedence.h>
#include <bantam/Token.h>
#include <bantam/TokenType.h>
#include <bantam/expressions/ConditionalExpression.h>
#include <bantam/expressions/Expression.h>

namespace bantam
{
namespace parselets
{

/**
 * Parselet for the condition or "ternary" operator, like "a ? b : c".
 */
class ConditionalParselet: public InfixParselet {
	virtual std::unique_ptr<expressions::Expression> parse(Parser& parser,
			std::unique_ptr<expressions::Expression> left, Token /*token*/) const override {
		std::unique_ptr<expressions::Expression> thenArm = parser.parseExpression();
		parser.consume(TokenType::COLON);
		std::unique_ptr<expressions::Expression> elseArm = parser.parseExpression(precedence::CONDITIONAL - 1);

		return std::unique_ptr<expressions::ConditionalExpression>(
				new expressions::ConditionalExpression(std::move(left), std::move(thenArm), std::move(elseArm)));
	}

	virtual int getPrecedence() const override {
		return precedence::CONDITIONAL;
	}
};

}
}

#endif
