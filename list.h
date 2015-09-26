#pragma once

#ifndef __INCL_LIST
#define __INCL_LIST

#include <new> //Used for bad_alloc errors
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

		void add(T value);
		void expand(int length);

		void set(int index, T value)
		{
			if(index < 0 || index >= _length) { throw new exception("Index out of bounds in list"); }
			else { *(_data + index) = value; }
		}

	};

	template<class T>
	void list<T>::add(T value) {
		T* tmp = _data;

		void* allocation = new void*[_length + 1];
		_data = static_cast<T*>(allocation);

		for(int i = 0; i < _length; i++) //length still has old value
		{
			*(_data + i) = *(tmp + i);
		}

		delete[] tmp;

		*(_data + _length) = value; //Set new value at largest index of new array

		_length++;
	}

	template<class T>
	void list<T>::expand(int length)
	{
		T* tmp = _data;

		void* allocation = new void*[_length + 1];
		_data = static_cast<T*>(allocation);

		for(int i = 0; i < _length; i++)
		{
			*(_data + i) = *(tmp + i);
		}

		delete[] tmp;

		_length += length;
	}

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
		T& get(int index) 
		{
			if(index < 0 || index >= _length) { throw exception("Index out of bounds in list"); }
			else {
				try {
					return *(static_cast<T*>(_data) + index);
				}
				catch (std::bad_alloc& err) {
					throw exception("Error returning object."); //TODO: make exception messages better
				}
			}
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