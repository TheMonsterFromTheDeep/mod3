#pragma once

#ifndef __INCL_LIST
#define __INCL_LIST

#include "exception.h"

namespace mod3 
{
	template <class T>
	class list
	{
	private:
		T* _data;
		int _length;
	public:
		
		list()
		{
			_data = nullptr;
			_length = 0;
		}

		list(int length)
		{
			void* allocation = new void*[length]; //In case data type doesn't have default, use a void pointer and cast
			_data = static_cast<T*>(allocation);

			_length = length;
		}

		list(int length, T value)
		{
			void* allocation = new void*[length];
			_data = static_cast<T*>(allocation);

			for(int i = 0; i < length; i++) { *(_data + i) = value; } //Populate list with value

			_length = length;
		}

		T operator[] (int index)
		{
			if(index < 0 || index >= _length) { throw new exception("Index out of bounds in list"); }
			else { return *(_data + index); }
		}
	};
}

#endif