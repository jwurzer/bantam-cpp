#ifndef ASSIGN_EXPRESSION_H
#define ASSIGN_EXPRESSION_H

#include <bantam/expressions/Expression.h>
#include <string>
#include <memory>

namespace bantam
{
namespace expressions
{

/**
 * An assignment expression like "a = b".
 */
class AssignExpression: public Expression {
public:
	AssignExpression(const std::string& name, std::unique_ptr<Expression> right)
		:mName(name),
		mRight(std::move(right))
	{
	}

	virtual void print(std::stringstream& builder) const override {
		builder << "(" << mName << " = ";
		mRight->print(builder);
		builder << ")";
	}

private:
	const std::string                 mName;
	const std::unique_ptr<Expression> mRight;
};

}
}

#endif
