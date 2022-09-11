#ifndef OPERATOR_EXPRESSION_H
#define OPERATOR_EXPRESSION_H

#include <bantam/expressions/Expression.h>
#include <bantam/TokenType.h>
#include <memory>

namespace bantam
{
namespace expressions
{

/**
 * A binary arithmetic expression like "a + b" or "c ^ d".
 */
class OperatorExpression: public Expression {
public:
	OperatorExpression(std::unique_ptr<Expression> left,
			TokenType operatorType, std::unique_ptr<Expression> right)
		:mLeft(std::move(left)),
		mOperator(operatorType),
		mRight(std::move(right))
	{
	}

	virtual void print(std::ostream& builder) const override {
		builder << "(";
		mLeft->print(builder);
		builder << " " << bantam::tokentype::punctuator(mOperator) << " ";
		mRight->print(builder);
		builder << ")";
	}

private:
	const std::unique_ptr<Expression> mLeft;
	const TokenType                   mOperator;
	const std::unique_ptr<Expression> mRight;
};

}
}

#endif
