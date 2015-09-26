#mod3
mod3 is the name for a one-man project to build a cross-platform C++ library with lots of functionality. Right now mod3 contains two data structures but much more should come sometime in the future.
###goals
The main goal of mod3 is to build a comprehensive C++ library that makes it simple to compile code compatible with multiple operating systems. It is meant to support as wide of a range of functions as possible, which in the future will include the types of files it will be able to load and the types of applications it will be able to create.
###functionality
Right now mod3 has only a few classes that do very little.
#####string
The string class contains data for a string. It can be constructed from a char\* or a const char\*, or just a single char. When being constructed from a const char\*, the data must be copied over. The string class has a few methods used to manipulate it. These include the at(index) method, which returns the character at the specified index, and the set(value,index) method which sets the value at the specified index. Strings can also be concatenated with other strings or char*s with the concatenate() method or the + or += operators. Sadly, the order of operands in string functions is not yet consistent with those in lists.
#####list
The list<T> class contains a list of elements of type T. The list class includes methods for manipulating these elements, including the get() method and set() method. The list class also has the operator [], which returns a reference to the value at the index specified, allowing modification of values such as `myIntList[0] = 23`. The list class also has a template specialization list<void>, which does not have the [] operator but does cast all elements retrieved to the type specified.
#####exception
A general exception class thrown by other mod3 classes when they encounter a strange scenario. The exception class has the accessor message() which returns a const char\* containing the message text of the exception thrown.
###format
mod3 is meant to be a consistent format but isn't quite formatted consistently as of the current version. The order of operands in the string class is (value, index) while in the list class it is (index, value).

All mod3 classes are located in the mod3 namespace.
###misc
In the future detailed documentation about mod3 as well as essentially an instruction manual should be available [here](http://themonsterfromthedeep.github.io/mod3/).
