#ifndef __INCL_LIST
#define __INCL_LIST

#include "base.hpp"

namespace mod3 {
	template <class T>
	class List {
	private:
		T* elems;
		uint _length;

		//Used by Builder class so that unnecessary copying doesn't happen
		List(T* e, uint s) : elems(e), _length(s) { }

		template<class B>
		class Builder {
		private:
			B* elems;
			uint length;
			uint write;
		public:
			Builder(uint size) {
				unsigned char* init = new unsigned char[size * sizeof(B)];
				for(uint i = 0; i < size * sizeof(B); init[i++] = 0);
				elems = reinterpret_cast<B*>(init);

				length = size;
				write = 0;
			}

			Builder<B>& operator()(B value) {
				if(length + 1 < length) { throw Exception("Adding element to built List failed - new size is greater than maximum List size"); }
				else {
					if(write < length) {
						elems[write] = value;
					}
					else {
						B* tmp = elems;

						elems = reinterpret_cast<T*>(new unsigned char[(length + 1) * sizeof(B)]);

						for(uint i = 0; i < length; i++) { //length still has old value
							elems[i] = tmp[i];
						}

						delete[] tmp;

						elems[length] = value; //Set new value at largest index of new array

						length++;
					}
					write++; //Write always needs to be incremented such that after the initial free space is exhausted, no other space is ever confused as free
				}
				return *this;
			}

			operator List<B>() {
				return List<B>(elems,length);
			}
		};
	public:	
		List() : elems(nullptr), _length(0) { }

		List(uint length);
		List(uint length, T value);
		template<uint size>
		List(T (&items)[size]);

		static Builder<T> create(T first) { return Builder<T>(1)(first); }
		template<uint size>
		static Builder<T> create(T first) { return Builder<T>(size)(first); }

		//Returns a const reference because this is not supposed to be modifiable
		const T& get(uint index) const {
			if(index >= _length) { throw Exception("List get failed - index out of bounds"); }
			else { return elems[index]; }
		}
		  
		//If a List is const, values should not be modifiable
		const T& operator[] (uint index) const {
			if(index >= _length) { throw Exception("List element access failed - index out of bounds"); }
			else { return elems[index]; }
		}

		T& operator[] (uint index) { //Returns a reference so value can be modified 
			if(index >= _length) { throw Exception("List element access failed - index out of bounds"); }
			else { return elems[index]; }
		}

		void add(T value);
		void insert(uint index, T value);

		void expand(uint length);
		void bubble(uint index, uint length);

		void reset(uint index);
		void reset(uint index, uint length);
		void remove(uint index);
		void remove(uint index, uint length);

		void set(uint index, const T& value) {
			if(index >= _length) { throw Exception("List set failed - index out of bounds"); }
			else { elems[index] = value; }
		}

		uint length() const { return _length; }
	};
	
	template<class T>
	List<T>::List(uint length) : _length(length) {
		unsigned char* init = new unsigned char[length * sizeof(T)];
		for(uint i = 0; i < length * sizeof(T); init[i++] = 0);
		elems = reinterpret_cast<T*>(init);
	}

	template<class T>
	List<T>::List(uint length, T value) : _length(length) {
		elems = reinterpret_cast<T*>(new unsigned char[length * sizeof(T)]);
		for(uint i = 0; i < length; i++) { elems[i] = value; } //Populate list with value
	}

	template<class T>
	template<uint size>
	List<T>::List(T (&items)[size]) {
		elems = new T[size];
		for(uint i = 0; i < size; i++) {
			elems[i] = items[i];
		}
		_length = size;
	}

	template<class T>
	void List<T>::add(T value) {
		//If the length plus one is less than the length, it must have rolled over to 0 and thus problems will happen. Prevent problems by throwing an exception.
		if(_length + 1 < _length) { throw Exception("List add failed - new size is greater than maximum List size"); }
		else {
			T* tmp = elems;

			elems = reinterpret_cast<T*>(new unsigned char[(_length + 1) * sizeof(T)]);

			for(uint i = 0; i < _length; i++) { //length still has old value
				elems[i] = tmp[i];
			}

			delete[] tmp;

			elems[_length] = value; //Set new value at largest index of new array

			_length++;
		}
	}

