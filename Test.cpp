#include "doctest.h"
#include "FamilyTree.hpp"
#include <string>
#include <stdexcept>

using namespace std;
//using family::Tree;

    /*
    The House of Windsor is the reigning royal house of the United Kingdom and the other Commonwealth realms.
    BTW, Windsor decendants are known today as the royal family of the entire UK ! 
    */

static family::Tree windsor("Harry");

TEST_CASE("House of Windsor - addMother && addFather Tests"){
   CHECK_NOTHROW(windsor.addFather("Harry","Charles"));
   CHECK_NOTHROW(windsor.addMother("Harry","Diana"));
   CHECK_THROWS(windsor.addFather("Zeus","Harry"));
   CHECK_THROWS(windsor.addMother("Zeus","Harry"));
   CHECK_THROWS(windsor.addFather("Harry","Ron"));
   CHECK_THROWS(windsor.addMother("Harry","Alex"));
   CHECK_NOTHROW(windsor.addMother("Charles","Elizabeth_II"));
   CHECK_THROWS(windsor.addFather("Elizabeth","Zeus"));
   CHECK_NOTHROW(windsor.addFather("Charles","Phillip"));
   CHECK_THROWS(windsor.addFather("Charles","Ron"));
   CHECK_THROWS(windsor.addMother("Charles","Alex"));
   CHECK_NOTHROW(windsor.addMother("Elizabeth_II","Elizabeth"));
   CHECK_NOTHROW(windsor.addFather("Elizabeth_II","George_VI"));
   CHECK_THROWS(windsor.addFather("CElizabeth_II","Ron"));
   CHECK_THROWS(windsor.addMother("Elizabeth_II","Alex"));
   CHECK_NOTHROW(windsor.addMother("George_VI","Mary"));
   CHECK_NOTHROW(windsor.addFather("George_VI","George_V")); 
   CHECK_THROWS(windsor.addFather("George_VI","Ron"));
   CHECK_THROWS(windsor.addMother("George_VI","Alex"));
   CHECK_NOTHROW(windsor.addMother("George_V","Alexandra"));
   CHECK_NOTHROW(windsor.addFather("George_V","Edward_VII"));      
   CHECK_THROWS(windsor.addFather("George_V","Ron"));
   CHECK_THROWS(windsor.addMother("George_V","Alex"));
   CHECK_NOTHROW(windsor.addMother("Edward_VII","Victoria"));
   CHECK_NOTHROW(windsor.addFather("Edward_VII","Albert"));
   CHECK_THROWS(windsor.addFather("Edward_VII","Ron"));
   CHECK_THROWS(windsor.addMother("Edward_VII","Alex"));

    /*
    From now on testing the following scenarios:
    adding parents to a child that is not a part of the royal family (aka, not a node of our tree)
    Inspired by Shakira's famous song - Waka Waka
    */
   CHECK_THROWS(windsor.addFather("pressure","is"));
   CHECK_THROWS(windsor.addMother("on","you"));
   CHECK_THROWS(windsor.addFather("feel","it"));
   CHECK_THROWS(windsor.addMother("But","you've"));
   CHECK_THROWS(windsor.addFather("got","it"));
   CHECK_THROWS(windsor.addMother("all","belive"));
   CHECK_THROWS(windsor.addFather("it","Ron"));
   CHECK_THROWS(windsor.addMother("when","you"));
   CHECK_THROWS(windsor.addFather("fall","get"));
   CHECK_THROWS(windsor.addMother("up","oh"));
   CHECK_THROWS(windsor.addFather("oh","and"));
   CHECK_THROWS(windsor.addMother("if","you"));
   CHECK_THROWS(windsor.addFather("fall","get"));
   CHECK_THROWS(windsor.addMother("up","oh"));   
   CHECK_THROWS(windsor.addMother("oh","Tsamina"));
   CHECK_THROWS(windsor.addFather("mina","zangalewa"));
   CHECK_THROWS(windsor.addMother("Cause","This"));
   CHECK_THROWS(windsor.addFather("is","Africa"));
   CHECK_THROWS(windsor.addMother("Tsamina","mina"));
   CHECK_THROWS(windsor.addFather("eh","eh"));
   CHECK_THROWS(windsor.addMother("Waka","waka"));
   CHECK_THROWS(windsor.addFather("eh","eh"));
   CHECK_THROWS(windsor.addMother("Tsamina","mina"));
   CHECK_THROWS(windsor.addFather("mina","zangalewa"));
   CHECK_THROWS(windsor.addMother("This","time"));
   CHECK_THROWS(windsor.addFather("for","Africa"));

}
/*
TEST_CASE("House of Windsor - remove Tests"){
CHECK_NOTHROW(windsor.remove("Albert")); // should remove Albert
CHECK_THROWS(windsor.remove("Albert")); //   already removed
CHECK_NOTHROW(windsor.remove("Edward_VII")); // should remove Edward_VII and his mother Victoria
CHECK_THROWS(windsor.remove("Victoria")); //   already removed
CHECK_NOTHROW(windsor.addMother("Edward_VII","Victoria"));

// let us delete some people who are not on tree in the first place

CHECK_THROWS(windsor.remove("pressure"));
CHECK_THROWS(windsor.remove("on"));
CHECK_THROWS(windsor.remove("you"));
CHECK_THROWS(windsor.remove("belive"));
CHECK_THROWS(windsor.remove("it"));
CHECK_THROWS(windsor.remove("when"));
CHECK_THROWS(windsor.remove("fall"));
CHECK_THROWS(windsor.remove("get"));
CHECK_THROWS(windsor.remove("up"));
CHECK_THROWS(windsor.remove("Tsamina"));
CHECK_THROWS(windsor.remove("mina"));
CHECK_THROWS(windsor.remove("zangalewa"));


// remain only with a small family by removing a whole brach

CHECK_NOTHROW(windsor.remove("Charles")); // should work ok

}
*/
TEST_CASE("House of Windsor - relation Tests"){
    // royal
CHECK(windsor.relation("Charles") == string("father") );
CHECK(windsor.relation("Diana") == string("mother") );
CHECK(windsor.relation("Elizabeth_II") == string("grandmother") );
CHECK(windsor.relation("Phillip") == string("grandfather") );
CHECK(windsor.relation("Elizabeth") == string("great-grandmother") );
CHECK(windsor.relation("George_VI") == string("great-grandfather") );
CHECK(windsor.relation("Mary") == string("great-great-grandmother") );
CHECK(windsor.relation("George_V") == string("great-great-grandfather") );
CHECK(windsor.relation("Alexandra") == string("great-great-great-grandmother") );
CHECK(windsor.relation("Edward_VII") == string("great-great-great-grandfather") );
CHECK(windsor.relation("Victoria") == string("great-great-great-great-grandmother") );
CHECK(windsor.relation("Albert") == string("great-great-great-great-grandfather") );

    // not royal
CHECK( windsor.relation("dog") == string("unrelated") );
CHECK(windsor.relation("cat") == string("unrelated") );
CHECK(windsor.relation("fish") == string("unrelated") );
CHECK(windsor.relation("uncle") == string("unrelated") );
CHECK(windsor.relation("nephew") == string("unrelated") );
CHECK(windsor.relation("messi") == string("unrelated") );
CHECK(windsor.relation("ronaldo") == string("unrelated") );
CHECK(windsor.relation("lewandovski") == string("unrelated") );
CHECK(windsor.relation("halland") == string("unrelated") );
CHECK(windsor.relation("mbape") == string("unrelated") );
CHECK(windsor.relation("neymar") == string("unrelated") );
CHECK(windsor.relation("neta") == string("unrelated") );
CHECK(windsor.relation("ofri") == string("unrelated") );
CHECK(windsor.relation("ron") == string("unrelated") );
CHECK(windsor.relation("alex") == string("unrelated") );


}

