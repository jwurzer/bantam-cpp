#ifndef PREFIX_OPERATOR_PARSELET
#define PREFIX_OPERATOR_PARSELET

#include <bantam/Parser.h>
#include <bantam/Token.h>
#include <bantam/expressions/Expression.h>
#include <bantam/expressions/PrefixExpression.h>

namespace bantam
{
namespace parselets
{

/**
 * Generic prefix parselet for an unary arithmetic operator. Parses prefix
 * unary "-", "+", "~", and "!" expressions.
 */
class PrefixOperatorParselet: public PrefixParselet {
public:
	PrefixOperatorParselet(int precedence)
		:mPrecedence(precedence)
	{
	}

	virtual std::unique_ptr<expressions::Expression> parse(
			Parser& parser, Token token) const override {
		// To handle right-associative operators like "^", we allow a slightly
		// lower precedence when parsing the right-hand side. This will let a
		// parselet with the same precedence appear on the right, which will then
		// take *this* parselet's result as its left-hand argument.
		std::unique_ptr<expressions::Expression> right = parser.parseExpression(mPrecedence);

		return std::unique_ptr<expressions::PrefixExpression>(
				new expressions::PrefixExpression(token.getType(), std::move(right)));
	}

	// not necessary. PrefixParselet doesn't have abstract function getPrecedence().
	//virtual int getPrecedence() const override {
	//	return mPrecedence;
	//}

private:
	const int mPrecedence;
};

}
}

#endif
