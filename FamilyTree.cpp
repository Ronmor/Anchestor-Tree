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
/*
Tree::~Tree(){
    I SAW SOME UNBELIVIBLE THINGS UNDER THE HOOD
    AT THE END OF MAIN FUNCTION AT THE DEMO FILE THIS DESTRUCTOR IS CALLED BY THE COMPILER
    AS MUCH AS IT IS AN EFFICIENT, IT CAUSED TROUBLES

    remove_node(_root);
}
*/
void Tree::remove_node(node* ptr)
{
    //cout << "inside remove_node with " << ptr -> getName() << endl;
    if (ptr != NULL)
    {
        //cout << ptr ->getName() << endl;  
        cout << "removed" << ptr -> getName() << endl;
        delete ptr;
        return;
    }
    else
        return;
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
    //cout << "succesfully entered relation function " << endl;
    if (_root -> getName() == family_member)
    {
        return "me";
    }
    else
    {
        node* ancestor = search(family_member, _root);
        //cout << "search succesfully returned " << endl;
        if (ancestor == NULL)
        {
            return "unrelated" ;
        }
        else
        {
            int counter;
            //cout << " Attempting counting " << endl;
            counter = countTreeLevel(ancestor,0);
            //cout << " counted succesfully, counter = " << counter << endl;
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
        
        int diff = counter - 2 ;
        int i = 0;
        for (; i < diff; i++)
        {
            //cout << "i = " << i << endl;
            ans.append(great);
        }
            ans.append(grand);
            ans.append(sex);
            return ans;
    }
    }
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

const string Tree::find(const string &relationship)
{
    
    
    if (  (int( relationship.find("mother") ) == -1 && int( relationship.find("father") ) == -1 ) )
    {
        throw invalid_argument("The tree cannot handle the '"+relationship+"' relation");
    }
    try{
        if (relationship == "mother" && _root -> getMother() != NULL )
        {
            return _root->getMother()->getName();
        }
        else if (relationship == "father" && _root -> getFather() != NULL )
        {
            return _root->getFather()->getName();
        }
        if (int( relationship.find("great")) ==  -1 )
            {
               return find2GensOfRoot(relationship);
            }       
        else
            {
            const int wanted_level = countFreq("great-", relationship) + 2; // the number of "great-" in the string + 2
            bool sexOfCandidate = int( relationship.find("mother") ) != -1 ? true : false ;
            //const string& cand_name = candidate(sexOfCandidate,wanted_level,_root);
            return   (candidate(sexOfCandidate,wanted_level,_root));
            }
        }catch
        (const exception& e) {
        cout << e.what()  << endl;
    }
    
    return relationship;
}

const string& Tree::find2GensOfRoot(const string &relation)
{
            if ( int (relation.find("mother") ) != -1 )
            {
                if (_root ->getMother()->getMother() != NULL)
                {
                    return _root -> getMother() ->getMother() ->getName();
                }
                else if (_root ->getFather()->getMother() != NULL)
                {
                    return _root -> getFather() ->getMother() ->getName();
                }
                else
                {
                    return string(_root -> getName()).append(" has no grandmother yet");
                }   
            }
            else if (  int(relation.find("father")) != -1 )
            {
               if (_root ->getMother()->getFather() != NULL)
                {
                    return _root -> getMother() ->getFather() ->getName();
                }
                else if (_root ->getFather()->getFather() != NULL)
                {
                    return _root -> getFather() ->getFather() ->getName();
                }
                else
                {
                    return string(_root -> getName()).append("has no grandfather yet");
                }
}
            return relation;
}

void Tree::remove(const string& family_memeber_toRemove){
    node* temp = search(family_memeber_toRemove,_root);
    if (family_memeber_toRemove == _root ->getName())
    {
        throw invalid_argument("deleting root is forbidden");
    }
    if (temp == NULL)
    {
        throw invalid_argument("either removed already or wasn't there on the first place");
    }
    try{
    if (temp -> getFather() != NULL) { remove(temp -> getFather() -> getName()); }
    if (temp -> getMother() != NULL) { remove(temp -> getMother() -> getName()); }
    
    if (temp -> getSon() != NULL && family_memeber_toRemove == temp->getName() )
    {
        //cout <<  " this child will not longer recognize father " << temp ->getSon() -> getName() << endl;
        remove_node( temp );
        temp -> getSon() -> _father =NULL;
    }
    else if (temp -> getSon() -> getMother() -> getName() == temp -> getName())
    {
        //cout <<  " this child will not longer recognize mother " << temp ->getSon() -> getName() << endl;
        remove_node(temp) ;
        temp -> getSon() -> _mother =NULL;
    }
    } catch (const exception& e){
        cout << e.what() << endl;
    }
}

void Tree::display()
{
    //cout << "enteres display" << endl;
    print_node(_root);
    cout << endl;
    //cout << "ended display" << endl;
}

node* Tree::find_node(const string& relation)
{
    return this->_root;
}

void Tree::print_node(node* current)
{
    //cout << "inside print_node, currently pointing at " << current -> getName() << endl;
    //current -> nodeId();
    if (current == NULL)
    {
        return;
    } 
    //cout <<  "name =" << current -> getName()  <<", level =" <<current->getLevel() << endl;
    if (current -> getFather() != NULL ){
      //  cout << "father = " << "print_node(" << current-> getFather()->getName()<<")   "<<endl;
        print_node(current-> getFather() );
    }
    
    if (current -> getMother() != NULL ) {
      //  cout << "print_node(" << current-> getMother()->getName()<<endl;
        print_node( current -> getMother () );                                    
}
cout << current->_name <<endl;
return;
}

void node::nodeId(){
    cout << " my name is : " <<  this -> getName() << endl;
    if (this -> _father) cout << " my father is : " <<  this -> _father -> getName() << endl;
    if (this -> _mother) cout << " my mother is : " <<  this -> _mother -> getName() << endl;
    return;

}

//constructor
node::node(const string &name) : _name(name), _myLevel(0) , _father(NULL), _mother(NULL), _origin_son(NULL) {}

node::node(node* _other) : _name(_other->_name), _myLevel(_other->_myLevel) , _father(_other->_father), _mother(_other->_mother), _origin_son(_other->_origin_son) {}


node* node::addMother(const string &mother_name)
{
    this->_mother = new node(mother_name);
    this -> _mother -> _origin_son = this ;
    const int& lev = 1 + this -> getLevel() ;
    this -> _mother -> setLevel(lev);
    return this;
}


node* node::addFather(const string &father_name){
    this->_father = new node(father_name);
    this -> _father -> _origin_son = this;
    const int& lev = 1 + this -> getLevel() ;
    this -> _father -> setLevel(lev);
    return this;
}

const string Tree::candidate(bool sex,const int& wanted_level,node* cand)
{   
    
    cout << "wanted_level = " << wanted_level << endl;
    cout << "in candidate, checking " << cand -> getName() << endl;
    /*
    if (0 == wanted_level && sex == cand -> whatIsMySex())
    {
        return const_cast<string&> (cand->getName());
    }
    if (cand -> getLevel() == wanted_level && sex != cand -> whatIsMySex())
    {
        throw string("unable to find match");
    }
    */
   if (wanted_level == 0)
   {
       return cand->getName();
   }
   if (wanted_level < 0)
   {
       throw invalid_argument("no match");
   }
    try
    {
        if ( 0 <= wanted_level && ( cand-> getMother() != NULL || cand -> getFather () != NULL )  )
    {
        if (cand -> getMother() != NULL && cand->goingSomeWhere(wanted_level,cand->getMother()) )
        { return candidate(sex,wanted_level,cand->getMother()); }
        else if (cand -> getFather() != NULL && cand ->goingSomeWhere( wanted_level, cand -> getFather() ) )
        { return candidate(sex,wanted_level,cand->getFather()); }
    }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return "error";
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
const int& node::getLevel()
        {
            return this ->_myLevel ;
        }
void node::setLevel(const int& depth)
        {
        this -> _myLevel = depth;
        }
node *node::find(const string &relation)
{
    return this;
}
bool node::goingSomeWhere(const int& level,node* current)
{
    if (current == NULL)
    {
        return false;
    }
    cout << current->getName() << ", level= " << current->getLevel() << endl;
    if (current->getLevel() == level)
    {
       return true;
    }
    else if (getLevel() < level)
    {
        /*
        if (getMother() == NULL && getFather() == NULL)
        {
            return false;
        }
        */
        if (getFather() != NULL)
        {
            return goingSomeWhere(level,current->getFather());
        }
        if (getMother() != NULL)
        {
            return goingSomeWhere(level,current->getMother());
        }
    }
    return false;
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


void node::deleteFather(){
        this -> _father = NULL ;
    }
void node::deleteMother(){
    this -> _mother = NULL;
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

 int Tree::countFreq(const string &pat,const string &txt) 
{ 
    int M = pat.length(); 
    int N = txt.length(); 
    int res = 0; 
    
    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++) 
    {  
        /* For current index i, check for  
           pattern match */
        int j; 
        for (j = 0; j < M; j++) 
            if (txt[i+j] != pat[j]) 
                break; 
   
        // if pat[0...M-1] = txt[i, i+1, ...i+M-1] 
        if (j == M)   
        { 
           res++; 
           j = 0; 
        } 
    } 
    return res; 
} 