TEST_CASE("House of Windsor - find Tests"){
    // valid cases
CHECK(windsor.find("father") == string("Charles") );
CHECK(windsor.find("mother") == string("Diana") );
CHECK(windsor.find("grandmother") == string("Elizabeth_II") );
CHECK(windsor.find("grandfather") == string("Phillip") );
CHECK(windsor.find("great-grandmother") == string("Elizabeth") );
CHECK(windsor.find("great-grandfather") == string("George_VI") );
CHECK(windsor.find("great-great-grandmother") == string("George_V") );
CHECK(windsor.find("great-great-grandfather") == string("Mary") );
CHECK(windsor.find("great-great-great-grandmother") == string("Alexandra") );
CHECK(windsor.find("great-great-great-grandfather") == string("Edward_VII") );
CHECK(windsor.find("great-great-great-great-grandmother") == string("Victoria") );
CHECK(windsor.find("great-great-great-great-grandfather") == string("Albert") );

    // invalid cases
CHECK_THROWS(windsor.find("dog"));
CHECK_THROWS(windsor.find("cat"));
CHECK_THROWS(windsor.find("fish"));
CHECK_THROWS(windsor.find("uncle"));
CHECK_THROWS(windsor.find("nephew"));
CHECK_THROWS(windsor.find("messi"));
CHECK_THROWS(windsor.find("ronaldo"));
CHECK_THROWS(windsor.find("lewandovski"));
CHECK_THROWS(windsor.find("halland"));
CHECK_THROWS(windsor.find("mbape"));
CHECK_THROWS(windsor.find("neymar"));
CHECK_THROWS(windsor.find("neta"));
CHECK_THROWS(windsor.find("ofri"));
CHECK_THROWS(windsor.find("ron"));
CHECK_THROWS(windsor.find("alex"));

}