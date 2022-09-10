#ifndef TOKEN_ITERATOR_H
#define TOKEN_ITERATOR_H

#include <bantam/Token.h>

namespace bantam
{
	class TokenIterator
	{
	public:
		virtual ~TokenIterator() = default;
		virtual bool hasNext() const = 0;
		virtual Token next() = 0;
	};
}

#endif
