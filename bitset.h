#pragma once

#ifndef __INCL_BITSET
#define __INCL_BITSET

#include "byte.h"
#include "exception.h"

namespace mod3 {
	typedef enum bit: mod3::byte {
		ZERO = 0,
		ONE = 1
	} bit;

	typedef class BitString {
	private:
		byte _value;
	public:
		BitString() {
			_value = 0;
		}

		void push(bit b) {
			_value <<= 1;
			_value += b;
		}

		void set(int index, bit b) {
			if(index < 0 || index >= 8) { throw mod3::exception("Index out of bounds in BitString"); }
			else {
				if(b == ONE) {
					_value |= (1 << index);
				}
				else {
					_value &= ~(1 << index);
				}
			}
		}

		bit get(int index) {
			if(index < 0 || index >= 8) { throw mod3::exception("Index out of bounds in BitString"); }
			else {
				return (((1 << index) & _value) == 0) ? ZERO : ONE;
			}
		}
	} BitString;

	typedef class BitSet {
	private:
		byte* _data; //Stores the data - the length of this pointer is equal to _length % 8 + 1
		int _length;
	public:
		BitSet() {
			_length = 0;
			_data = nullptr;
		}

		BitSet(int length) {
			_data = new byte[(length / 8) + 1];
			_length = length;
		}

		void set(int index, bit b) {
			if(index < 0 || index >= _length) { throw mod3::exception("Index out of bounds in BitSet"); }
			else {
				//This equation sets the bit at the right byte to the specified bit.
				//First, the byte at _data + (index / 8) is accessed. This is the
				//index of the byte needed to be set because it returns the floor
				//of index / 8. This is then set using the |= operator to the bit
				//shifted by the index modulo 8. The index is modulo'd 8 so that it has
				//the proper remained from the index passed to the method.
				if(b == ONE) {
					*(_data + (index / 8)) |= (1 << (index % 8));
				}
				else {
					*(_data + (index / 8)) &= ~(0 << (index % 8));
				}
			}
		}

		bit get(int index) {
			if(index < 0 || index >= _length) { throw mod3::exception("Index out of bounds in BitSet"); }
			else {
				return (((1 << index) & *(_data + (index / 8))) == 0) ? ZERO : ONE;
			}
		}
	} BitSet;
}

#endif