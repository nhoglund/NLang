#ifndef types_h
#define types_h

#include <simpletest.h>

namespace nlang {
	namespace types {
		typedef long TypeId;

		class Type {
		public:
			Type();
			bool operator==(const Type& t) {return _id == t._id;}
			bool operator!=(const Type& t) {return !(*this == t);}
			
		private:
			TypeId	_id;
		};

		class TestUniqueness : public simpletest::Test {
			void execute() {
				describe("Different types");

				Type t1;
				Type t2;
				assert(t1 != t2, "compare as different");
				assert(!(t1 == t2), "do not compare as equal");
			}
		};

		class TestPreserveIdentity : public simpletest::Test {
			void execute() {
				describe("A copy of a type");
			
				Type t1;
				Type t2(t1);

				assert(t1 == t2, "keep its identity");

			}
		};
	}
}

#endif