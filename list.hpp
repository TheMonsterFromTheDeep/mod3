#ifndef __INCL_LIST
#define __INCL_LIST

#include <new> //Used for bad_alloc errors
#include "memory.hpp" //For getNullified() and c_size
#include "exception.hpp"

namespace mod3 {
	template <class T>
	class list {
	private:
		T* _elems;
		numc _length;
	public:	
		list() {
			_elems = nullptr;
			_length = 0;
		}

		list(numc length);
		list(numc length, T value);

		T get(numc index) const {
			if(index >= _length) { throw exception("Index out of bounds in list"); }
			else { return *(_elems + index); }
		}

		T& operator[] (numc index) { //Returns a reference so value can be modified 
			if(index >= _length) { throw exception("Index out of bounds in list"); }
			else { return *(_elems + index); }
		}

		void add(T value);
		void insert(numc index, T value);

		void expand(numc length);
		void bubble(numc index, numc length);

		void reset(numc index);
		void remove(numc index);
		void remove(numc index, numc length);

		void set(numc index, T value) {
			if(index >= _length) { throw exception("Index out of bounds in list"); }
			else { *(_elems + index) = value; }
		}

		int length() const { return _length; }
	};

	template<class T>
	void list<T>::add(T value) {
		//If the length plus one is less than the length, it must have rolled over to 0 and thus problems will happen. Prevent problems by throwing an exception.
		if(_length + 1 < _length) { throw mod3::exception("Attempting to extend list past maximum list length"); }
		else {
			T* tmp = _elems;

			_elems = memory::getNullifiedSet<T>(_length + 1);

			for(numc i = 0; i < _length; i++) { //length still has old value
				*(_elems + i) = *(tmp + i);
			}

			delete[] tmp;

			*(_elems + _length) = value; //Set new value at largest index of new array

			_length++;
		}
	}

	template<class T>
	void list<T>::insert(numc index, T value) {
		if(index >= _length) { throw exception("Index out of bounds in list"); }
		else if(_length + 1 < _length) { throw mod3::exception("Attempting to extend list past maximum list length"); }
		else {
			T* tmp = _elems;

			_elems = memory::getNullifiedSet<T>(_length + 1);

			for(numc i = 0; i < index; i++) { //If index = 0 inserted element should be first
				*(_elems + i) = *(tmp + i);
			}
			*(_elems + index) = value; //Insert the new value at the index
			for(numc i = index + 1; i < _length + 1; i++) {
				*(_elems + i) = *(tmp + i - 1);
			}

			delete[] tmp;

			_length++;
		}
	}

	template<class T>
	void list<T>::expand(numc length) {
		//If the length plus the new length is less than the old length, it must rollover and thus expanding list would cause problems.
		if(_length + length < _length) { throw mod3::exception("Attempting to extend list past maximum list length"); }
		else {
			T* tmp = _elems;

			_elems = memory::getNullifiedSet<T>(_length + length);

			for(numc i = 0; i < _length; i++)
			{
				*(_elems + i) = *(tmp + i);
			}

			delete[] tmp;

			_length += length;
		}
	}

	template<class T>
	void list<T>::bubble(numc index, numc length) {
		if(index >= _length) { throw exception("Index out of bounds in list"); }
		else if(length < 1) { throw exception("Invalid length parameter"); }
		else if(_length + length < _length) { throw mod3::exception("Attempting to extend list past maximum list length"); }
		else {
			T* tmp = _elems;

			_elems = memory::getNullifiedSet<T>(_length + length);

			for(numc i = 0; i < index; i++) {
				*(_elems + i) = *(tmp + i);
			}
			for(numc i = index + length; i < _length + length; i++) {
				*(_elems + i) = *(tmp + i - length);
			}

			delete[] tmp;

			_length += length;
		}
	}

	template<class T>
	void list<T>::reset(numc index) {
		if(index >= _length) { throw exception("Index out of bounds in list"); }
		else {
			*(_elems + index) = *memory::getNullified<T>();
		}
	}

	template<class T>
	void list<T>::remove(numc index) {
		if(index >= _length) { throw exception("Index out of bounds in list"); }
		else {
			T* tmp = _elems;

			_elems = memory::getNullifiedSet(_length - 1);

			for(numc i = 0; i < index; i++) {
				*(_elems + i) = *(tmp + i);
			}
			for(numc i = index + 1; i < _length; i++) {
				*(_elems + i - 1) = *(tmp + i);
			}

			delete[] tmp;

			_length--;
		}
	}

	template<class T>
	void list<T>::remove(numc index, numc length) {
		if(index >= _length) { throw exception("Index out of bounds in list"); }
		else if(length < 1 || length > _length) { throw exception("Invalid length parameter"); }
		else {
			T* tmp = _elems;

			_elems = memory::getNullifiedSet(_length - length);

			for(numc i = 0; i < index; i++) {
				*(_elems + i) = *(tmp + i);
			}
			for(numc i = index + length; i < _length; i++) {
				*(_elems + i - length) = *(tmp + i);
			}

			delete[] tmp;

			_length -= length;
		}
	}

	template<class T>
	list<T>::list(numc length) {
		_elems = memory::getNullifiedSet(length);

		_length = length;
	}

	template<class T>
	list<T>::list(numc length, T value) {
		_elems = memory::getNullifiedSet<T>(length);

		for(numc i = 0; i < length; i++) { *(_elems + i) = value; } //Populate list with value

		_length = length;
	}
}

#endif