#pragma once

#ifndef __INCL_STRING
#define __INCL_STRING

namespace mod3
{
	class string
	{
	private:
		const char* _data; //Stores the value of the string
		int _length; //Stores the length of the string
	public:
		string() //Default constructor
		{
			_data = "\0"; //The string simply consists of a null terminator
			_length = 0; //The useable length of the string is zero
		}

		string(const char* value) //Creating the string from a const char literal is simple
		{
			_data = value;
		}

		string(const char* &value)  //Creating a string from a const char value takes a little bit of work
		{
			int length = 0; //First the length is calculated with a while loop
			while(*(value + length) != '\0')
			{
				length++;
			}
			char* tmp = new char[length++]; //Data is allocated for the new string
			for(int i = 0; i < length; i++)
			{
				*(tmp + i) = *(value + i);
			}
			_data = tmp; //The value of the string is set
		}

		int length() { return _length; } //Returns the length - the length is a private variable so it isn't screwed with
	};
};

#endif