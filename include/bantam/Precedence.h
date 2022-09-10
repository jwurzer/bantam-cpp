#ifndef PRECEDENCE_H
#define PRECEDENCE_H

namespace bantam
{

/**
 * Defines the different precedence levels used by the infix parsers. These
 * determine how a series of infix expressions will be grouped. For example,
 * "a + b * c - d" will be parsed as "(a + (b * c)) - d" because "*" has higher
 * precedence than "+" and "-". Here, bigger numbers mean higher precedence.
 */
namespace precedence {
	// Ordered in increasing precedence.
	constexpr int ASSIGNMENT  = 1;
	constexpr int CONDITIONAL = 2;
	constexpr int SUM         = 3;
	constexpr int PRODUCT     = 4;
	constexpr int EXPONENT    = 5;
	constexpr int PREFIX      = 6;
	constexpr int POSTFIX     = 7;
	constexpr int CALL        = 8;
}

}

#endif
