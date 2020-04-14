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


// global variables
    const static string& great = "great-" ;
    const static string& grand = "grand" ;


Tree::Tree(const string& head) : _root(new node(head)), _size(1) 
{
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
    //cout <<  decendant -> getName() << " , "  << decendant -> _father ->getName() << endl;
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
   // cout <<  decendant -> getName() << " , "  << decendant -> _mother ->getName() << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
    return *this;
}

const string Tree::relation(const string& family_member)
{
    if (_root -> getName() == family_member)
    {
        return "me";
    }
    try{
    node* ancestor = search(family_member, _root);
    //cout << "ancestor is : " << ancestor -> getName() << endl;
    if (ancestor == NULL)
    {
        return "unrelated" ;
    }
    int counter;
    counter = countTreeLevel(ancestor,0);

    const string& sex = ancestor -> whatIsMySex() ? "mother" : "father" ;


    //cout << " levels = " << counter << endl;
    if ( counter == 1 )
    { 
        return sex;
    }
    else if ( counter == 2 ) 
    {
         return grand + sex ;
    }
    else
    {
        
        string ans = "";
        
        size_t diff = counter - 2 ;
        for (size_t i = diff; i < counter; i++)
        {
            
            ans.append(great);
        }
            ans.append(grand);
            ans.append(sex);
            return ans;
    }
} 
catch (const exception& e) {
    cout << e.what() << endl;
}
return " i got here somehow ";
}

int Tree::countTreeLevel(node* countFromHere,int counter)
{
    //cout << " Goes with this line is the lever counter " << counter << endl;
    if ( countFromHere -> getSon() != NULL )
    {
        counter++;
        return countTreeLevel ( countFromHere -> getSon() , counter );
    }
    
    return counter;
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
    cout << endl;
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

//constructor
node::node(const string &name) : _name(name), _father(nullptr), _mother(nullptr), _origin_son(nullptr) {}


node* node::addMother(const string &mother_name)
{
    this->_mother = new node(mother_name);
    this -> _mother -> _origin_son = this ;
    return this;
}
node* node::addFather(const string &father_name){
    this->_father = new node(father_name);
    this -> _father -> _origin_son = this;
    return this;
}

bool node::whatIsMySex()
{
    //cout << " every name that goes with this line is a part of WHATISMYSEX func, this time it is =  " << this -> getName() << endl;
    
    if ( this -> getSon() -> getMother() != NULL && this -> getName() == this -> getSon() -> getMother() -> getName() )
    {
        return true;
    }
    else
    {
        return false;
    }
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
node* node::getSon(){
    return this -> _origin_son;
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
                 return NULL; // it's neither of them.
             }
         }
     }
    
     return NULL;
 }
     
     
     
     




 



