#include <atomic>
#include "types.h"

namespace nlang {
	namespace types {
		// Generates a sequence of integers to use to identify the uniqueness of types
		TypeId generate_new_type_id() {
			static std::atomic<TypeId> unique(0);
			return ++unique;
		}
	
		Type::Type() : _id(generate_new_type_id()) {}
	}
}
