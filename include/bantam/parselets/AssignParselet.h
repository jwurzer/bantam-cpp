#ifndef ASSIGN_PARSELET_H
#define ASSIGN_PARSELET_H

#include <bantam/parselets/InfixParselet.h>
#include <bantam/ParseException.h>
#include <bantam/Parser.h>
#include <bantam/Precedence.h>
#include <bantam/Token.h>
#include <bantam/expressions/AssignExpression.h>
#include <bantam/expressions/Expression.h>
#include <bantam/expressions/NameExpression.h>

namespace bantam
{
namespace parselets
{

/**
 * Parses assignment expressions like "a = b". The left side of an assignment
 * expression must be a simple name like "a", and expressions are
 * right-associative. (In other words, "a = b = c" is parsed as "a = (b = c)").
 */
class AssignParselet: public InfixParselet {
public:
	virtual std::unique_ptr<expressions::Expression> parse(Parser& parser,
			std::unique_ptr<expressions::Expression> left, Token /*token*/) const override {
		std::unique_ptr<expressions::Expression> right =
				parser.parseExpression(precedence::ASSIGNMENT - 1);

		expressions::NameExpression* leftNameExp =
				dynamic_cast<expressions::NameExpression*>(left.get());
		if (!leftNameExp)
			throw ParseException("The left-hand side of an assignment must be a name.");

		std::string name = leftNameExp->getName();
		return std::unique_ptr<expressions::AssignExpression>(
				new expressions::AssignExpression(name, std::move(right)));
	}

	virtual int getPrecedence() const override { return precedence::ASSIGNMENT; }
};

}
}

#endif
