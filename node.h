//Header guards and imports
#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>

using namespace std;

//Creates Node class
class Node{
	//public constructor, destructor, and functions
	public:
		Node(int);
		~Node();
		int getValue();
		void setValue(int);
	//private variables
	private:
		int value;
};
//end of header guard
#endif
