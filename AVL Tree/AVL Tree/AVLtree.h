#pragma once
#include <iostream>
#include <math.h>
using namespace std;


template <typename T>
class node
{
	T value;
	node*parent;
	node*rightChild;
	node*leftChild;
	int balanceFactor;
	int leftBranchHeight;
	int rightBranchHeight;
	node();

};

template <typename T>
class AVLTree
{
private:
	node*root;
	node*findNode(T input);
	void balancetree(node*x);
	void leftRotation(node*x);
	void rightRotation(node*x);
	void insert(T input);
	void reportHeight(node *x);
	void disintegrate(node *x);
public:
	void remove(T input);
	void search(T input);
	AVLTree();
};
