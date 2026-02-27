//Include modules
#include <iostream>
#include <cstring>
#include <fstream>
#include "node.h"
using namespace std;

//Function prototypes
void addNode(int value, Node** treeArray);
void printTree(Node** treeArray, int lastIndex, int currentIndex, int depth);
int findLastIndex(Node** treeArray);
void swap(Node** treeArray, int firstIndex, int secondIndex);
void Delete(Node** treeArray, int searchIndex);
void DeleteAll(Node** treeArray);

int main(){

	//Basic var instantiation
	char command[1000];
	Node** tree = new Node*[101];
	bool runProgram = true;
	for (int i = 0; i < 101;i++){
		tree[i] = nullptr;
	}

	//Valid Command prompts
	char del[] = "DELETE";
	char delAll[] = "DELETEALL";
	char add[] = "ADD";
	char addF[] = "ADDF";
	char display[] = "PRINT";
	char quit[] = "QUIT";

	while (runProgram){
		cout << "\nEnter Command(DELETE, DELETEALL, ADD, PRINT, ADDF, QUIT): ";
		cin >> command;
		command[9] = '\0';

		//Command recognition
		if (strcmp(command, del) == 0){
			if (tree[1] != nullptr){
				//outputs root to standard output
				cout << tree[1]->getValue();

				//deletes unneccessary allocated memory
				delete tree[1];

				//Find length of array, just counting non-null pointers
				int lastIndex = findLastIndex(tree);
			
				//Not root
				if (lastIndex != 1){
					tree[1] = tree[lastIndex-1];
					tree[lastIndex-1] = nullptr;
					Delete(tree, 1);
				}
				else{
					tree[1] = nullptr;
				}
			}
			else{
				cout << "Nothing to delete" << endl;
			}

		}
		//Deletes all nodes in tree
		else if (strcmp(command, delAll) == 0){
			DeleteAll(tree);
		}
		//Adds individual node
		else if (strcmp(command, add) == 0){
			cout << "Value: " << endl;
			int addedValue;
			cin >> addedValue;
			addNode(addedValue, tree);
		}
		//Adds input from formatted file
		else if (strcmp(command, addF) == 0){

			char fileName[100];
			cout << "Enter file name (include .txt): ";
			cin >> fileName;

			ifstream numFile(fileName);

			if (!numFile) {
				cout << "Invalid file name." << endl;
			}
			else{
				int number;
				while (numFile >> number) {
					addNode(number, tree);
				}
				numFile.close();
			}
		}
		//Quits out of loop
		else if (strcmp(command, quit) == 0){
			cout << "Quitting..." << endl;
			runProgram = false;
		}
		//Prints the tree
		else if (strcmp(command, display) == 0){
			printTree(tree, findLastIndex(tree),1,0);
		}
		//Occurs for invalid command prompts
		else{
			cout << "Command prompt unrecognized" << endl;
		}
	}

	//Cleans up all remaining node objects
	for (int i = 0;i<101;i++){
		delete tree[i];
	}

	return 0;
}

//Adds node and sorts it into array
void addNode(int value, Node** treeArray){
	Node *newNode = new Node(value);
	int searchIndex = 1;
	//Adds to next avaliable index
	if (treeArray[searchIndex] == nullptr){
		treeArray[searchIndex] = newNode;
	}
	else{
		searchIndex = 1;
		while (treeArray[searchIndex] != nullptr){
			searchIndex++;
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
//Print function -> credit to Mr. Galbraith for the code
void printTree(Node** treeArray, int lastIndex, int currentIndex, int depth){
	if ((currentIndex *2) + 1 < lastIndex){
		printTree(treeArray, lastIndex, (currentIndex*2)+1, depth+1);
	}
	for (int i = 0;i<depth;i++){
		cout << "\t";
	}
	if (treeArray[currentIndex] != nullptr){
		cout << treeArray[currentIndex]->getValue() << endl;
	}
	if ((currentIndex*2) < lastIndex){
		printTree(treeArray, lastIndex, currentIndex*2, depth+1);
	}
}
//Finds the last index in the tree array
int findLastIndex(Node** treeArray){
	int lastIndex = 1;
	while (lastIndex < 101 and treeArray[lastIndex] != nullptr){
		lastIndex++;
	}
	return lastIndex;
}
//Swaps two nodes given index location in treeArray
void swap(Node** treeArray, int firstIndex, int secondIndex){
	Node* temp = treeArray[firstIndex];
	treeArray[firstIndex] = treeArray[secondIndex];
	treeArray[secondIndex] = temp;
}
//Deletes root and resorts array
void Delete(Node** treeArray, int searchIndex){

	//Left and right nodes
	Node* left = treeArray[searchIndex*2];
	Node* right = treeArray[(searchIndex*2)+1];

	//Does each case and swaps neccessary nodes, and recursively calls Delete
	if (left != nullptr){
		if (right == nullptr){
			if (left->getValue() > treeArray[searchIndex]->getValue()){
				swap(treeArray, searchIndex, searchIndex*2);
			}
		}
		else{
			if (left->getValue() > treeArray[searchIndex]->getValue() or right->getValue() > treeArray[searchIndex]->getValue()){
				if (left->getValue() > right->getValue()){
					swap(treeArray, searchIndex, searchIndex*2);
					Delete(treeArray, searchIndex*2);
				}
				else{
					swap(treeArray, searchIndex, (searchIndex*2)+1);
					Delete(treeArray, (searchIndex*2)+1);
				}
			}
		}
	}
}
//Deletes all nodes
void DeleteAll(Node** treeArray){
	while (treeArray[1] != nullptr){
		//outputs root to standard output
		cout << treeArray[1]->getValue() << " ";

		//deletes unneccessary allocated memory
		delete treeArray[1];

		//Find length of array, just counting non-null pointers
		int lastIndex = findLastIndex(treeArray);

		//Not root
		if (lastIndex != 1){
			treeArray[1] = treeArray[lastIndex-1];
			treeArray[lastIndex-1] = nullptr;
			Delete(treeArray, 1);
		}
		else{
			treeArray[1] = nullptr;
		}
	}
}

