#ifndef __INCL_LIST
#define __INCL_LIST

#include <new> //Used for bad_alloc errors
#include "memory.hpp" //For getNullified() and c_size
#include "exception.hpp"

namespace mod3 
{
	template <class T>
	class list
	{
	private:
		T* _data;
		idx _length;
	public:
		
		list()
		{
			_data = nullptr;
			_length = 0;
		}

		list(idx length);
		list(idx length, T value);

		T get(idx index) const
		{
			if(index >= _length) { throw exception("Index out of bounds in list"); }
			else { return *(_data + index); }
		}

		T& operator[] (idx index) //Returns a reference so value can be modified
		{
			if(index >= _length) { throw exception("Index out of bounds in list"); }
			else { return *(_data + index); }
		}

		void add(T value);
		void insert(idx index, T value);

		void expand(idx length);
		void bubble(idx index, idx length);

		void reset(idx index);
		void remove(idx index);
		void remove(idx index, idx length);

		void set(idx index, T value)
		{
			if(index >= _length) { throw exception("Index out of bounds in list"); }
			else { *(_data + index) = value; }
		}

		int length() const { return _length; }
	};

	template<class T>
	void list<T>::add(T value) {
		//If the length plus one is less than the length, it must have rolled over to 0 and thus problems will happen. Prevent problems by throwing an exception.
		if(_length + 1 < _length) { throw mod3::exception("Attempting to extend list past maximum list length"); }
		else {
			T* tmp = _data;

			_data = memory::getNullifiedSet<T>(_length + 1);

			for(idx i = 0; i < _length; i++) //length still has old value
			{
				*(_data + i) = *(tmp + i);
			}

			delete[] tmp;

			*(_data + _length) = value; //Set new value at largest index of new array

			_length++;
		}
	}

	template<class T>
	void list<T>::insert(idx index, T value) {
		if(index >= _length) { throw exception("Index out of bounds in list"); }
		else if(_length + 1 < _length) { throw mod3::exception("Attempting to extend list past maximum list length"); }
		else
		{
			T* tmp = _data;

			_data = memory::getNullifiedSet<T>(_length + 1);

			for(idx i = 0; i < index; i++) //If index = 0 inserted element should be first
			{
				*(_data + i) = *(tmp + i);
			}
			*(_data + index) = value; //Insert the new value at the index
			for(idx i = index + 1; i < _length + 1; i++)
			{
				*(_data + i) = *(tmp + i - 1);
			}

			delete[] tmp;

			_length++;
		}
	}

	template<class T>
	void list<T>::expand(idx length)
	{
		//If the length plus the new length is less than the old length, it must rollover and thus expanding list would cause problems.
		if(_length + length < _length) { throw mod3::exception("Attempting to extend list past maximum list length"); }
		else {
			T* tmp = _data;

			_data = memory::getNullifiedSet<T>(_length + length);

			for(idx i = 0; i < _length; i++)
			{
				*(_data + i) = *(tmp + i);
			}

			delete[] tmp;

			_length += length;
		}
	}

	template<class T>
	void list<T>::bubble(idx index, idx length)
	{
		if(index >= _length) { throw exception("Index out of bounds in list"); }
		else if(length < 1) { throw exception("Invalid length parameter"); }
		else if(_length + length < _length) { throw mod3::exception("Attempting to extend list past maximum list length"); }
		else
		{
			T* tmp = _data;

			_data = memory::getNullifiedSet<T>(_length + length);

			for(idx i = 0; i < index; i++)
			{
				*(_data + i) = *(tmp + i);
			}
			for(idx i = index + length; i < _length + length; i++)
			{
				*(_data + i) = *(tmp + i - length);
			}

			delete[] tmp;

			_length += length;
		}
	}

	template<class T>
	void list<T>::reset(idx index) 
	{
		if(index >= _length) { throw exception("Index out of bounds in list"); }
		else
		{
			*(_data + index) = *memory::getNullified<T>();
		}
	}

	template<class T>
	void list<T>::remove(idx index)
	{
		if(index >= _length) { throw exception("Index out of bounds in list"); }
		else
		{
			T* tmp = _data;

			_data = memory::getNullifiedSet(_length - 1);

			for(idx i = 0; i < index; i++)
			{
				*(_data + i) = *(tmp + i);
			}
			for(idx i = index + 1; i < _length; i++)
			{
				*(_data + i - 1) = *(tmp + i);
			}

			delete[] tmp;

			_length--;
		}
	}

	template<class T>
	void list<T>::remove(idx index, idx length)
	{
		if(index >= _length) { throw exception("Index out of bounds in list"); }
		else if(length < 1 || length > _length) { throw exception("Invalid length parameter"); }
		else
		{
			T* tmp = _data;

			_data = memory::getNullifiedSet(_length - length);

			for(idx i = 0; i < index; i++)
			{
				*(_data + i) = *(tmp + i);
			}
			for(idx i = index + length; i < _length; i++)
			{
				*(_data + i - length) = *(tmp + i);
			}

			delete[] tmp;

			_length -= length;
		}
	}

	template<>
	class list<void>
	{
	private:
		void* _data;
		idx _length;
	public:
		list()
		{
			_data = nullptr;
			_length = 0;
		}

		list(idx length)
		{
			_data = new void*[length];
			_length = length;
		}

		template<class T>
		T get(idx index) const
		{
			if(index >= _length) { throw exception("Index out of bounds in list"); }
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
		T& elem(idx index) {
			if(index >= _length) { throw exception("Index out of bounds in list"); }
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
		void set(idx index, T value);
	};

	template<class T>
	list<T>::list(idx length)
	{
		_data = memory::getNullifiedSet(length);

		_length = length;
	}

	template<class T>
	list<T>::list(idx length, T value)
	{
		_data = memory::getNullifiedSet<T>(length);

		for(int i = 0; i < length; i++) { *(_data + i) = value; } //Populate list with value

		_length = length;
	}

	template<class T>
	void list<void>::set(idx index, T value)
	{
		if(index >= _length) { throw exception("Index out of bounds in list"); }
		else
		{
			T* tmp = static_cast<T*>(_data);
			*(tmp + index) = value;
		}
	}
}

#endif

//end of file