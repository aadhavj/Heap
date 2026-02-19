//imports
#include "node.h"
#include <iostream>
#include <cstring>
using namespace std;

//Node constructor
Node::Node(int inputValue){
	value = inputValue;
	right = nullptr;
	left = nullptr;	
}
//Node destructor
Node::~Node(){}

//Get right node
Node* Node::getRight(){
	return right;
}

//Get left node
Node* Node::getLeft(){
	return left;
}

//Set right node
void Node::setRight(Node* inputRight){
	right = inputRight;
}

//Set left node
void Node::setLeft(Node* inputLeft){
	left = inputLeft;
}

//Get value
int Node::getValue(){
	return value;
}

//Set value
void Node::setValue(int newVal){
	value = newVal;
}

