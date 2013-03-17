#include "types.h"

using namespace simpletest;
using namespace nlang::types;

int main() {
	SpecReporter reporter(std::cout);
	Suite suite(reporter, "Types");
	suite.add(new TestUniqueness);
	suite.add(new TestPreserveIdentity);
	return suite.main();
}
