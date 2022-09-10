#ifndef BINARY_OPERATOR_PARSELET_H
#define BINARY_OPERATOR_PARSELET_H

#include <bantam/Parser.h>
#include <bantam/Token.h>
#include <bantam/expressions/Expression.h>
#include <bantam/expressions/OperatorExpression.h>

namespace bantam
{
namespace parselets
{

/**
 * Generic infix parselet for a binary arithmetic operator. The only
 * difference when parsing, "+", "-", "*", "/", and "^" is precedence and
 * associativity, so we can use a single parselet class for all of those.
 */
class BinaryOperatorParselet: public InfixParselet {
public:
	BinaryOperatorParselet(int precedence, bool isRight)
		:mPrecedence(precedence),
		mIsRight(isRight)
	{
	}

	virtual std::unique_ptr<expressions::Expression> parse(Parser& parser,
			std::unique_ptr<expressions::Expression> left, Token token) const override {
		// To handle right-associative operators like "^", we allow a slightly
		// lower precedence when parsing the right-hand side. This will let a
		// parselet with the same precedence appear on the right, which will then
		// take *this* parselet's result as its left-hand argument.
		std::unique_ptr<expressions::Expression> right = parser.parseExpression(
				mPrecedence - (mIsRight ? 1 : 0));

		return std::unique_ptr<expressions::OperatorExpression>(
				new expressions::OperatorExpression(std::move(left),
						token.getType(), std::move(right)));
	}

	virtual int getPrecedence() const override {
		return mPrecedence;
	}

private:
	const int mPrecedence;
	const bool mIsRight;
};

}
}

#endif
