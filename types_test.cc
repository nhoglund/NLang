#include "types.h"

using namespace simpletest;
using namespace nlang::types;

int main() {
	Suite suite("Types");
	suite.add(new TestUniqueness);
	suite.add(new TestPreserveIdentity);
	return suite.main();
}
