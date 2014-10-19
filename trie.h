#ifndef TRIE_H
#define TRIE_H

#include <list>
#include <string>
#include <vector>

using namespace std;


template<class T>
class Trie {
	
	private:
		struct Node {
			T* value;
			vector<Node*> chars;
			Node* parent;
			int countNotNull;
			int parentPosition;

			Node(){
				this->value = NULL;
				this->parent = NULL;
				this->chars = vector<Node*>(256,NULL);
				this->countNotNull = 0;
				this->parentPosition = -1;
			}

			~Node(){
				if(value != NULL){
					delete value;
					value = NULL;
				}

				for(int i = 256; i>0; i--)
					if(chars[i-1] != NULL){
						delete chars[i-1];
						chars[i-1] = NULL;
					}
			
			}

		};

		Node* _root;
		vector<Node*> _keysRef;


	public:
	  	class Iterator;

		Trie();
		~Trie();
		void define(const string, const T&);
		bool defined(const string) const;
		T& value(const string) const;
		void erase(const string);
		int keysCount() const;
		const Iterator keys() const;

		class Iterator{
			
			public:	
				Iterator(const Trie<T>& trie);
				bool thereIsMore() const;
				void advance();
				string next() const;
			
			private:
				int _current;
				vector<Node*> _ptrToKeys;
		
		};

};


template<class T>
Trie<T>::Trie(){
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
			newNode->parentPosition = characterPos;

			iter->chars[characterPos] = newNode;
			iter->countNotNull++;
		}

		iter = iter->chars[characterPos];
	}

	if(iter->value == NULL)
		_keysRef.push_back(iter);
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
	
	for(int i = 0; i < key.length() ; i++)
		iter = iter->chars[(int)key[i]];

	return *iter->value;
}


template<class T>
void Trie<T>::erase(const string key){
	Node* iter = _root;
	
	for(int i = 0; i < key.length() ; i++)
		iter = iter->chars[(int)key[i]];

	for (int i = 0; i < _keysRef.size(); i++)
		if(_keysRef[i] == iter){
			_keysRef[i] = NULL;
			_keysRef.erase(_keysRef.begin() + i);
			break;
		}


	if(iter->countNotNull == 0){

		for (int i = key.length()-1; i >= 0 ; i--){
			iter = iter->parent;

			if(iter->countNotNull > 1 || i == 0){
				int characterPos = (int)key[i];

				Node* buffer = iter->chars[characterPos];
				iter->chars[characterPos] = NULL;
				delete buffer;
				break;
			}
		}

	}else{
		delete iter->value;
		iter->value = NULL;
	}

}


template<class T>
int Trie<T>::keysCount() const{
	return _keysRef.size();
}


template<class T>
const typename Trie<T>::Iterator Trie<T>::keys() const{
	return Iterator(*this);
}



/*
 * Keys iterator implementation.
 */

template<class T>
Trie<T>::Iterator::Iterator(const Trie<T>& trie){
	_current = 0;
	_ptrToKeys = trie._keysRef;
}

template<class T>
void Trie<T>::Iterator::advance(){
	_current++;
}

template<class T>
string Trie<T>::Iterator::next() const{
	Node* temp = _ptrToKeys[_current];
	list<char> chars;

	while(temp->parentPosition != -1){
		chars.push_back((char)temp->parentPosition);
		temp = temp->parent;
	}
	
	int strSize = chars.size();
	
	int i = strSize-1;
	char ret[strSize+1];
	for (list<char>::iterator it=chars.begin(); it!=chars.end() ; ++it){
    	ret[i] = *it;
    	i--;
    }
    
    ret[strSize] = '\0';
	return ret;
}

template<class T>
bool Trie<T>::Iterator::thereIsMore() const{
	return _current < _ptrToKeys.size();
}


#endif //TRIE_H