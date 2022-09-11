#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <ostream>

namespace bantam
{
namespace expressions
{

/**
 * Interface for all expression AST node classes.
 */
class Expression {
public:
	virtual ~Expression() = default;
	/**
	 * Pretty-print the expression to a string.
	 */
	virtual void print(std::ostream& builder) const = 0;
};

}
}

#endif
