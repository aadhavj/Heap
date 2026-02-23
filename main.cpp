#include <iostream>
#include <cstring>
#include <fstream>
#include "node.h"
using namespace std;

void addNode(int value, Node** treeArray);
void printTree(Node** treeArray, int lastIndex, int currentIndex, int depth);
int findLastIndex(Node** treeArray);
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
	char addF[] = "ADDF";
	char display[] = "PRINT";
	char quit[] = "QUIT";

	while (runProgram){
		cout << "\nEnter Command(DELETE, DELETEALL, ADD, PRINT, ADDF, QUIT): ";
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
			cout << "Value: " << endl;
			int addedValue;
			cin >> addedValue;
			addNode(addedValue, tree);
		}
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
		else if (strcmp(command, quit) == 0){
			cout << "Quitting..." << endl;
			runProgram = false;
		}
		else if (strcmp(command, display) == 0){
			printTree(tree, findLastIndex(tree),1,0);
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
int findLastIndex(Node** treeArray){
	int lastIndex = 1;
	while (lastIndex < 101 and treeArray[lastIndex] != nullptr){
		lastIndex++;
	}
	return lastIndex;
}
