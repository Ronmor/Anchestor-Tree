#include "FamilyTree.hpp"
#include <stdexcept>
#include <iostream>


//using std::string::compare;
using family::node;
using family::Tree;
using std::cout;
using std::endl;
using std::string;
using std::exception;
using std::invalid_argument;


Tree::Tree(const string& head) : _root(new node(head)), _size(1) {
    cout << head <<endl;
}

Tree::~Tree(){
    remove_node(_root);
}

void Tree::remove_node(node *ptr)
{
    if (ptr == nullptr)
    {
        return;
    }
    else
        remove_node(ptr->_father);
        remove_node(ptr->_mother);
        delete ptr;
}

Tree& Tree::addFather(const string &son, const string &father)
{
    node* decendant = search(son, _root);
    if (decendant == NULL)
    {
        throw invalid_argument("an error has occured !  " +son +" is not a part of this family !");
    }
    else if (decendant != NULL && decendant -> getFather() != NULL)
    {
        throw invalid_argument("an error has occured !  " +son +" already has a father !");
    }
    try{
    decendant -> addFather(father);
    cout <<  decendant -> getName() << " , "  << decendant -> _father ->getName() << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
    return *this;
}

Tree& Tree::addMother(const string &son, const string &mother)
{
    node* decendant = search(son, _root);
    if (decendant == NULL)
    {
        throw invalid_argument("an error has occured !  " +son +" is not a part of this family !");
    }
    else if (decendant != NULL && decendant -> getMother() != NULL)
    {
        throw invalid_argument("an error has occured !  " +son +" already has a mother !");
    }
    try{
    decendant -> addMother(mother);
    cout <<  decendant -> getName() << " , "  << decendant -> _mother ->getName() << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
    return *this;
}

const string Tree::relation(const string& family_member)
{
    return " ";
}
const string& Tree::find(const string &relation)
{
    return relation;
}

void Tree::remove(const string& family_memeber_toRemove){
    node* temp = find_node(family_memeber_toRemove);
    remove_node(temp);
}

void Tree::display()
{
    print_node(_root);   
}

node* Tree::find_node(const string& relation)
{
    return this->_root;
}

void Tree::print_node(node* current)
{
    if (current == nullptr)
    {
        return;
    }
        
    print_node(current->_father);
    cout << current -> getName() << "\t";
    print_node( current -> _mother);                                    
}


node::node(const string &name) : _name(name), _father(nullptr), _mother(nullptr) {}


node* node::addMother(const string &mother_name)
{
    this->_mother = new node(mother_name);
    return this;
}
node* node::addFather(const string &father_name){
    this->_father = new node(father_name);
    return this;
}

node *node::find(const string &relation)
{
    return this;
}

const string& node::getName(){
    return this->_name;
}

node* node::getFather(){
    return this -> _father;
}

node* node::getMother(){
    return this -> _mother;
}

node* Tree::find_node_by_name_father(const string& name,node* current){
    if (current -> getFather() == nullptr && current -> getName() == name)
    {
        return current;
    }
    else if (current -> getName() == name && current -> getFather() != NULL)
    {
        throw invalid_argument("an error has occured !  " +name +" already has a father !");
    }
    else
    {
      return find_node_by_name_father(name,current -> getFather()) ;
 }
 }

node* Tree::find_node_by_name_mother(const string& name,node* current){
    if (current -> getMother() == nullptr && current -> getName() == name)
    {
        return current;
    }
    else if (current -> getName() == name && current -> getMother() != NULL)
    {
        throw invalid_argument("an error has occured !  " +name +" already has a father !");
    }
    else
    {
      return find_node_by_name_mother(name,current -> getMother()) ;
 }
 }

 node* Tree::search(const std::string& decendant,node* current){
     try{
     if (decendant == current -> getName())   // found you!
     {
         return current;
     }
     else if (current -> getFather() == NULL && current -> getMother() == NULL)
     /*
        poor baby has no parents, and since it's not him in the fist place there is no where to procced
        find a fat lady and tell her to sing , 'cause it's all over ! 
     */
     {
         return NULL;
     }
     else if( current -> getFather() != NULL && current -> getMother() == NULL) // only has a father
     {
         if (current -> getFather() -> getName() == decendant) // if the answer is your father
         {
             return current-> getFather();
         }
         else   // we should continue searching over this branch.
         {
             return search(decendant,current -> getFather());
         } 
     }
     else if (current -> getFather() == NULL && current -> getMother() != NULL) // similarly , has only mother.
     {
         if (current -> getMother() -> getName() == decendant)
         {
             return current-> getMother();
         }
         else
         {
             return search(decendant,current -> getMother());
         }
     }
     else if (current -> getFather() != NULL && current -> getMother() != NULL) // has both parents
     {
         if (current -> getMother() -> getName() == decendant) // if answer is currnet node's mother
         {
             return current-> getMother();
         }
         if (current -> getFather() -> getName() == decendant) // or it's father
         {
             return current-> getFather();
         }
         else
         {
             node* mother_can = search(decendant,current -> getMother()); // search recursively for ma
             node* father_can = search(decendant,current -> getFather()); // search recursively for pa
             if (father_can != NULL && mother_can == NULL) // one expilicit answer , it's daddy
             {
                 return father_can;
             }
             else if (father_can == NULL && mother_can != NULL) // one expilicit answer , it's mommy
             {
                 return mother_can;
             }
             else
             {
                 throw invalid_argument("unable to find"); // it's neither of them.
             }
         }
     }
     } catch (const exception& e) {
        cout << e.what() << endl;
    }
     return NULL;
 }
     
     
     
     




 
//constructor


