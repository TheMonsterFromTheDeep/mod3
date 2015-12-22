#ifndef __INCL_STRING
#define __INCL_STRING

#include "base.hpp"
#include "exception.hpp"

namespace mod3 {
	/* class String
	Represents a string of characters.
	*/
	typedef class String {
	private:
		char* _text; //Stores the value of the string - not const because it needs to be able to be manipulated
		uint _length; //Stores the length of the string	
	public:
		String() : _text('\0'), _length(0) { }

		String(char* value) : _text(value) { //By default, the pointer isn't copied
			_length = 0;
			//Calculate the length of the passed pointer
			while(value[++_length] != '\0'); 
		} 
		String(char* value, bool copy); //Use this method to copy data from pointer
		String(const char* value); //Initializing from a const char* requires copying the data over
		String(const char* value, bool copy); //Define this specifically for const char*s so that they have to be copied

		String(char c) : _length(1) { //Construct string from single char
			_text = new char[2];
			_text[0] = c;
			_text[1] = '\0';
		}

		String(const String& s) {
			_text = s.copy(); //Copy data over
			_length = s._length;
		}

		String(String&& source) : _text(source._text), _length(source._length) {
			source._text = nullptr;
		}

		~String();

		void concatenate(char c);
		void concatenate(const char* c); //Concatenate with a const char* 	
		void concatenate(const String& s); //Concatenate with another string

		void insert(uint index, char c);
		void insert(uint index, const char* c);
		void insert(uint index, const String& s);

		void replace(char find, char replace) {
			for(uint i = 0; i < _length; i++) {
				if(_text[i] == find) { _text[i] = replace; }
			}
		}

		void replace(uint index, char c) {
			if(index >= _length) { throw Exception("Index out of bounds in string"); }
			else { _text[index] = c; }
		}

		void operator+=(char c) { concatenate(c); }
		void operator+=(const char* c) { concatenate(c); }
		void operator+=(const String& s) { concatenate(s); }
	
		bool equals(const char* c) const;
		bool equals(const String& s) const;

		bool operator==(const char* c) const { return equals(c); }
		bool operator==(const String& s) const { return equals(s); }

		const char& operator[] (uint index) const {
			if(index >= _length) { throw Exception("Index out of bounds in string"); }
			else { return _text[index]; }
		}

		char& operator[] (uint index) {
			if(index >= _length) { throw Exception("Index out of bounds in string"); }
			else { return _text[index]; }
		}

		char* copy() const; //Return a copy of the pointer with the data
		char* text() { return _text; } //Unmodifiable lvalue
		const char* text() const { return _text; } //Return the text pointer for whatever reason

		char at(uint index) const {
			if(index >= _length) { throw Exception("Index out of bounds in string"); }
			else { return _text[index]; }
		}
		
		int length() const { return _length; } //Returns the length - the length is a private variable so it isn't screwed with		

		String operator+(const String& s) const;	
		String& operator+(const char* c) const;
		String operator+(char c) const;

		String& operator=(char c) {
			_text = new char[2];
			*_text = c;
			_text[1] = '\0';

			_length = 1;

			return *this;
		}
		String& operator=(const char* c);
		String& operator=(const String& s);

		String& operator=(String&& s);
	} String;

	String::String(char* value, bool copy) {
		_length = 0;
		while(value[++_length] != '\0');
		if(copy) {		
			_text = new char[_length + 1];
			for(uint i = 0; i < _length; i++) {
				_text[i] = value[i];
			}
			_text[_length] = '\0';
		}
		else {
			_text = value;
			value = nullptr;
		}
	}

	String::String(const char* value) {
		_length = 0;
		while(value[++_length] != '\0');//Null terminator is end of string
		_text = new char[_length + 1];
		for(uint i = 0; i < _length; i++) {
			_text[i] = value[i];
		}
		_text[_length] = '\0'; //Add null terminator
	}

	String::String(const char* value, bool copy) {
		//Ignore copy value, because if the passed char* is const, it essentially needs to be copied.
		_length = 0;
		while(value[++_length] != '\0');//Null terminator is end of string
		_text = new char[_length + 1];
		for(uint i = 0; i < _length; i++) {
			_text[i] = value[i];
		}
		_text[_length] = '\0'; //Add null terminator
	}

	String::~String() {
		//Deallocate memory storing String data
		delete[] _text;
	}

	void String::concatenate(char c) {
		if(_length + 2 < _length + 1) { throw Exception("Attempting to extend string past maximum string length"); }
		else {
			char* tmp = _text;
			_text = new char[_length + 2]; //Enough room for the new char and the null terminator
			for(uint i = 0; i < _length; i++) {
				_text[i] = tmp[i];
			}
			_text[_length] = c;
			_text[_length + 1] = '\0';

			delete[] tmp;

			++_length;
		}
	}

	void String::concatenate(const char* c) {
		uint addLength = 0; //The length of the String being concatenated to the end of this one
		while(c[++addLength] != '\0');
		if(_length + addLength + 1 < _length + 1) { throw mod3::Exception("Attempting to extend string past maximum string length"); }
		else {
			char* tmp = _text;
			_text = new char[_length + addLength + 1];
			for(uint i = 0; i < _length; i++) {
				_text[i] = tmp[i];
			}
			for(uint i = 0; i < addLength; i++) {
				_text[_length + i] = c[i];
			}
			_text[_length + addLength] = '\0';

			delete[] tmp;

			_length += addLength;
		}
	}

