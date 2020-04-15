#pragma once
#include <iostream>
#include <string>

/*
using std::string;
using std::cout;
using std::endl;
using std::invalid_argument;
*/
//using namespace std;

namespace family
{

class node
{
private:
    std::string _name;
    int _myLevel;

public:
    node*  _father;
    node*  _mother;
    node*  _origin_son;

    //Structure
    node(const std::string &name); 
    node(node*);
    const std::string& getName();
    const int& getLevel();
    void setLevel(const int&);
    node* getMother();
    node* getFather();
    node* getSon();
    void deleteMother();
    void deleteFather();
    
    //Methods
    node* addMother(const std::string &mother_name);
    node* addFather(const std::string &father_name);
    node *relation(node *relativeName);
    void freeSubtree(node *ptr);
    node *find(const std::string &relationship);
    node *MinValueSubtree(node *root);
    void remove();
    bool whatIsMySex();
    void nodeId();
    bool goingSomeWhere(const int& level);

    friend class Tree;

};

class Tree
{

private:
    node* _root;
    unsigned int _size;
    node* find_node(const std::string& relation);
    void remove_node(node*);
    void print_node(node*);
    node* find_node_by_name_father(const std::string& name,node* current);
    node* find_node_by_name_mother(const std::string& name,node* current);
    node* search(const std::string& decendant, node* current);
    const std::string& find2GensOfRoot(const std::string &relation);
    int countFreq(const std::string& pat, const std::string& txt);
    const std::string candidate(bool sex,const int& wanted_level,node* cand);
public:
    Tree(const std::string &head);
    //~Tree();
    Tree &addMother(const std::string &son, const std::string &mother_name);
    Tree &addFather(const std::string &son, const std::string &father);
    void remove(const std::string&);
    const std::string find(const std::string&);
    const std::string relation(const std::string& family_member);
    void display();
    int countTreeLevel(node* countFromHere,int counter);

};

} // namespace family
