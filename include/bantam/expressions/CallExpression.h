#ifndef CALL_EXPRESSION_H
#define CALL_EXPRESSION_H

#include <bantam/expressions/Expression.h>
#include <memory>
#include <list>

namespace bantam
{
namespace expressions
{

/**
 * A function call like "a(b, c, d)".
 */
class CallExpression: public Expression {
public:
	CallExpression(std::unique_ptr<Expression> function, std::list<std::unique_ptr<Expression>>& args)
		:mFunction(std::move(function)),
		mArgs(std::move(args))
	{
	}

	virtual void print(std::ostream& builder) const override {
		mFunction->print(builder);
		builder << "(";
		unsigned int i = 0;
		for (const std::unique_ptr<Expression>& arg : mArgs) {
			arg->print(builder);
			if (i + 1 < mArgs.size()) builder << ", ";
			++i;
		}
		builder << ")";
	}

private:
	const std::unique_ptr<Expression>            mFunction;
	const std::list<std::unique_ptr<Expression>> mArgs;
};

}
}

#endif