	void String::concatenate(const String& s) {
		if(_length + s._length + 1 > _length + 1) { throw mod3::Exception("Attempting to extend string past maximum string length"); }
		else {
			char* tmp = _text;
			_text = new char[_length + s._length + 1];
			for(uint i = 0; i < _length; i++) {
				_text[i] = tmp[i];
			}
			for(uint i = 0; i < s._length; i++) {
				_text[_length + i] = s._text[i];
			}
			_text[_length + s._length] = '\0';

			delete[] tmp;

			_length += s._length;
		}
	}

	void String::insert(uint index, char c) {
		if(index > _length) { throw Exception("Index out of bounds in string"); }
		else if(_length + 2 < _length + 1) { throw mod3::Exception("Attempting to extend string past maximum string length"); }
		else {
			char* tmp = _text;
			_text = new char[_length + 2];
			for(uint i = 0; i < index; i++) {
				_text[i] = tmp[i];
			}
			_text[index] = c;
			for(uint i = index; i < _length; i++) {
				_text[i + 1] = tmp[i];
			}
			*(_text + _length + 1) = '\0';
			_length++;
			delete[] tmp;
		}
	}

	void String::insert(uint index, const char* c) {
		if(index > _length) { throw Exception("Index out of bounds in string"); }
		else {
			uint addLength = 0;
			while(c[++addLength] != 0);

			if(_length + addLength + 1 < _length + 1) { throw mod3::Exception("Attempting to extend string past maximum string length"); }
			else {
				char* tmp = _text;
				_text = new char[_length + addLength + 1];
				for(uint i = 0; i < index; i++) {
					_text[i] = tmp[i];
				}
				for(uint i = 0; i < addLength; i++) {
					_text[index + i] = c[i];
				}
				for(uint i = index; i < _length; i++) {
					_text[i + addLength] = tmp[i];
				}
				_text[_length + addLength] = '\0';
				_length += addLength;
				delete[] tmp;
			}
		}
	}

	void String::insert(uint index, const String& s) {
		if(index > _length) { throw Exception("Index out of bounds in string"); }
		else if(_length + s._length + 1 < _length + 1) { throw mod3::Exception("Attempting to extend string past maximum string length"); }
		else {
			char* tmp = _text;
			_text = new char[_length + s._length + 1];
			for(uint i = 0; i < index; i++) {
				_text[i] = tmp[i];
			}
			for(uint i = 0; i < s._length; i++) {
				_text[index + i] = s._text[i];
			}
			for(uint i = index; i < _length; i++) {
				_text[i + s._length] = tmp[i];
			}
			_text[_length + s._length] = '\0';
			_length += s._length;
			delete[] tmp;
		}
	}

	bool String::equals(const String& s) const {
		if(_length == s._length) {
			for(uint i = 0; i < _length; i++) {
				if(_text[i] != s._text[i]) { return false; }
			}
			return true;
		}
		return false;
	}

	bool String::equals(const char* c) const {
		int checkLength = 0;
		while(c[++checkLength] != '\0');
		if(_length == checkLength) {
			for(uint i = 0; i < _length; i++) {
				if(_text[i] != c[i]) { return false; }
			}
			return true;
		}
		return false;
	}

	char* String::copy() const {
		char* tmp;
		tmp = new char[_length + 1];
		
		for(uint i = 0; i <= _length; i++) { //Copy data over including null terminator
			tmp[i] = _text[i];
		}

		return tmp;
	}

	String& String::operator+(const char* c) const {	
		uint addLength = 0;
		while(c[++addLength] != '\0');

		if(addLength + _length + 1 < _length + 1) { throw mod3::Exception("Attempting to extend string past maximum string length"); }
		else {
			char* tmp = new char[_length + addLength];

			for(uint i = 0; i < _length; i++) {
				tmp[i] = _text[i];
			}

			for(uint i = 0; i < addLength; i++) {
				tmp[_length + i] = c[i];
			}
			tmp[_length + addLength] = '\0';

			String ret(tmp);
			ret._length = _length + addLength;

			return ret;
		}
	}

	String String::operator+(const String& s) const {
		if(_length + s._length + 1 < _length + 1) { throw mod3::Exception("Attempting to extend string past maximum string length"); }
		else {
			String tmp(*this);

			//TODO: FIX THIS PROBLEM!!!!!
			tmp._length += s._length;
			for(uint i = 0; i < s._length; i++) {
				tmp._text[_length + i] = s._text[i];
			}
			tmp._text[_length + s._length] = '\0';

			return tmp;
		}
	}

	String String::operator+(char c) const {
		if(_length + 2 < _length + 1) { throw mod3::Exception("Attempting to extend string past maximum string length"); }
		else {
			//Copy this String
			String tmp(*this);

			tmp._length++;
			tmp._text[_length] = c; //This string's length hasn't changed
			tmp._text[_length + 1] = '\0';

			return tmp;
		}
	}

	String& String::operator=(const char* c) {
		_length = 0;
		while(c[++_length] != '\0'); //Null terminator is end of string

		_text = new char[_length + 1];
		for(uint i = 0; i < _length; i++) {
			_text[i] = c[i];
		}
		_text[_length] = '\0'; //Add null terminator

		return *this;
	}

	String& String::operator=(const String& s) {
		_text = s.copy();
		_length = s._length;

		return *this;
	}

	String& String::operator=(String&& s) {
		_text = s._text;
		_length = s._length;

		return *this;
	}
};

#endif