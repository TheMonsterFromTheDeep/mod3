#ifndef __INCL_BITSET
#define __INCL_BITSET

#include "memory.hpp"
#include "exception.hpp"

namespace mod3 {
	typedef class BitString {
	private:
		byte _value;
	public:
		BitString() {
			_value = 0;
		}

		void set(unsigned short index, bit b) {
			if(index >= memory::bytelength) { throw mod3::exception("Index out of bounds in BitString"); }
			else {
				if(b == ONE) {
					_value |= (1 << index);
				}
				else {
					_value &= ~(1 << index);
				}
			}
		}

		bit get(unsigned short index) const {
			if(index >= memory::bytelength) { throw mod3::exception("Index out of bounds in BitString"); }
			else {
				return (((1 << index) & _value) == 0) ? ZERO : ONE;
			}
		}
	} BitString;

	typedef class BitSet {
	private:
		byte* _data; //Stores the data - the length of this pointer is equal to _length / 8 + 1
		idx _length;
	public:
		BitSet() {
			_length = 0;
			_data = nullptr;
		}

		BitSet(idx length) {
			_data = new byte[(length / memory::bytelength) + 1];
			for(idx i = 0; i < (length / memory::bytelength) + 1; i++) {
				_data[i] = 0; //Initialize value to be 00000000 (or other based on computer)
			}
			_length = length;
		}

		void set(idx index, bit b) {
			if(index >= _length) { throw mod3::exception("Index out of bounds in BitSet"); }
			else {
				//This equation sets the bit at the right byte to the specified bit.
				//First, the byte at _data + (index / 8) is accessed. This is the
				//index of the byte needed to be set because it returns the floor
				//of index / 8. This is then set using the |= operator to the bit
				//shifted by the index modulo 8. The index is modulo'd 8 so that it has
				//the proper remained from the index passed to the method.
				if(b == ONE) {
					*(_data + (index / memory::bytelength)) |= (1 << (index % memory::bytelength));
				}
				else {
					*(_data + (index / memory::bytelength)) &= ~(1 << (index % memory::bytelength));
				}

			}
		}

		bit get(idx index) const {
			if(index >= _length) { throw mod3::exception("Index out of bounds in BitSet"); }
			else {
				return (((1 << (index % memory::bytelength)) & *(_data + (index / memory::bytelength))) == 0) ? ZERO : ONE;
			}
		}
	} BitSet;
}

#endif