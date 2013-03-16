#ifndef types_h
#define types_h

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
	}
}

#endif