#include <bantam/Lexer.h>
#include <bantam/BantamParser.h>
#include <bantam/expressions/Expression.h>
#include <string>
#include <iostream>
#include <sstream>

using namespace bantam;

static int sPassed = 0;
static int sFailed = 0;

/**
 * Parses the given chunk of code and verifies that it matches the expected
 * pretty-printed result.
 */
static void test(const std::string& source, const std::string& expected);

int main()
{
	// Function call.
	test("a()", "a()");
	test("a(b)", "a(b)");
	test("a(b, c)", "a(b, c)");
	test("a(b)(c)", "a(b)(c)");
	test("a(b) + c(d)", "(a(b) + c(d))");
	test("a(b ? c : d, e + f)", "a((b ? c : d), (e + f))");

	// Unary precedence.
	test("~!-+a", "(~(!(-(+a))))");
	test("a!!!", "(((a!)!)!)");

	// Unary and binary predecence.
	test("-a * b", "((-a) * b)");
	test("!a + b", "((!a) + b)");
	test("~a ^ b", "((~a) ^ b)");
	test("-a!",    "(-(a!))");
	test("!a!",    "(!(a!))");

	// Binary precedence.
	test("a = b + c * d ^ e - f / g", "(a = ((b + (c * (d ^ e))) - (f / g)))");

	// Binary associativity.
	test("a = b = c", "(a = (b = c))");
	test("a + b - c", "((a + b) - c)");
	test("a * b / c", "((a * b) / c)");
	test("a ^ b ^ c", "(a ^ (b ^ c))");

	// Conditional operator.
	test("a ? b : c ? d : e", "(a ? b : (c ? d : e))");
	test("a ? b ? c : d : e", "(a ? (b ? c : d) : e)");
	test("a + b ? c * d : e / f", "((a + b) ? (c * d) : (e / f))");

	// Grouping.
	test("a + (b + c) + d", "((a + (b + c)) + d)");
	test("a ^ (b + c)", "(a ^ (b + c))");
	test("(!a)!",    "((!a)!)");

	// Show the results.
	if (sFailed == 0) {
		std::cout << "Passed all " << sPassed << " tests." << std::endl;
	} else {
		std::cout << "----";
		std::cout << "Failed " << sFailed << " out of " +
				(sFailed + sPassed) << " tests." << std::endl;
	}
}

/**
 * Parses the given chunk of code and verifies that it matches the expected
 * pretty-printed result.
 */
static void test(const std::string& source, const std::string& expected)
{
	std::unique_ptr<Lexer> lexer(new Lexer(source));
	std::unique_ptr<Parser> parser(new BantamParser(std::move(lexer)));

	try {
		std::unique_ptr<expressions::Expression> result = parser->parseExpression();
		std::stringstream builder;
		result->print(builder);
		std::string actual = builder.str();

		if (expected == actual) {
			sPassed++;
		} else {
			sFailed++;
			std::cout << "[FAIL] Expected: " << expected << std::endl;
			std::cout << "         Actual: " << actual << std::endl;
		}
	} catch (const ParseException& ex) {
		sFailed++;
		std::cout << "[FAIL] Expected: " << expected << std::endl;
		std::cout << "          Error: " << ex.what() << std::endl;
	}
}

