#pragma once

#ifndef __INCL_STRING
#define __INCL_STRING

#include "exception.h"

namespace mod3
{
	class string
	{
	private:
		char* _data; //Stores the value of the string - not const because it needs to be able to be manipulated
		int _length; //Stores the length of the string	
	public:
		string() //Default constructor
		{
			_data = '\0'; //The string simply consists of a null terminator
			_length = 0; //The useable length of the string is zero
		}

		string(char* value) //Copy the data over so that the char* isn't overwritten by string manipulations
		{
			_length = 0;
			while(*(value + _length) != '\0')
			{
				_length++;
			}
			_data = new char[_length + 1];
			for(int i = 0; i < _length; i++)
			{
				*(_data + i) = *(value + i);
			}
			*(_data + _length) = '\0';
		}

		string(const char* value) //Initializing from a const char* requires copying the data over
		{
			_length = 0;
			while(*(value + _length) != '\0') //Null terminator is end of string
			{
				_length++;
			}
			_data = new char[_length + 1];
			for(int i = 0; i < _length; i++)
			{
				*(_data + i) = *(value + i);
			}
			*(_data + _length) = '\0'; //Add null terminator
		}

		string(char c) //Construct string from single char
		{
			_length = 1;
			_data = new char[2];
			*_data = c;
			*(_data + 1) = '\0';
		}

		string(string& s)
		{
			_data = s.get_data(); //Copy data over
			_length = s._length;
		}

		void concat(string s) //Concatenate with another string
		{
			char* tmp = _data;
			_data = new char[_length + s._length + 1];
			for(int i = 0; i < _length; i++)
			{
				*(_data + i) = *(tmp + i);
			}
			for(int i = 0; i < s._length; i++)
			{
				*(_data + _length + i) = *(s._data + i);
			}
			*(_data + _length + s._length) = '\0';

			delete[] tmp;

			_length += s._length;
		}
		void operator+=(string s) { concat(s); } //Operators for convenience
		string operator+(string s) { string r(*this); r.concat(s); return r; }

		void concat(const char* c) //Concatenate with a const char* 
		{
			int c_length = 0;
			while(*(c + c_length) != '\0') { c_length++; }

			char* tmp = _data;
			_data = new char[_length + c_length + 1];
			for(int i = 0; i < _length; i++)
			{
				*(_data + i) = *(tmp + i);
			}
			for(int i = 0; i < c_length; i++)
			{
				*(_data + _length + i) = *(c + i);
			}
			*(_data + _length + c_length) = '\0';

			delete[] tmp;

			_length += c_length;
		}
		void operator+=(const char* c) { concat(c); } //Operators for convenience
		string operator+(const char* c) { string r(*this); r.concat(c); return r; }

		void concat(char c)
		{
			char* tmp = _data;
			_data = new char[_length + 2]; //Enough room for the new char and the null terminator
			for(int i = 0; i < _length; i++)
			{
				*(_data + i) = *(tmp + i);
			}
			*(_data + _length) = c;
			*(_data + _length + 1) = '\0';

			delete[] tmp;

			_length += 1;
		}
		void operator+=(char c) { concat(c); }
		string operator+(char c) { string r(*this); r.concat(c); return r; }

		bool equals(string s)
		{
			if(_length == s._length)
			{
				for(int i = 0; i < _length; i++)
				{
					if(*(_data + i) != *(s._data + i)) { return false; }
				}
				return true;
			}
			return false;
		}
		bool operator==(string s) { return equals(s); }

		bool equals(const char* c)
		{
			int c_length = 0;
			while(*(c + c_length) != '\0') { c_length++; }
			if(_length == c_length)
			{
				for(int i = 0; i < _length; i++)
				{
					if(*(_data + i) != *(c + i)) { return false; }
				}
				return true;
			}
			return false;
		}
		bool operator==(const char* c) { return equals(c); }

		int length() { return _length; } //Returns the length - the length is a private variable so it isn't screwed with

		char char_at(int index)
		{
			if(index < 0 || index >= _length) { throw new exception("Index out of bounds in string"); }
			else { return *(_data + index); }
		}

		char& operator[] (int index)
		{
			if(index < 0 || index >= _length) { throw new exception("Index out of bounds in string"); }
			else { return *(_data + index); }
		}

		char* get_data() //Return a copy of the pointer with the data
		{
			char* tmp = new char[_length + 1];
			for(int i = 0; i <= _length; i++) //Copy data over including null terminator
			{
				*(tmp + i) = *(_data + i);
			}
			return tmp;
		}
	};
};

#endif