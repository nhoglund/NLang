#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include "types.h"

using namespace nlang::types;

BOOST_AUTO_TEST_CASE(types_are_unique)
{
	Type t1;
	Type t2;

	BOOST_CHECK(t1 != t2);
	BOOST_CHECK(!(t1 == t2));
}
BOOST_AUTO_TEST_CASE(copying_types_preserves_identity)
{
	Type t1;
	Type t2(t1);

	BOOST_CHECK(t1 == t2);
}