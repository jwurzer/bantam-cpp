#ifndef POSTFIX_EXPRESSION_H
#define POSTFIX_EXPRESSION_H

#include <bantam/expressions/Expression.h>
#include <bantam/TokenType.h>
#include <memory>

namespace bantam
{
namespace expressions
{

/**
 * A postfix unary arithmetic expression like "a!".
 */
class PostfixExpression: public Expression {
public:
	PostfixExpression(std::unique_ptr<Expression> left, TokenType operatorType)
		:mLeft(std::move(left)),
		mOperator(operatorType)
	{
	}

	virtual void print(std::ostream& builder) const override {
		builder << "(";
		mLeft->print(builder);
		builder << bantam::tokentype::punctuator(mOperator) << ")";
	}

private:
	const std::unique_ptr<Expression> mLeft;
	const TokenType                   mOperator;
};

}
}

#endif
