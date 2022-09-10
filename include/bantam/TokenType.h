#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

#include <string>

namespace bantam
{

enum class TokenType {
	LEFT_PAREN = 0,
	RIGHT_PAREN,
	COMMA,
	ASSIGN,
	PLUS,
	MINUS,
	ASTERISK,
	SLASH,
	CARET,
	TILDE,
	BANG,
	QUESTION,
	COLON,
	NAME,
	END_OF_FILE, // should be the last one
};

namespace tokentype
{
/**
 * If the TokenType represents a punctuator (i.e. a token that can split an
 * identifier like '+', this will get its text.
 */
static inline char punctuator(TokenType tokenType) {
	switch (tokenType) {
	case bantam::TokenType::LEFT_PAREN:  return '(';
	case bantam::TokenType::RIGHT_PAREN: return ')';
	case bantam::TokenType::COMMA:       return ',';
	case bantam::TokenType::ASSIGN:      return '=';
	case bantam::TokenType::PLUS:        return '+';
	case bantam::TokenType::MINUS:       return '-';
	case bantam::TokenType::ASTERISK:    return '*';
	case bantam::TokenType::SLASH:       return '/';
	case bantam::TokenType::CARET:       return '^';
	case bantam::TokenType::TILDE:       return '~';
	case bantam::TokenType::BANG:        return '!';
	case bantam::TokenType::QUESTION:    return '?';
	case bantam::TokenType::COLON:       return ':';
	default:                             return '\0';
	}
}

static inline std::string toString(TokenType tokenType) {
	switch (tokenType) {
	case TokenType::LEFT_PAREN: return "LEFT_PAREN";
	case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
	case TokenType::COMMA: return "COMMA";
	case TokenType::ASSIGN: return "ASSIGN";
	case TokenType::PLUS: return "PLUS";
	case TokenType::MINUS: return "MINUS";
	case TokenType::ASTERISK: return "ASTERISK";
	case TokenType::SLASH: return "SLASH";
	case TokenType::CARET: return "CARET";
	case TokenType::TILDE: return "TILDE";
	case TokenType::BANG: return "BANG";
	case TokenType::QUESTION: return "QUESTION";
	case TokenType::COLON: return "COLON";
	case TokenType::NAME: return "NAME";
	case TokenType::END_OF_FILE: return "END_OF_FILE";
	}
	return "unknown";
}

}

}

#endif
