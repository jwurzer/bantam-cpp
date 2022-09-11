#ifndef PREFIX_EXPRESSION_H
#define PREFIX_EXPRESSION_H

#include <bantam/expressions/Expression.h>
#include <bantam/TokenType.h>
#include <memory>

namespace bantam
{
namespace expressions
{

/**
 * A prefix unary arithmetic expression like "!a" or "-b".
 */
class PrefixExpression: public Expression {
public:
	PrefixExpression(TokenType operatorType, std::unique_ptr<Expression> right)
		:mOperator(operatorType),
		mRight(std::move(right))
	{
	}

	virtual void print(std::ostream& builder) const override {
		builder << "(" << bantam::tokentype::punctuator(mOperator);
		mRight->print(builder);
		builder << ")";
	}

private:
	const TokenType  mOperator;
	const std::unique_ptr<Expression> mRight;
};

}
}

#endif
