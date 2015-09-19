#pragma once

#ifndef __INCL_STRING
#define __INCL_STRING

#include "exception.h"

namespace mod3
{
	class string
	{
	private:
		char* _text; //Stores the value of the string - not const because it needs to be able to be manipulated
		int _length; //Stores the length of the string	
	public:

		string() //Default constructor
		{
			_text = '\0'; //The string simply consists of a null terminator
			_length = 0; //The useable length of the string is zero
		}

		string(char* value) //Copy the data over so that the char* isn't overwritten by string manipulations
		{
			_length = 0;
			while(*(value + _length) != '\0')
			{
				_length++;
			}
			_text = new char[_length + 1];
			for(int i = 0; i < _length; i++)
			{
				*(_text + i) = *(value + i);
			}
			*(_text + _length) = '\0';
		}

		string(const char* value) //Initializing from a const char* requires copying the data over
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

		string(char c) //Construct string from single char
		{
			_length = 1;
			_text = new char[2];
			*_text = c;
			*(_text + 1) = '\0';
		}

		string(string& s)
		{
			_text = s.copy(); //Copy data over
			_length = s._length;
		}	

		void concatenate(char c)
		{
			char* tmp = _text;
			_text = new char[_length + 2]; //Enough room for the new char and the null terminator
			for(int i = 0; i < _length; i++)
			{
				*(_text + i) = *(tmp + i);
			}
			*(_text + _length) = c;
			*(_text + _length + 1) = '\0';

			delete[] tmp;

			_length += 1;
		}

		void concatenate(const char* c) //Concatenate with a const char* 
		{
			int c_length = 0;
			while(*(c + c_length) != '\0') { c_length++; }

			char* tmp = _text;
			_text = new char[_length + c_length + 1];
			for(int i = 0; i < _length; i++)
			{
				*(_text + i) = *(tmp + i);
			}
			for(int i = 0; i < c_length; i++)
			{
				*(_text + _length + i) = *(c + i);
			}
			*(_text + _length + c_length) = '\0';

			delete[] tmp;

			_length += c_length;
		}
		
		void concatenate(string s) //Concatenate with another string
		{
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

		void insert(char c, int index)
		{
			if(index < 0 || index > _length) { throw new exception("Index out of bounds in string"); }
			else
			{
				char* tmp = _text;
				_text = new char[_length + 2];
				for(int i = 0; i < index; i++)
				{
					*(_text + i) = *(tmp + i);
				}
				*(_text + index) = c;
				for(int i = index; i < _length; i++)
				{
					*(_text + i + 1) = *(tmp + i);
				}
				*(_text + _length + 1) = '\0';
				_length++;
				delete[] tmp;
			}
		}

		void insert(const char* c, int index)
		{
			if(index < 0 || index > _length) { throw new exception("Index out of bounds in string"); }
			else
			{
				int c_length = 0;
				while(*(c + c_length) != '\0') { c_length++; }

				char* tmp = _text;
				_text = new char[_length + c_length + 1];
				for(int i = 0; i < index; i++)
				{
					*(_text + i) = *(tmp + i);
				}
				for(int i = 0; i < c_length; i++)
				{
					*(_text + index + i) = *(c + i);
				}
				for(int i = index; i < _length; i++)
				{
					*(_text + i + c_length) = *(tmp + i);
				}
				*(_text + _length + c_length) = '\0';
				_length += c_length;
				delete[] tmp;
			}
		}

		void insert(string s, int index)
		{
			if(index < 0 || index > _length) { throw new exception("Index out of bounds in string"); }
			else
			{
				char* tmp = _text;
				_text = new char[_length + s._length + 1];
				for(int i = 0; i < index; i++)
				{
					*(_text + i) = *(tmp + i);
				}
				for(int i = 0; i < s._length; i++)
				{
					*(_text + index + i) = *(s._text + i);
				}
				for(int i = index; i < _length; i++)
				{
					*(_text + i + s._length) = *(tmp + i);
				}
				*(_text + _length + s._length) = '\0';
				_length += s._length;
				delete[] tmp;
			}
		}

		void replace(char find, char replace) 
		{
			for(int i = 0; i < _length; i++)
			{
				if(*(_text + i) == find) { *(_text + i) = replace; }
			}
		}

		void replace(int index, char c)
		{
			if(index < 0 || index > _length) { throw new exception("Index out of bounds in string"); }
			else { *(_text + index) = c; }
		}

		void operator+=(char c) { concatenate(c); }
		void operator+=(const char* c) { concatenate(c); }
		void operator+=(string s) { concatenate(s); }
		
		bool equals(string s)
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

		bool equals(const char* c)
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

		bool operator==(const char* c) { return equals(c); }
		bool operator==(string s) { return equals(s); }

		char& operator[] (int index)
		{
			if(index < 0 || index >= _length) { throw new exception("Index out of bounds in string"); }
			else { return *(_text + index); }
		}

		char* copy() //Return a copy of the pointer with the data
		{
			char* tmp = new char[_length + 1];
			for(int i = 0; i <= _length; i++) //Copy data over including null terminator
			{
				*(tmp + i) = *(_text + i);
			}
			return tmp;
		}

		char* text() //Return the text pointer for whatever reason
		{
			return _text;
		}

		char at(int index)
		{
			if(index < 0 || index >= _length) { throw new exception("Index out of bounds in string"); }
			else { return *(_text + index); }
		}
		
		int length() { return _length; } //Returns the length - the length is a private variable so it isn't screwed with		

		string operator+(string s) { string r(*this); r.concatenate(s); return r; }		
		string operator+(const char* c) { string r(*this); r.concatenate(c); return r; }		
		string operator+(char c) { string r(*this); r.concatenate(c); return r; }		
	};

	char* getSubstring(string s, int start, int end) //Returns char* so redundant conversion to string doesn't happen when char* wanted
	{
		if((start < 0 || start >= s.length()) || (end < 0 || end >= s.length())) { throw new exception("Index out of bounds in string"); }
		else 
		{
			char* tmp = new char[end - start + 1];
			char* base = s.text();
			for(int i = start; i < end; i++)
			{
				*(tmp + i - start) = *(base + i);
			}
			*(tmp + end - start) = '\0';
			return tmp;
		}
	}
};

#endif