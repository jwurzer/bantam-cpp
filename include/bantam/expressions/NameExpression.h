#ifndef NAME_EXPRESSION_H
#define NAME_EXPRESSION_H

#include <bantam/expressions/Expression.h>
#include <string>

namespace bantam
{
namespace expressions
{

/**
 * A simple variable name expression like "abc".
 */
class NameExpression: public Expression {
public:
	NameExpression(const std::string& name)
		:mName(name) {
	}

	std::string getName() const { return mName; }

	virtual void print(std::stringstream& builder) const override {
		builder << mName;
	}

private:
	const std::string mName;
};

}
}

#endif
