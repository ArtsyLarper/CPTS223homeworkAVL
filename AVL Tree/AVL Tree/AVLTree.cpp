#include "AVLtree.h";


template<typename T>
node<T> * AVLTree<T>::findNode(T input)
{
	while (this->value != input)
	{
		if (this->value < input)
		{
			if (this->leftChild == nullptr)
			{
				return nullptr;
			}
			this = this->leftChild;
		}
		if (this->value>input)
		{
			if (this->rightChild == nullptr)
			{
				return nullptr;
			}
			this = this->rightChild;
		}
	}
	if (this->value == input)
	{
		return this;
	}
	return nullptr;
}

template<typename T>
void inline AVLTree<T>::insert(T input)
{
	if (root == nullptr)
	{
		root = new node;
		root->value = input;
	}
	if (root != nullptr)
	{
		node*temp;
		temp = root;
		while (temp->value != input)
		{
			//temp->height = height + 1;
			if (temp->value > input)  //ADD a comment to remind you where the node goes
			{
				if (temp->rightChild == nullptr)
				{
					temp->rightChild = new node;
					temp = temp->rightChild;
					temp->value = input;
				}
				else
				{
					temp = temp->rightChild;
				}
			}
			if (temp->value < input)
			{
				if (temp->leftChild == nullptr)
				{
					temp->leftChild = new node;
					temp = temp->leftChild;
					temp->value = input;
				}
				else
				{
					temp = temp->leftChild;
				}
			}
		}
		
	}
}

template<typename T>
void inline AVLTree<T>::reportHeight(node<T> *x)
{
	
	if (x->parent == nullptr)
	{
		if (x->balanceFactor < -1)
		{
			leftRotation();
			return;
		}
		if (x->balanceFactor > 1)
		{
			rightRotation();
			return;
		}
		}
		if (x == x->parent->leftChild)
		{
			
			x = x->parent;
			x->leftBranchHeight++;
			x->balanceFactor = (x->rightBranchHeight) - (x->leftBranchHeight);
			if (x->balanceFactor < -1 || x->balanceFactor > 1)
			{
				if (x->balanceFactor < -1)
				{
					leftRotation();
					reportHeight(x);
				}
				if (x->balanceFactor > 1)
				{
					rightRotation();
					reportHeight(x);
				}
			}
			if (x->leftBranchHeight > x->rightBranchHeight)
			{
				if (x->balanceFactor < -1)
				{
					leftRotation();
					reportHeight(x);
				}
				if (x->balanceFactor > 1)
				{
					rightRotation();
					reportHeight(x);
				}
			}
		}
		if (x == x->parent->rightChild)
		{
			x = x->parent;
			x->rightBranchHeight++;
			x->balanceFactor = (x->rightBranchHeight) - (x->leftBranchHeight);
			if (x->balanceFactor < -1 )
			{
				leftRotation();
				reportHeight(x);
			}
			if (x->balanceFactor > 1)
			{
				rightRotation();
				reportHeight(x);
			}
			if (x->leftBranchHeight < x->rightBranchHeight)
			{
				reportHeight(x);
			}
		}
}

template<typename T>
void AVLTree<T>::disintegrate(node<T> * x)
{
	node<T> *temp = x;
	node<T> *temp2;
	node<T> *temp3;
	node<T> *temp4;
	if (temp->parent == nullptr)
	{
		temp2 = temp->leftChild;
		while (temp2->rightChild != nullptr)
		{
			temp2 = temp2->rightChild;
		}
		temp2->rightChild = temp->rightChild;
		temp2->rightChild->parent = temp2;
		temp2->parent->rightChild = nullptr;
		temp2->parent = nullptr;
		if (temp2->leftChild == nullptr)
		{
			temp2->leftChild = temp->leftChild;
			temp2->leftChild->parent = temp2;
			delete temp;
			return;
		}
		temp3 = temp2->leftChild;
		while (temp3->leftChild != nullptr)
		{
			temp3 = temp3->leftChild;
		}
		temp3->leftChild-> = temp->leftChild;
		temp3->leftChild->parent = temp3;
		delete temp;
		return;
	}
	temp2 = temp->parent;
	if (temp->leftChild != nullptr && temp->rightChild != nullptr)
	{
		if (temp->parent->leftChild == temp)
		{
			temp3 = temp->leftChild;
			while (temp->rightChild != nullptr)
			{
				temp3 = temp3->rightChild;
			}
			
			temp3->parent->rightChild = nullptr;
			temp3->parent = temp->parent;
			temp3->rightChild = temp->rightChild;
			temp3->rightChild->parent = temp3;
			if (temp3->leftChild == nullptr)
			{
				temp3->leftChild = temp->leftChild;
				temp3->leftChild->parent = temp3;
				delete temp;
				return;
			}
			temp4 = temp3;
			while (temp4->leftChild != nullptr)
			{
				temp4 = temp4->leftChild;
			}

		}
	}
	if (temp2->leftChild == nullptr)
	{
		temp2->rightChild = temp->rightChild;
		temp->rightChild->parent = temp2;
		delete temp;
	}
	if (temp2->rightChild == nullptr)
	{
		temp2->leftChild = temp->rightChild;
		temp->rightChild->parent = temp2;
		delete temp;
	}
}

