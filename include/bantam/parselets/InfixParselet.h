#ifndef INFIX_PARSELET
#define INFIX_PARSELET

#include <bantam/Token.h>
#include <bantam/expressions/Expression.h>
#include <memory>

namespace bantam
{
class Parser;

namespace parselets
{

/**
 * One of the two parselet interfaces used by the Pratt parser. An
 * InfixParselet is associated with a token that appears in the middle of the
 * expression it parses. Its parse() method will be called after the left-hand
 * side has been parsed, and it in turn is responsible for parsing everything
 * that comes after the token. This is also used for postfix expressions, in
 * which case it simply doesn't consume any more tokens in its parse() call.
 */
class InfixParselet {
public:
	virtual ~InfixParselet() = default;
	virtual std::unique_ptr<expressions::Expression> parse(Parser& parser,
			std::unique_ptr<expressions::Expression> left, Token token) const = 0;
	virtual int getPrecedence() const = 0;
};

}
}

#endif
