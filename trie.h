#ifndef TRIE_H
#define TRIE_H

#include <list>
#include <string>
#include <vector>

using namespace std;


template<typename T>
class Trie {

	public:
	  	class Iterator;

		Trie();
		~Trie();
		void define(const string, const T&);
		bool defined(const string) const;
		T& value(const string) const;
		int keysCount() const;
		const Iterator keys() const;

		class Iterator{
			
			public:	
				Iterator(const Trie<T>& trie);
				bool thereIsMore() const;
				void advance();
				string next() const;
			
			private:
				list<string>::const_iterator _keysIterator;
				list<string>::const_iterator _lastKeyIterate;
		
		};


	private:
		struct Node {
			T* value;
			vector<Node*> chars;
			Node* parent;
			int countNotNull;

			Node(){
				this->value = NULL;
				this->parent = NULL;
				this->chars = vector<Node*>(256,NULL);
				this->countNotNull = 0;
			}

			~Node(){
				if(value != NULL)
					delete value;

				for(int i = 256; i>0; i--)
					if(chars[i-1] != NULL)
						delete chars[i-1];
			}

		};

		Node* _root;
		list<string> _keys;

};


template<class T>
Trie<T>::Trie(){
	_keys = list<string>();
	_root = new Node();
}


template<class T>
Trie<T>::~Trie(){
	delete _root;
}


template<class T>
void Trie<T>::define(const string key, const T& value){
	Node* iter = _root;
	
	for(int i = 0; i < key.length(); i++){
		int characterPos = (int)key[i];

		if(iter->chars[characterPos] == NULL){
			Node* newNode = new Node();
			newNode->parent = iter;

			iter->chars[characterPos] = newNode;
			iter->countNotNull++;
		}

		iter = iter->chars[characterPos];
	}

	if(iter->value == NULL)
		_keys.push_back(key);
	else
		delete iter->value;
	
	iter->value = new T(value);
}


template<class T>
bool Trie<T>::defined(const string key) const{
	Node* iter = _root;
	
	for (int i = 0; i < key.length(); ++i){
		int characterPos = (int)key[i];

		if(iter->chars[characterPos] != NULL)
			iter = iter->chars[characterPos];
		else
			return false;
	}

	return iter->value != NULL;
}


template<class T>
T& Trie<T>::value(const string key) const{
	Node* iter = _root;
	
	for(int i = 0; i < key.length() ; i++){
		int characterPos = (int)key[i];
		iter = iter->chars[characterPos];
	}

	return *iter->value;
}


template<class T>
int Trie<T>::keysCount() const{
	return _keys.size();
}


template<class T>
const typename Trie<T>::Iterator Trie<T>::keys() const{
	return Iterator(*this);
}



/*
 * Keys iterator impl. Is a traslator of the list class iterator.
 */

template<class T>
Trie<T>::Iterator::Iterator(const Trie<T>& trie){
	_keysIterator = trie._keys.begin();
	_lastKeyIterate = trie._keys.end();
}

template<class T>
void Trie<T>::Iterator::advance(){
	_keysIterator++;
}

template<class T>
string Trie<T>::Iterator::next() const{
	return *_keysIterator;
}

template<class T>
bool Trie<T>::Iterator::thereIsMore() const{
	return _keysIterator != _lastKeyIterate;
}


#endif //TRIE_H