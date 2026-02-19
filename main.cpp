#include <iostream>
#include <cstring>
#include "node.h"
using namespace std;

void addNode(int value, Node** treeArray);
void printTree(Node** treeArray);
//void Delete(Node** treeArray);
//void DeleteAll(Node** treeArray);

int main(){

	//Basic var instantiation
	char command[1000];
	Node** tree = new Node*[101];
	bool runProgram = true;
	for (int i = 0; i <= 101;i++){
		tree[i] = nullptr;
	}

	//Valid Command prompts
	char del[] = "DELETE";
	char delAll[] = "DELETEALL";
	char add[] = "ADD";
	char quit[] = "QUIT";

	while (runProgram){
		cout << "\nEnter Command(DELETE, DELETEALL, ADD, QUIT): ";
		cin >> command;
		command[9] = '\0';

		//Command recognition
		if (strcmp(command, del) == 0){
			cout << "Deletes stuff" << endl;
		}
		else if (strcmp(command, delAll) == 0){
			cout << "Deletes everything" << endl;
		}
		else if (strcmp(command, add) == 0){
			cout << "Value (-1 last val to terminate): " << endl;
			int addedValue;
			while (cin >> addedValue and addedValue != -1){
				addNode(addedValue,tree);
				printTree(tree);
			}
		}
		else if (strcmp(command, quit) == 0){
			cout << "Quitting..." << endl;
			runProgram = false;
		}
		else{
			cout << "Command prompt unrecognized" << endl;
		}
	}

	return 0;
}

void addNode(int value, Node** treeArray){
	Node *newNode = new Node(value);
	int searchIndex = 1;
	//Adds to next avaliable index
	if (treeArray[searchIndex] == nullptr){
		treeArray[searchIndex] = newNode;
	}
	else{
		while (treeArray[searchIndex] != nullptr){
			searchIndex = (searchIndex*2)+1;
			int numOfreps = searchIndex / 2;
			for (int i = numOfreps; i > 0;i--){
				if (treeArray[searchIndex] != nullptr){
					searchIndex--;
				}
				else{
					break;
				}
			}
			if (treeArray[searchIndex] != nullptr){
				searchIndex += numOfreps;
			}
			
		}
		treeArray[searchIndex] = newNode;
	}

	//Sorts the newly added node
	while (searchIndex != 1 and value > treeArray[searchIndex / 2]->getValue()){
		int parentVal = treeArray[searchIndex / 2]->getValue();
		treeArray[searchIndex]->setValue(parentVal);
		treeArray[searchIndex / 2]->setValue(value);
		searchIndex /= 2;
	}
}
void printTree(Node** treeArray){
	for (int i = 0; i < 101;i++){
		if (treeArray[i] != nullptr){
			cout << i << " : " << treeArray[i]->getValue() << endl;
		}
	}
}