	template<class T>
	void List<T>::insert(uint index, T value) {
		if(index >= _length) { throw Exception("List insert failed - index out of bounds"); }
		else if(_length + 1 < _length) { throw Exception("List insert failed - new size is greater than maximum List size"); }
		else {
			T* tmp = elems;

			elems = reinterpret_cast<T*>(new unsigned char[(_length + 1) * sizeof(T)]);

			for(uint i = 0; i < index; i++) { //If index = 0 inserted element should be first
				elems[i] = tmp[i];
			}
			*(elems + index) = value; //Insert the new value at the index
			for(uint i = index + 1; i < _length + 1; i++) {
				elems[i] = tmp[i - 1];
			}

			delete[] tmp;

			_length++;
		}
	}

	template<class T>
	void List<T>::expand(uint length) {
		if(_length + length < _length) { throw Exception("List expand failed - new size is greater than maximum List size"); } //If the length plus the new length is less than the old length, it must rollover and thus expanding list would cause problems.
		else if(length == 0) { } //TODO: Do this prettier
		else {
			T* tmp = elems;

			unsigned char* init = new unsigned char[(_length + length) * sizeof(T)];
			for(uint i = _length * sizeof(T); i < (_length + length) * sizeof(T); init[i++] = 0);
			elems = reinterpret_cast<T*>(init);

			for(uint i = 0; i < _length; i++) {
				elems[i] = tmp[i];
			}

			delete[] tmp;

			_length += length;
		}
	}

	template<class T>
	void List<T>::bubble(uint index, uint length) {
		if(index >= _length) { throw Exception("List bubble failed - out of bounds"); }
		else if(_length + length < _length) { throw Exception("List bubble failed - new size is greater than maximum List size"); }
		else if(length == 0) { }
		else {
			T* tmp = elems;

			unsigned char* init = new unsigned char[(_length + length) * sizeof(T)];
			for(uint i = index * sizeof(T); i < (index + length) * sizeof(T); init[i++] = 0);
			elems = reinterpret_cast<T*>(init);

			for(uint i = 0; i < index; i++) {
				elems[i] = tmp[i];
			}
			for(uint i = index + length; i < _length + length; i++) {
				elems[i] = tmp[i - length];
			}

			delete[] tmp;

			_length += length;
		}
	}

	template<class T>
	void List<T>::reset(uint index) {
		if(index >= _length) { throw Exception("List reset failed - index out of bounds"); }
		else {
			unsigned char* value = new unsigned char[sizeof(T)];
			for(uint i = 0; i < sizeof(T); i++) { value[i] = 0; }
			elems[index] = *reinterpret_cast<T*>(value);
		}
	}

	template<class T>
	void List<T>::reset(uint index, uint length) {
		if(index + length >= _length) { throw Exception("List reset failed - out of bounds"); }
		else if(length == 0) { }
		else {
			unsigned char* value = new unsigned char[sizeof(T)];
			for(uint i = 0; i < sizeof(T); i++) { value[i] = 0; }
			for(uint i = 0; i < length; i++) {
				elems[i + index] = *reinterpret_cast<T*>(value);
			}		
		}
	}

	template<class T>
	void List<T>::remove(uint index) {
		if(index >= _length) { throw Exception("List remove failed - index out of bounds"); }
		else {
			T* tmp = elems;

			elems = reinterpret_cast<T*>(new unsigned char[(_length - 1) * sizeof(T)]);

			for(uint i = 0; i < index; i++) {
				elems[i] = tmp[i];
			}
			for(uint i = index + 1; i < _length; i++) {
				elems[i - 1] = tmp[i];
			}

			delete[] tmp;

			_length--;
		}
	}

	template<class T>
	void List<T>::remove(uint index, uint length) {
		if(index + length >= _length) { throw Exception("List remove failed - out of bounds"); }
		else if(length == 0) { }
		else {
			T* tmp = elems;

			elems = reinterpret_cast<T*>(new unsigned char[(_length - length) * sizeof(T)]);

			for(uint i = 0; i < index; i++) {
				elems[i] = tmp[i];
			}
			for(uint i = index + length; i < _length; i++) {
				elems[i - length] = tmp[i];
			}

			delete[] tmp;

			_length -= length;
		}
	}
}

#endif