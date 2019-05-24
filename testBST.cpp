// Description: Assignment 14 - BST 
// Author: Katherine-Marie Gonzales
// COMSC200 - 5001
// May 23, 2019
// Status: Not sure if tests are correct, frac and FeetInches Included

//testBST.cpp

#include <bits/stdc++.h> 
#include "Frac.h"
#include "FeetInches.h"
#include <string>
using namespace std;


template<class T>
class BST {
    
    struct Node{
public:
	T data;
	Node *left, *right;
	Node(T data){
		this->data = data;
		left = right = nullptr;
	}
};
    Node *root;	
    void display(Node *root);
    bool travInOrder(Node *root, vector<T> &record);
    void printInOrder(const Node *p, string lpad, string rpad) const;
public:
	BST(){ root = nullptr; }
	bool find(T id);
	bool remove(T id);
	Node *getSuccessor(Node* target) const;
	void insert(T id);
	void display() { display(root); }
	void printInOrder () const { printInOrder(root, " ", " "); }
	bool travInOrder(vector<T> &record ) {
	    travInOrder(root, record );
	}
};

template<class T>
bool BST<T>::find(T id) {
	Node *current = root;
	while(current) {
		if(current->data > id) { current = current->left; }
		else if(current->data < id) { current = current->right; }
		else { return true; }
	}
	return false;
}

template<class T>
bool BST<T>::remove(T id) {
	Node *parent = root;
	Node *current = root;
	bool isLeftChild = false;
	while(current->data!=id) {
		parent = current;
		if(current->data > id) {
			isLeftChild = true;
			current = current->left;
		}
		else {
			isLeftChild = false;
			current = current->right;
		}
		if( !current ) return false; 
	}
	//if i am here that means we have found the node
	//Case 1: if node to be removed has no children
	if(!current->left && !current->right){
		if(current==root) { root = nullptr; }
		if(isLeftChild){ parent->left = nullptr; }
		else { parent->right = nullptr; }
	}
	//Case 2 : if node to be removed has only one child
	else if(current->right==nullptr){
		if(current==root){ root = current->left; }
		else if(isLeftChild) { parent->left = current->left; }
		else{ parent->right = current->left; }
	}
	else if(current->left==nullptr){
		if(current==root){ root = current->right; }
		else if(isLeftChild){ parent->left = current->right; }
		else{ parent->right = current->right; }
	}else {// i.e. if( current->left && current->right){
		//now we are to find the minimum left on the right sub tree
		Node *successor = getSuccessor(current);
		if(current==root){ root = successor; }
		else if(isLeftChild){ parent->left = successor; }
		else{ parent->right = successor; }			
		successor->left = current->left;
	}		
	return true;		
}

template<class T>
typename BST<T>::Node* BST<T>::getSuccessor(Node* target) const {
	Node *successsor = nullptr;
	Node *successsorParent = nullptr;
	Node *current = target->right;
	while(current) {
		successsorParent = successsor;
		successsor = current;
		current = current->left;
	}
	//check if successor has the right child, it cannot have left child for sure
	// if it does have the right child, add it to the left of successorParent.
	if(successsor != target->right) {
		successsorParent->left = successsor->right;
		successsor->right = target->right;
	}
	return successsor;
}

template<class T>
void BST<T>::insert(T id){
	Node *newNode = new Node(id);
	if(!root){ root = newNode; return;}
	Node *current = root;
	Node *parent = nullptr;
	while(true){
		parent = current;
		if(id<current->data){				
			current = current->left;
			if(!current){
				parent->left = newNode;
				return;
			}
		}
		else{
			current = current->right;
			if(!current){
				parent->right = newNode;
				return;
			}
		}
	}
}

// traversal only version
//
// void BST::display(Node *root){
// 	if(root){
// 		display(root->left);
// 		cout << " " << root->data;
// 		display(root->right);
// 	}
// }

// the cash-back (call-back) version
//
template<class T>
void BST<T>::display(Node *root) {
    vector<T> record;
    travInOrder(record);
    for( auto x:record )
        cout << x << " ";
}

template<class T>
bool BST<T>::travInOrder(Node *p, vector<T> &record){
	if (p){
	    if(p->left) travInOrder(p->left, record);
		record.push_back(p->data);
		if(p->right) travInOrder(p->right, record);
	}
	return true;
}

template<class T>
void BST<T>::printInOrder(const Node *p, string lpad, string rpad) const {
    string pad = lpad.substr(0, lpad.size() - 1);
    if (p == nullptr)	return;
    printInOrder(p->right, rpad + "    |", rpad + "     ");
    cout << pad << "+--" << setw(3) << p->data << endl;
    printInOrder(p->left, lpad + "     ", lpad + "    |");
}
    
    
template<class T> void test(vector<T> list);

int main() {
    vector<int> intPattern {3,8,1,4,6,25,15,16};
    test(intPattern);

    vector<string> strPattern {
        "how", "many", "apples", "did", "you", "buy"};
    test(strPattern);
    
    vector<FeetInches> feetInchesPattern {
        (4,9),(3,8),(5,2)
    };
    test(feetInchesPattern);
    
    vector<Frac> fracPattern {(10/5), (12/4), (5/1)};
    test(fracPattern);
}

// test Driver
template<class T>
void test(vector<T> list) {
    BST<T> *b = new BST<T>;
    
    cout << "Insertion sequence for new tree: \n   ";
    bool first = true;
    for(auto x:list) {
        b->insert(x);
        if(first) first = false;
        else cout << ", ";
        cout << x;
    }

    cout << "\n Listing Tree nodes in order: \n   ";
    b->display();		
    cout << "\n Show the Original Tree diagram:\n";
    b->printInOrder();
    cout << "\n Check whether last inserted Node, (" 
    << list[list.size()-1] << ") exists? " 
    << ( (b->find(list[list.size()-1]))?"YES":"NO" ) 
    << "\n Remove fist inserted Node\n   ";
    b->display();
    cout << "\n Show the final result in Diagram:\n";
    b->printInOrder();
}