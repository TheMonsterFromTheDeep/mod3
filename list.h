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

		list(int length);
		list(int length, T value);

		T get(int index)
		{
			if(index < 0 || index >= _length) { throw new exception("Index out of bounds in list"); }
			else { return *(_data + index); }
		}

		T& operator[] (int index) //Returns a reference so value can be modified
		{
			if(index < 0 || index >= _length) { throw new exception("Index out of bounds in list"); }
			else { return *(_data + index); }
		}

		void set(int index, T value)
		{
			if(index < 0 || index >= _length) { throw new exception("Index out of bounds in list"); }
			else { *(_data + index) = value; }
		}

	};

	template<>
	class list<void>
	{
	private:
		void* _data;
		int _length;
	public:
		list()
		{
			_data = nullptr;
			_length = 0;
		}

		list(int length)
		{
			_data = new void*[length];
			_length = length;
		}

		template<class T>
		T get(int index)
		{
			if(index < 0 || index >= _length) { throw new exception("Index out of bounds in list"); }
			else { return *(static_cast<T*>(_data) + index); }
		}

		template<class T>
		void set(int index, T value);
	};

	template<class T>
	list<T>::list(int length)
	{
		void* allocation = new void*[length]; //In case data type doesn't have default, use a void pointer and cast
		_data = static_cast<T*>(allocation);

		_length = length;
	}

	template<class T>
	list<T>::list(int length, T value)
	{
		void* allocation = new void*[length];
		_data = static_cast<T*>(allocation);

		for(int i = 0; i < length; i++) { *(_data + i) = value; } //Populate list with value

		_length = length;
	}

	template<class T>
	void list<void>::set(int index, T value)
	{
		if(index < 0 || index >= _length) { throw new exception("Index out of bounds in list"); }
		else
		{
			T* tmp = static_cast<T*>(_data);
			*(tmp + index) = value;
		}
	}
}

#endif

//end of file