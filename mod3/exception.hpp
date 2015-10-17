#ifndef __INCL_EXCEPTION
#define __INCL_EXCEPTION

namespace mod3 {
	class exception {
	private:
		char* _message;
	public:
		exception(char* msg) { 
			_message = msg;
		}

		char* message() {
			return _message;
		}
	};
};

#endif