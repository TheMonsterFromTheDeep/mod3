#pragma once

#ifndef __INCL_EXCEPTION
#define __INCL_EXCEPTION

namespace mod3
{
	class exception
	{
	private:
		const char* _message;
	public:
		exception(const char* msg) { _message = msg; }

		const char* message() {
			return _message;
		}
	};
};

#endif

//end of file