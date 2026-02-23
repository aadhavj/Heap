//imports
#include "node.h"
#include <iostream>
#include <cstring>
using namespace std;

//Node constructor
Node::Node(int inputValue){
	value = inputValue;	
}
//Node destructor
Node::~Node(){}

//Get value
int Node::getValue(){
	return value;
}

//Set value
void Node::setValue(int newVal){
	value = newVal;
}

