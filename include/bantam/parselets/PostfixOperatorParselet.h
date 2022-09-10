#ifndef POSTFIX_OPERATOR_PARSELET_H
#define POSTFIX_OPERATOR_PARSELET_H

#include <bantam/parselets/InfixParselet.h>
#include <bantam/Token.h>
#include <bantam/expressions/Expression.h>
#include <bantam/expressions/PostfixExpression.h>

namespace bantam
{
namespace parselets
{

/**
 * Generic infix parselet for an unary arithmetic operator. Parses postfix
 * unary "?" expressions.
 */
class PostfixOperatorParselet: public InfixParselet {
public:
	PostfixOperatorParselet(int precedence)
		:mPrecedence(precedence)
	{
	}

	virtual std::unique_ptr<expressions::Expression> parse(Parser& /*parser*/,
			std::unique_ptr<expressions::Expression> left, Token token) const override {
		return std::unique_ptr<expressions::PostfixExpression>(
				new expressions::PostfixExpression(std::move(left), token.getType()));
	}

	virtual int getPrecedence() const override {
		return mPrecedence;
	}

private:
	const int mPrecedence;
};

}
}

#endif
