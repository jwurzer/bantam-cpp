#ifndef CONDITIONAL_EXPRESSION_H
#define CONDITIONAL_EXPRESSION_H

#include <bantam/expressions/Expression.h>
#include <memory>

namespace bantam
{
namespace expressions
{

/**
 * A ternary conditional expression like "a ? b : c".
 */
class ConditionalExpression: public Expression {
public:
	ConditionalExpression(std::unique_ptr<Expression> condition,
			std::unique_ptr<Expression> thenArm,
			std::unique_ptr<Expression> elseArm)
		:mCondition(std::move(condition)),
		mThenArm(std::move(thenArm)),
		mElseArm(std::move(elseArm))
	{
	}

	virtual void print(std::stringstream& builder) const override {
		builder << "(";
		mCondition->print(builder);
		builder << " ? ";
		mThenArm->print(builder);
		builder << " : ";
		mElseArm->print(builder);
		builder << ")";
	}

private:
	const std::unique_ptr<Expression> mCondition;
	const std::unique_ptr<Expression> mThenArm;
	const std::unique_ptr<Expression> mElseArm;
};

}
}

#endif
