#include <simpletest.h>
#include <sstream>

using namespace simpletest;

class TrivialTest : public Test {
public:
	void execute() {
		describe("Trivial test");
		assert(true, "true is true");
	}
};

class TrivialTestNoDescription : public Test {
public:
	void execute() {
		assert(true, "true is true");
	}
};

class ExecuteSingleTestInSuite : public Test {
	void execute() {
		describe("Execute a single test in a test suite");

		std::stringstream result;
		SpecReporter reporter(result);
		Suite suite(reporter);
		suite.add(new TrivialTest);
		int exit_code = suite.main();

		assert(result.str() == "\n  Trivial test\n    - true is true\n\n  1 test complete.\n\n", "the output is correct");
		assert(exit_code == 0, "the error code is 0");
	}
};

class FailingTest : public Test {
public:
	void execute() {
		assert(false, "false is not true");
	}
};

class ExecuteFailingTest : public Test {
	void execute() {
		describe("Execute a failing test in a test suite");

		std::stringstream result;
		SpecReporter reporter(result);
		Suite suite(reporter);
		suite.add(new FailingTest);
		int exit_code = suite.main();

		assert(result.str() == "\n  X false is not true\n\n  1 test complete.  1 test failed.\n\n", "the output is correct");
		assert(exit_code == 1, "the error code is 1");
	}
};

int main() {
	SpecReporter reporter(std::cout);
	Suite suite(reporter);
	suite.add(new TrivialTestNoDescription);
	suite.add(new TrivialTest);
	suite.add(new TrivialTestNoDescription);
	suite.add(new ExecuteSingleTestInSuite);
	suite.add(new ExecuteFailingTest);
	return suite.main();
}