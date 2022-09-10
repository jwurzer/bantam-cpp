#ifndef PREFIX_PARSELET
#define PREFIX_PARSELET

#include <bantam/Token.h>
#include <bantam/expressions/Expression.h>
#include <memory>

namespace bantam
{
class Parser;

namespace parselets
{

/**
 * One of the two interfaces used by the Pratt parser. A PrefixParselet is
 * associated with a token that appears at the beginning of an expression. Its
 * parse() method will be called with the consumed leading token, and the
 * parselet is responsible for parsing anything that comes after that token.
 * This interface is also used for single-token expressions like variables, in
 * which case parse() simply doesn't consume any more tokens.
 * @author rnystrom
 *
 */
class PrefixParselet {
public:
	virtual ~PrefixParselet() = default;
	virtual std::unique_ptr<expressions::Expression> parse(
			Parser& parser, Token token) const = 0;
};

}
}

#endif
