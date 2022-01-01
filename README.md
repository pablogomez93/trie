trie
====

An implementation of a trie map with basic and common methods, in C++

Below are listed the complexity for each class method

Constructor

	- Trie();	Constant, O(1).

Methods

	- define(const str, const T&) 	Linear in length of str passed by parameter, O(str.length).
	
	- defined(const str)			Linear in length of str passed by parameter plus copy time of type T, O(str.length + copy(T)).
	
	- value(const str)				Linear in length of str passed by parameter, O(str.length).

	- keysCount()					Constant, O(1).

	- erase(const str)				Linear in length of str passed by parameter (destruction) plus the number of elements defined (moving keys), O(str.length + keysCount).

	- keys();						Returns a iterator of the keys defined at now. Constant, O(Iterator default constructor).

Iterator
	
	- Iterator(const Trie<T>& t)	Linear in quantity of keys defined in the map at the requested moment, O(keysCount).

	- advance()						Increase pointer to next key. Constant, O(1).

	- thereIsMore()					Constant, O(1).

	- next()						Return a reference to current key. Constant, O(1)
