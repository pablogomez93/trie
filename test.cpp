#include <iostream>
#include <assert.h>
#include <string>
#include <list>
#include "trie.h"

int main(){

		Trie<int> t = Trie<int>();
		t.define("test1",2);
		t.define("test2",67);
		t.define("test3",4);
		t.define("test4",22);

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
		assert(it.thereIsMore());

		while(it.thereIsMore()){
			assert(it.next() == *copyListIt);
			copyListIt++;
			it.advance();
		}

		assert(!it.thereIsMore());



		// Trie<int> e = Trie<int>();
		// e.define("iterador_prueba_1",22);
		// e.define("iterador_prueba_2",4);
		// e.define("iterador_prueba_3",5);
		// e.define("iterador_prueba_4",6);
		// e.define("iterador_prueba_5",8);
		// typename Trie<int>::Iterador it = e.Claves();
		// std::cout << "\n";
		// while(it.HaySiguiente()){
		// 	std::cout << it.Siguiente() << "\n";
		// 	it.Avanzar();
		// }




		// Trie<int> d = Trie<int>();
		// d.define("test",22);
		// d.define("usando",4);
		// d.define("los",5);
		// d.define("assert",6);
		// typename Trie<int>::Iterador iter = d.Claves();
		// assert(iter.HaySiguiente(), true);
		// assert(iter.Siguiente(), "test");
		// iter.Avanzar();
		// assert(iter.HaySiguiente(), true);
		// assert(iter.Siguiente(), "usando");
		// iter.Avanzar();
		// assert(iter.HaySiguiente(), true);
		// assert(iter.Siguiente(), "los");
		// iter.Avanzar();
		// assert(iter.HaySiguiente(), true);
		// assert(iter.Siguiente(), "assert");
		// iter.Avanzar();
		// assert(iter.HaySiguiente(), false);




		Trie<int> trie6 = Trie<int>();
		trie6.define("test",22);
		trie6.define("de",4);
		trie6.define("cambio",5);
		trie6.define("de valor",6);
		trie6.define("por referencia",7);
		assert(trie6.value("test") == 22);
		assert(trie6.value("de") == 4);
		assert(trie6.value("cambio") == 5);
		assert(trie6.value("de valor") == 6);
		assert(trie6.value("por referencia") == 7);
		
		trie6.value("de valor") = 44;
		trie6.value("cambio") = 101;

		assert(trie6.value("test") == 22);
		assert(trie6.value("de") == 4);
		assert(trie6.value("cambio") == 101);
		assert(trie6.value("de valor") == 44);
		assert(trie6.value("por referencia") == 7);




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

		//Redefinicion de clave no deberia sumar una clave
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
