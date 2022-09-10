#ifndef BANTAM_PARSER_H
#define BANTAM_PARSER_H

#include <bantam/Parser.h>
#include <bantam/parselets/NameParselet.h>
#include <bantam/parselets/AssignParselet.h>
#include <bantam/parselets/ConditionalParselet.h>
#include <bantam/parselets/GroupParselet.h>
#include <bantam/parselets/CallParselet.h>
#include <bantam/parselets/PostfixOperatorParselet.h>
#include <bantam/parselets/PrefixOperatorParselet.h>
#include <bantam/parselets/BinaryOperatorParselet.h>

namespace bantam
{

/**
 * Extends the generic Parser class with support for parsing the actual Bantam
 * grammar.
 */
class BantamParser: public Parser {
public:
	BantamParser(std::unique_ptr<TokenIterator> tokens)
		:Parser(std::move(tokens))
	{
		// Register all of the parselets for the grammar.

		// Register the ones that need special parselets.
		registerParselet(TokenType::NAME,       std::unique_ptr<parselets::NameParselet>(new parselets::NameParselet()));
		registerParselet(TokenType::ASSIGN,     std::unique_ptr<parselets::AssignParselet>(new parselets::AssignParselet()));
		registerParselet(TokenType::QUESTION,   std::unique_ptr<parselets::ConditionalParselet>(new parselets::ConditionalParselet()));
		registerParselet(TokenType::LEFT_PAREN, std::unique_ptr<parselets::GroupParselet>(new parselets::GroupParselet()));
		registerParselet(TokenType::LEFT_PAREN, std::unique_ptr<parselets::CallParselet>(new parselets::CallParselet()));

		// Register the simple operator parselets.
		prefix(TokenType::PLUS,      precedence::PREFIX);
		prefix(TokenType::MINUS,     precedence::PREFIX);
		prefix(TokenType::TILDE,     precedence::PREFIX);
		prefix(TokenType::BANG,      precedence::PREFIX);

		// For kicks, we'll make "!" both prefix and postfix, kind of like ++.
		postfix(TokenType::BANG,     precedence::POSTFIX);

		infixLeft(TokenType::PLUS,     precedence::SUM);
		infixLeft(TokenType::MINUS,    precedence::SUM);
		infixLeft(TokenType::ASTERISK, precedence::PRODUCT);
		infixLeft(TokenType::SLASH,    precedence::PRODUCT);
		infixRight(TokenType::CARET,   precedence::EXPONENT);
	}

	/**
	 * Registers a postfix unary operator parselet for the given token and
	 * precedence.
	 */
	void postfix(TokenType token, int precedence) {
		registerParselet(token, std::unique_ptr<parselets::PostfixOperatorParselet>(
				new parselets::PostfixOperatorParselet(precedence)));
	}

	/**
	 * Registers a prefix unary operator parselet for the given token and
	 * precedence.
	 */
	void prefix(TokenType token, int precedence) {
		registerParselet(token, std::unique_ptr<parselets::PrefixOperatorParselet>(
				new parselets::PrefixOperatorParselet(precedence)));
	}

	/**
	 * Registers a left-associative binary operator parselet for the given token
	 * and precedence.
	 */
	void infixLeft(TokenType token, int precedence) {
		registerParselet(token, std::unique_ptr<parselets::BinaryOperatorParselet>(
				new parselets::BinaryOperatorParselet(precedence, false)));
	}

	/**
	 * Registers a right-associative binary operator parselet for the given token
	 * and precedence.
	 */
	void infixRight(TokenType token, int precedence) {
		registerParselet(token, std::unique_ptr<parselets::BinaryOperatorParselet>(
				new parselets::BinaryOperatorParselet(precedence, true)));
	}
};

}

#endif
