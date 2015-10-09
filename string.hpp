#ifndef __INCL_STRING
#define __INCL_STRING

#include "memory.hpp"
#include "exception.hpp"

namespace mod3
{
	typedef class string
	{
	private:
		char* _text; //Stores the value of the string - not const because it needs to be able to be manipulated
		idx _length; //Stores the length of the string	

		string(char* text, idx length) { _text = text; _length = length; }
	public:

		string() //Default constructor
		{
			_text = '\0'; //The string simply consists of a null terminator
			_length = 0; //The useable length of the string is zero
		}

		string(char* value); //By default, the pointer isn't copied
		string(char* value, bool copy); //Use this method to copy data from pointer
		string(const char* value); //Initializing from a const char* requires copying the data over

		string(char c) //Construct string from single char
		{
			_length = 1;
			_text = new char[2];
			*_text = c;
			*(_text + 1) = '\0';
		}

		string(const string& s)
		{
			_text = s.copy()._text; //Copy data over
			_length = s._length;
		}	

		void concatenate(char c);
		void concatenate(const char* c); //Concatenate with a const char* 	
		void concatenate(const string& s); //Concatenate with another string

		void insert(char c, idx index);
		void insert(const char* c, idx index);
		void insert(const string& s, idx index);

		void replace(char find, char replace)
		{
			for(int i = 0; i < _length; i++)
			{
				if(*(_text + i) == find) { *(_text + i) = replace; }
			}
		}

		void replace(idx index, char c)
		{
			if(index > _length) { throw exception("Index out of bounds in string"); }
			else { *(_text + index) = c; }
		}

		void operator+=(char c) { concatenate(c); }
		void operator+=(const char* c) { concatenate(c); }
		void operator+=(const string& s) { concatenate(s); }
	
		bool equals(const char* c) const;
		bool equals(const string& s) const;

		bool operator==(const char* c) const { return equals(c); }
		bool operator==(const string& s) const { return equals(s); }

		char& operator[] (idx index) const
		{
			if(index >= _length) { throw exception("Index out of bounds in string"); }
			else { return *(_text + index); }
		}

		string copy() const; //Return a copy of the pointer with the data
		char* text() const { return _text; } //Return the text pointer for whatever reason

		char at(idx index) const
		{
			if(index >= _length) { throw exception("Index out of bounds in string"); }
			else { return *(_text + index); }
		}
		
		int length() const { return _length; } //Returns the length - the length is a private variable so it isn't screwed with		

		string operator+(const string& s) const;	
		string operator+(const char* c) const;
		string operator+(char c) const;
	} string;

	string::string(char* value)
	{
		_length = 0;
		while(*(value + _length) != '\0')
		{
			_length++;
		}
		_text = value;
	}

	string::string(char* value, bool copy)
	{
		_length = 0;
		while(*(value + _length) != '\0')
		{
			_length++;
		}
		if(copy) {
			
			_text = new char[_length + 1];
			for(int i = 0; i < _length; i++)
			{
				*(_text + i) = *(value + i);
			}
			*(_text + _length) = '\0';
		}
		else {
			_text = value;
		}
	}

	string::string(const char* value)
	{
		_length = 0;
		while(*(value + _length) != '\0') //Null terminator is end of string
		{
			_length++;
		}
		_text = new char[_length + 1];
		for(int i = 0; i < _length; i++)
		{
			*(_text + i) = *(value + i);
		}
		*(_text + _length) = '\0'; //Add null terminator
	}

	void string::concatenate(char c)
	{
		if(_length + 2 < _length + 1) { throw mod3::exception("Attempting to extend string past maximum string length"); }
		else {
			char* tmp = _text;
			_text = new char[_length + 2]; //Enough room for the new char and the null terminator
			for(idx i = 0; i < _length; i++)
			{
				*(_text + i) = *(tmp + i);
			}
			*(_text + _length) = c;
			*(_text + _length + 1) = '\0';

			delete[] tmp;

			_length += 1;
		}
	}

	void string::concatenate(const char* c)
	{
		idx c_length = 0;
		while(*(c + c_length) != '\0') { c_length++; }
		if(_length + c_length + 1 > _length + 1) { throw mod3::exception("Attempting to extend string past maximum string length"); }
		else {
		char* tmp = _text;
			_text = new char[_length + c_length + 1];
			for(idx i = 0; i < _length; i++)
			{
				*(_text + i) = *(tmp + i);
			}
			for(idx i = 0; i < c_length; i++)
			{
				*(_text + _length + i) = *(c + i);
			}
			*(_text + _length + c_length) = '\0';

			delete[] tmp;

			_length += c_length;
		}
	}

	void string::concatenate(const string& s)
	{
		if(_length + s._length + 1 > _length + 1) { throw mod3::exception("Attempting to extend string past maximum string length"); }
		else {
			char* tmp = _text;
			_text = new char[_length + s._length + 1];
			for(int i = 0; i < _length; i++)
			{
				*(_text + i) = *(tmp + i);
			}
			for(int i = 0; i < s._length; i++)
			{
				*(_text + _length + i) = *(s._text + i);
			}
			*(_text + _length + s._length) = '\0';

			delete[] tmp;

			_length += s._length;
		}
	}

