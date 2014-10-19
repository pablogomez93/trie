#include <assert.h>
#include <iostream>
#include <list>
#include "trie.h"

void define_noBreak_test();
void defined_test();
void values_goodSave_test();
void keysIterator_test();
void redefinitionOfKeys_test();
void eraseKeys_test();

int main(){

		define_noBreak_test();
		defined_test();
		values_goodSave_test();
		keysIterator_test();
		redefinitionOfKeys_test();
		eraseKeys_test();

		return 0;
}

void define_noBreak_test(){
	Trie<int> t = Trie<int>();
	t.define("test1",2);
	t.define("test2",67);
	t.define("test3",4);
	t.define("test4",22);
}

void defined_test(){
	Trie<int> trie = Trie<int>();
	trie.define("test1",22);
	trie.define("tesa-test4",4);
	trie.define("tesa-test5",5);
	trie.define("tesa-test6",6);
	trie.define("tesa-test8",8);
	assert(trie.defined("test1"));
	assert(!trie.defined("test2"));
	assert(!trie.defined("test4"));
	assert(trie.defined("tesa-test4"));
	assert(trie.defined("tesa-test5"));
	assert(trie.defined("tesa-test6"));
	assert(trie.defined("tesa-test8"));
}

void values_goodSave_test(){
	Trie<int> trie2 = Trie<int>();
	trie2.define("test1",22);
	trie2.define("tesa-test4",4);
	trie2.define("tesa-test5",5);
	trie2.define("tesa-test6",6);
	trie2.define("tesa-test8",8);
	assert(trie2.value("test1") == 22);
	assert(trie2.value("tesa-test4") == 4);
	assert(trie2.value("tesa-test5") == 5);
	assert(trie2.value("tesa-test6") == 6);
	assert(trie2.value("tesa-test8") == 8);	
}

void keysIterator_test(){
	Trie<int> trie3 = Trie<int>();
	trie3.define("test1",22);
	trie3.define("tesa-test4",4);
	trie3.define("tesa-test5",5);
	trie3.define("tesa-test6",6);
	trie3.define("tesa-test8",8);

	list<string> copys;
	copys.push_back("test1");
	copys.push_back("tesa-test4");
	copys.push_back("tesa-test5");
	copys.push_back("tesa-test6");
	copys.push_back("tesa-test8");

	list<string>::const_iterator copyListIt = copys.begin();

	typename Trie<int>::Iterator it = trie3.keys();
	while(it.thereIsMore()){
		assert(it.next() == *copyListIt);
		copyListIt++;
		it.advance();
	}

	assert(!it.thereIsMore());
}

void redefinitionOfKeys_test(){
	Trie<int> d = Trie<int>();
	assert(d.keysCount() == 0);
	d.define("test",22);
	assert(d.keysCount() == 1);
	d.define("de",4);
	assert(d.keysCount() == 2);
	d.define("cantidad",5);
	d.define("de claves",6);
	assert(d.keysCount() == 4);
	d.define("definidas",7);
	assert(d.keysCount() == 5);

	//Redefinition o a key must not add a key to a keys set.
	d.define("test",25);
	d.define("de",45);
	d.define("cantidad",55);
	d.define("de claves",65);
	d.define("definidas",75);
	assert(d.keysCount() == 5);

	d.define("agregado Extra De Clave",8);
	assert(d.keysCount() == 6);

	d.define("test",226);
	d.define("de",46);
	d.define("cantidad",56);
	d.define("de claves",66);
	d.define("definidas",76);
	assert(d.keysCount() == 6);
}

void eraseKeys_test(){
	Trie<int> trie8 = Trie<int>();
	trie8.define("test",22);
	trie8.define("de",4);
	trie8.define("borrado",5);
	trie8.define("de alguna",6);
	trie8.define("clave",7);

	assert(trie8.keysCount() == 5);
	assert(trie8.value("test") == 22);
	assert(trie8.value("de") == 4);
	assert(trie8.value("borrado") == 5);
	assert(trie8.value("de alguna") == 6);
	assert(trie8.value("clave") == 7);

	typename Trie<int>::Iterator testIter = trie8.keys();
	assert(testIter.thereIsMore());
	while(testIter.thereIsMore()){
		assert(testIter.next() == "test" 
			|| testIter.next() == "de" 
			|| testIter.next() == "borrado" 
			|| testIter.next() == "de alguna" 
			|| testIter.next() == "clave");
		
		testIter.advance();
	}

	trie8.erase("borrado");
	trie8.erase("test");

	assert(trie8.keysCount() == 3);
	assert(trie8.value("de") == 4);
	assert(trie8.value("de alguna") == 6);
	assert(trie8.value("clave") == 7);

	testIter = trie8.keys();
	assert(testIter.thereIsMore());
	while(testIter.thereIsMore()){
		assert(testIter.next() == "de" 
			|| testIter.next() == "de alguna" 
			|| testIter.next() == "clave");
		
		testIter.advance();
	}

	trie8.erase("de");
	trie8.erase("de alguna");
	trie8.erase("clave");

	testIter = trie8.keys();
	assert(!testIter.thereIsMore());
	assert(trie8.keysCount() == 0);

	trie8.define("a",4);
	trie8.define("a",5);
	trie8.define("aa",6);
	trie8.define("ab",4);
	trie8.define("",4);

	assert(trie8.keysCount() == 4);

	trie8.erase("");

	assert(trie8.keysCount() == 3);

	testIter = trie8.keys();
	assert(testIter.thereIsMore());
	while(testIter.thereIsMore()){
		assert(testIter.next() == "a" 
			|| testIter.next() == "aa" 
			|| testIter.next() == "ab");
		
		testIter.advance();
	}

	trie8.erase("a");

	assert(trie8.keysCount() == 2);

	testIter = trie8.keys();
	assert(testIter.thereIsMore());
	while(testIter.thereIsMore()){
		assert(testIter.next() == "aa" 
			|| testIter.next() == "ab");
		
		testIter.advance();
	}

	trie8.erase("ab");

	assert(trie8.keysCount() == 1);

	testIter = trie8.keys();
	assert(testIter.thereIsMore());
	while(testIter.thereIsMore()){
		assert(testIter.next() == "aa");
		
		testIter.advance();
	}

	trie8.erase("aa");

	testIter = trie8.keys();
	assert(!testIter.thereIsMore());
	assert(trie8.keysCount() == 0);
}