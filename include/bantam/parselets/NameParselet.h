#ifndef NAME_PARSELET
#define NAME_PARSELET

#include <bantam/parselets/PrefixParselet.h>
#include <bantam/Token.h>
#include <bantam/expressions/Expression.h>
#include <bantam/expressions/NameExpression.h>

namespace bantam
{
namespace parselets
{

/**
 * Simple parselet for a named variable like "abc".
 */
class NameParselet: public PrefixParselet {
	virtual std::unique_ptr<expressions::Expression> parse(
			Parser& /*parser*/, Token token) const override {
		return std::unique_ptr<expressions::NameExpression>(
				new expressions::NameExpression(token.getText()));
	}
};

}
}

#endif
