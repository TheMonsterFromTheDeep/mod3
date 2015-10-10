#ifndef __INCL_MEMORY
#define __INCL_MEMORY

namespace mod3 {
	typedef unsigned long idx; //Stores either a list length or index, ergo called "idx"
	typedef unsigned char byte; //A simple "byte" is simply an unsigned char, which is essentially a one-byte unsigned integer in memory
	
	typedef enum bit: byte {
		ZERO = 0,
		ONE = 1
	} bit;

	namespace memory {
		unsigned short calculateByteLength() {
			short length = 0;
			byte b = 1;
			while(b != 0) {
				length++;
				b <<= 1;
			}
			return length;
		}

		const unsigned short bytelength = calculateByteLength(); //Bytelength is a short because if the length of a byte is more than 65536, than that computer shouldn't be running this code

		template<class T>
		T* getNullified() {
			byte* tmp = new byte[sizeof(T)];
			for(int i = 0; i < sizeof(T); i++) {
				*(tmp + i) = 0;
			}
			return reinterpret_cast<T*>(tmp);
		}

		template<class T>
		T* getNullifiedSet(idx size) {
			byte* tmp = new byte[sizeof(T) * size];
			for(idx i = 0; i < sizeof(T) * size; i++) {
				*(tmp + i) = 0;
			}
			return reinterpret_cast<T*>(tmp);
		}

		template<class T>
		int typeSizeInBits() {
			return sizeof(T) * bytelength;
		}
	}
}

#endif