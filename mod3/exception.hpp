#ifndef __INCL_EXCEPTION
#define __INCL_EXCEPTION

namespace mod3 {
	class Exception {
	public:
		char* message;

		Exception(char* msg) : message(msg) { }
	};
};

#endif