	void string::insert(char c, idx index)
	{
		if(index > _length) { throw exception("Index out of bounds in string"); }
		else if(_length + 2 < _length + 1) { throw mod3::exception("Attempting to extend string past maximum string length"); }
		else
		{
			char* tmp = _text;
			_text = new char[_length + 2];
			for(idx i = 0; i < index; i++)
			{
				*(_text + i) = *(tmp + i);
			}
			*(_text + index) = c;
			for(idx i = index; i < _length; i++)
			{
				*(_text + i + 1) = *(tmp + i);
			}
			*(_text + _length + 1) = '\0';
			_length++;
			delete[] tmp;
		}
	}

	void string::insert(const char* c, idx index)
	{
		if(index > _length) { throw exception("Index out of bounds in string"); }
		else
		{
			idx c_length = 0;
			while(*(c + c_length) != '\0') { c_length++; }

			if(_length + c_length + 1 > _length + 1) { throw mod3::exception("Attempting to extend string past maximum string length"); }
			else {
				char* tmp = _text;
				_text = new char[_length + c_length + 1];
				for(idx i = 0; i < index; i++)
				{
					*(_text + i) = *(tmp + i);
				}
				for(idx i = 0; i < c_length; i++)
				{
					*(_text + index + i) = *(c + i);
				}
				for(idx i = index; i < _length; i++)
				{
					*(_text + i + c_length) = *(tmp + i);
				}
				*(_text + _length + c_length) = '\0';
				_length += c_length;
				delete[] tmp;
			}
		}
	}

	void string::insert(const string& s, idx index)
	{
		if(index > _length) { throw exception("Index out of bounds in string"); }
		else if(_length + s._length + 1 < _length + 1) { throw mod3::exception("Attempting to extend string past maximum string length"); }
		else
		{
			char* tmp = _text;
			_text = new char[_length + s._length + 1];
			for(idx i = 0; i < index; i++)
			{
				*(_text + i) = *(tmp + i);
			}
			for(idx i = 0; i < s._length; i++)
			{
				*(_text + index + i) = *(s._text + i);
			}
			for(idx i = index; i < _length; i++)
			{
				*(_text + i + s._length) = *(tmp + i);
			}
			*(_text + _length + s._length) = '\0';
			_length += s._length;
			delete[] tmp;
		}
	}

	bool string::equals(const string& s) const
	{
		if(_length == s._length)
		{
			for(int i = 0; i < _length; i++)
			{
				if(*(_text + i) != *(s._text + i)) { return false; }
			}
			return true;
		}
		return false;
	}

	bool string::equals(const char* c) const
	{
		int c_length = 0;
		while(*(c + c_length) != '\0') { c_length++; }
		if(_length == c_length)
		{
			for(int i = 0; i < _length; i++)
			{
				if(*(_text + i) != *(c + i)) { return false; }
			}
			return true;
		}
		return false;
	}

	string string::copy() const
	{
		char* tmp;
		tmp = new char[_length + 1];
		
		for(idx i = 0; i <= _length; i++) //Copy data over including null terminator
		{
			*(tmp + i) = *(_text + i);
		}

		return string(tmp,_length);
	}

	string string::operator+(const char* c) const
	{	
		int c_length = 0;
		while(*(c + c_length) != '\0') { c_length++; }

		if(c_length + _length + 1 < _length + 1) { throw mod3::exception("Attempting to extend string past maximum string length"); }
		else {
			string tmp = copy();

			tmp._length += c_length;
			for(int i = 0; i < c_length; i++)
			{
				*(tmp._text + _length + i) = *(c + i);
			}
			*(tmp._text + _length + c_length) = '\0';

			return tmp;
		}
	}

	string string::operator+(const string& s) const
	{
		if(_length + s._length + 1 < _length + 1) { throw mod3::exception("Attempting to extend string past maximum string length"); }
		string tmp = copy();

		tmp._length += s._length;
		for(int i = 0; i < s._length; i++)
		{
			*(tmp._text + _length + i) = *(s._text + i);
		}
		*(tmp._text + _length + s._length) = '\0';

		return tmp;
	}

	string string::operator+(char c) const
	{
		if(_length + 2 < _length + 1) { throw mod3::exception("Attempting to extend string past maximum string length"); }
		else {
			string tmp = copy();

			tmp._length++;
			*(tmp._text + _length) = c; //This string's length hasn't changed
			*(tmp._text + _length + 1) = '\0';

			return tmp;
		}
	}

	char* substring(const string& base, int start, int end) //Returns char* so redundant conversion to string doesn't happen when char* wanted
	{
		if((start < 0 || start >= base.length()) || (end < 0 || end >= base.length())) { throw new exception("Index out of bounds in string"); }
		else 
		{
			char* tmp = new char[end - start + 1];
			char* text = base.text();
			for(int i = start; i < end; i++)
			{
				*(tmp + i - start) = *(text + i);
			}
			*(tmp + end - start) = '\0';
			return tmp;
		}
	}
};

#endif

//end of file