template<typename T>
void AVLTree<T>::remove(T input)
{
	node*temp = search(input);
	if (temp->leftChild == nullptr && temp->rightChild == nullptr)
	{
		if (temp == temp->parent->rightChild)
		{
			temp->parent->rightChild = nullptr;
			delete temp;
			return;
		}
		if (temp == temp->parent->leftChild)
		{
			temp->parent->leftChild = nullptr;
			delete temp;
			return;
		}
	}
	disintegrate(temp);
}

template<typename T>
AVLTree<T>::AVLTree()
{
	root = nullptr;
}


template<typename T>
inline node<T>::node()
{
	T value = NULL;
	parent = nullptr;
	rightChild = nullptr;
	leftChild = nullptr;
	balanceFactor = 0;
	leftBranchHeight = 0;
	rightBranchHeight = 0;
}

template <typename T>
node<T>* findPredessor(node<T> *position)
{
	node *temp1;
	node *temp2;
	temp1 = position;
	temp2 = temp1->left;
	while (temp2 != nullptr)
	{
		temp1 = temp2;
		temp2 = temp1->right;
	}
	return temp1;
}

template<typename T>
void inline AVLTree<T>::rightRotation(node<T>*current)
{
	node*pivotPoint;
	node*orbitingPoint;
	pivotPoint = current;

	if (pivotPoint->parent == nullptr)
	{
		orbitingPoint = pivotPoint->left;
		pivotPoint->left = orbitingPoint->right;
		orbitingPoint->right->parent = pivotPoint;
		orbitingPoint->right = pivotPoint;
		pivotPoint->parent = orbitingPoint;
		return;
	}
	if (pivotPoint->left != nullptr&&pivotPoint->right != nullptr)
	{
		if (pivotPoint->parent->parent == nullptr)
		{
			root = pivotPoint;
		}
		orbitingPoint = pivotPoint->parent;
		pivotPoint->parent = orbitingPoint->parent;
		orbitingPoint->left = pivotPoint->right;
		orbitingPoint->parent = pivotPoint;
		pivotPoint->right = orbitingPoint;
		orbitingPoint->left->parent = orbitingPoint;
		return;
	}

}

template<typename T>
void inline AVLTree<T>::leftRotation(node<T> *current)
{
	node*pivotPoint;
	node*orbitingPoint;
	pivotPoint = current;

	if (pivotPoint->parent == nullptr)
	{
		orbitingPoint = pivotPoint->right;
		pivotPoint->right = orbitingPoint->left;
		orbitingPoint->left->parent = pivotPoint;
		orbitingPoint->left = pivotPoint;
		pivotPoint->parent = orbitingPoint;
		return;
	}
	if (pivotPoint->left != nullptr&&pivotPoint->right != nullptr)
	{
		if (pivotPoint->parent->parent == nullptr)
		{
			root = pivotPoint;
		}
		orbitingPoint = pivotPoint->parent;
		pivotPoint->parent = orbitingPoint->parent;
		orbitingPoint->right = pivotPoint->left;
		orbitingPoint->parent = pivotPoint;
		pivotPoint->left = orbitingPoint;
		orbitingPoint->right->parent = orbitingPoint;
		return;
	}

}

