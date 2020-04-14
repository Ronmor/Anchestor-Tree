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
TEST_CASE("House of Windsor - remove Tests")
{
CHECK_NOTHROW(windsor.remove("Albert")); // should remove Albert
CHECK_THROW(windsor.remove("Albert")); //   already removed
CHECK_NOTHROW(windsor.remove("Edward_VII")); // should remove Edward_VII and his mother Victoria
CHECK_THROW(windsor.remove("Victoria")); //   already removed
CHECK_NOTHROW(windsor.addMother("Edward_VII","Victoria"));

// let us delete some people who are not on tree in the first place

CHECK_THROW(windsor.remove("pressure"));
CHECK_THROW(windsor.remove("on"));
CHECK_THROW(windsor.remove("you"));
CHECK_THROW(windsor.remove("belive"));
CHECK_THROW(windsor.remove("it"));
CHECK_THROW(windsor.remove("when"));
CHECK_THROW(windsor.remove("fall"));
CHECK_THROW(windsor.remove("get"));
CHECK_THROW(windsor.remove("up"));
CHECK_THROW(windsor.remove("Tsamina"));
CHECK_THROW(windsor.remove("mina"));
CHECK_THROW(windsor.remove("zangalewa"));


// remain only with a small family by removing a whole brach

CHECK_NOTHROW(windsor.remove("Charles")); // should work ok

}
TEST_CASE("House of Windsor - relation Tests"){}

TEST_CASE("House of Windsor - find Tests"){}