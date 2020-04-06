#include <queue>

#include <iostream>
#include <cstdlib>
#include <queue>
#include "AVLNode.h"



template <class T> 
class AVL
{
	template <typename U>
	friend class AVLNode;  //friend class AVLNode<T> declares it as a class and ruins that class later on
public:
	//copy assignment/constructor, move assignment/constructor, destructor, insert (includes rotate)
	AVL<T>()
	{
		mproot = nullptr;
		std::cout << "made a tree\n";
	}
	const AVLNode<T>* getRoot()
	{
		return mproot;
	}

	void insert(T newData)
	{
		if (this->mproot != nullptr) //tree not empty, insert
		{
			insertHelper(mproot, newData);
		}
		else 
		{ 
			this->mproot = new AVLNode<T>(newData); //amibguous call to overloaded function
		} //make a new Node and say root is equal to it 
	}

	void remove(T num)
	{
		privateRemove(mproot, num); 
	}

	void printInOrder()
	{
		if (mproot == nullptr)
			std::cout << "tree is empty\n";
		else printinOrderHelper(mproot);
	}
	void isEmpty()
	{
		return mproot == nullptr;
	}

	void levelOrderPrint() //work on this after math
	{
		std::queue<AVLNode<T>*> q;
		AVLNode<T> * pCur = nullptr;
		if (mproot != nullptr)
		{
			q.push(mproot);
			while (q.size() != 0)
			{
				pCur = q.front();
				std::cout << pCur->val << std::endl;

				if (pCur->mpRight!=nullptr){
					q.push(pCur->mpLeft);
				}
				if (pCur->mpLeft!=nullptr){
					q.push(pCur->mpRight);
				}
				
				q.pop();
			}
			
		}
	}
	void printinOrderHelper(AVLNode<T>* root) //left, process, right
	{
		//base case, nold == null; return;
		if (root == nullptr)
			return;
		else if (root->mpLeft != nullptr)
		{
			printinOrderHelper(root->mpLeft);
		}
		std::cout << root->getVal()<<"  ht "<< root->height <<std::endl;
		if (root->mpRight != nullptr)
		{
			printinOrderHelper(root->mpRight);
		}	
	}
	T findMax()
	{
		if(mproot != nullptr)
		{
			return PrivateFindMax(mproot)->getVal();
		}
		
	}

	T findMin()
	{
		if(mproot != nullptr)
		{
			return PrivateFindMin(mproot)->getVal();
		}
	}

private:

	AVLNode<T> * mproot; 
	AVLNode<T>* PrivateFindMin(AVLNode<T>* subTree) //returns pointer to smallest, doesn't need to be recursive
	{
		AVLNode<T> * pCur = subTree;
		if(pCur != nullptr)
		{
			while (pCur->mpLeft != nullptr)
			{
				pCur = pCur->mpLeft;
			}
		}
		return pCur;
	}
	AVLNode<T>* PrivateFindMax(AVLNode<T>* subTree) //want it to work on a subtree, subTree didn't get passed in
	{
		AVLNode<T> * pCur = subTree;

		if (subTree != nullptr) {
			while (pCur->mpRight != nullptr)
			{
				pCur = pCur->mpRight;
			}
			//return pCur;
		}
		return pCur;
	}
	void privateRemove(AVLNode<T>* & root, T num) //cases; 0. tree empty 1. not found 2. no children 3. one child 4. two children
	{
		//forst find the spot to remove
		if (root == nullptr) //not found, go back
		{
			std::cout << num << " not found " << std::endl;
			return;
		}
		if (root -> val > num) //traverse right
		{
			privateRemove(root->mpLeft, num);
		}
		else if (root->val < num)
		{
			privateRemove(root ->mpRight, num); //traverse left
		}
		else if (root -> val == num) //found
		{
			//if no children:
			if (root ->mpLeft == nullptr && root -> mpRight == nullptr)
			{
				delete root; //is this all to do this
				root = nullptr;
			}

			//if one left child:
			else if (root->mpLeft != nullptr && root ->mpRight == nullptr) //need copy assignment operator(?)
			{
				AVLNode<T>* temp = root;
				root = root->mpLeft;
				delete temp;
			}
			//if one right child:
			else if (root->mpRight != nullptr && root->mpLeft == nullptr) //need copy assignment operator
			{
				AVLNode<T>* temp = root;
				
				root = root->mpRight;
				delete temp;
			}
			//if two children:
			//replace the node with the smallest of the right side or biggest on left side, call remove on num again
			else if (root ->mpLeft != nullptr && root ->mpRight != nullptr) //another copy assignment 
			{
				root = PrivateFindMax(root->mpRight); //only called by AVL, not node
				privateRemove(root, root ->val);
			}
		}
			balance(root); //should be allowed to pass in nullptr becasue this function will take care of it 
		
	}
	void insertHelper(AVLNode<T>* &root, T data) //one you pass in the root to and it inserts 
	{
		//T curVal = root->getVal();// = 
		if (data < root ->getVal()) //reference can only referto l value
		{
			if (root ->mpLeft == nullptr) //insert left
			{
				root->mpLeft = new AVLNode<T>(data); //inserts it 
			//	root->heightLeft++;
			}
			else {
				insertHelper(root->mpLeft, data);
				//root->heightLeft++; //adjust the height at the end
			}
		}
		else if (data> root->getVal()) 
		{
			if (root ->mpRight == nullptr) //insert right
			{
				//root->setRight(AVLNode<T>(data)); //may not work
				root->mpRight = new AVLNode<T>(data);
			//	root->heightRight++;
			}
			else
			insertHelper(root->mpRight, data);
			//root->heightRight++; //inc height after we go through it
		}
		else if (data == root->getVal()) {}; //it is a duplicate and skip

		balance(root);
	}

	void balance( AVLNode<T> * &root) //would check each node going down the call stakc after inserting new number
	{
		//LL-> R
		//RR-> L
		//RL->LR
		//LR->LR
		if(root == nullptr)
		{
			return;
		}
		//learn your LEFT and RIGHTSDKJFFDJGLKG
			if (getHeight(root->mpLeft) - getHeight(root->mpRight)>=2) // LL or LR insert
			{
				if (getHeight(root->mpLeft->mpLeft) >= getHeight(root->mpLeft->mpRight)) // LL insert //BREAKS 
				{
					rightRotate(root);
				}
				else //if (getHeight(root->mpLeft->mpLeft) < getHeight(root->mpLeft->mpRight)) //LR insert
				{
					//LR rotate
					leftRotate(root->mpRight);
					rightRotate(root);
				}
			}//end if getHeight()
			else if (getHeight(root->mpRight)- getHeight(root->mpLeft)>=2)//LL or LR insert
			{
				if (getHeight(root->mpRight->mpRight) >= getHeight(root->mpRight->mpLeft)) //RR insert
				{
					leftRotate(root);
				}
				else //if (getHeight(root->mpRight->mpRight)<getHeight(root->mpRight->mpLeft)) //RL insert
				{
					//RL rotate
					rightRotate(root->mpLeft); //STOLEN FROM BOOK
					leftRotate(root);
				}
			}//end second if getHeight()

		// adjust height at the end of the rotate
		root->height = std::max(getHeight(root->mpLeft), getHeight( root->mpRight)) +1; 

	}
	void rightRotate(AVLNode<T>*& root) //LL insert
	{
		AVLNode<T>* pTemp = root->mpLeft;
		root->mpLeft = pTemp->mpRight; //pTemp was nullptr //BERAKS
		pTemp->mpRight = root;
		
		root->height = std::max(getHeight(root->mpLeft), getHeight(root->mpRight)) + 1;
		pTemp->height = std::max(getHeight(pTemp->mpLeft), getHeight(pTemp->mpRight)) + 1; //error
		root = pTemp;

	}
	void leftRotate(AVLNode<T>*& root) // RR insert
	{
		AVLNode<T>* pTemp = root->mpRight;
		root->mpRight = pTemp->mpLeft; //pTemp was nullptr 
		pTemp->mpLeft = root;
	
		root->height = std::max(getHeight(root->mpLeft), getHeight(root->mpRight))+1;
		pTemp->height= std::max(getHeight(pTemp->mpLeft), getHeight(pTemp->mpRight))+1; //error
		root = pTemp;

	}

	int getHeight(AVLNode<T> *child) //because if you don't have this function, you can't get the height of a null subtree
	{
		return child == nullptr ? -1 : child->height; //cond , if true ? ,  if false :
	}
};
/////////////////////////////////////////////////////////////////////
// super sophisticated tests I would normally do in main 

void testNodeConstructor()
{
	AVLNode<int> a(4);
	std::cout << a.getVal()<<std::endl;
	AVLNode<int> b(12);
	std::cout << b.getVal()<<std::endl;

}

void testAVLConstructor(void)
{
	AVL<int> a;
}
void testInsert(void)
{
	AVL<int> t;
	t.insert(1);
	t.insert(2);
	t.insert(3);
	t.insert(4);
	t.insert(-1);
	t.insert(-2);
	t.insert(-3);
	t.insert(-4);
	t.printInOrder();
}
void testLeftRotate(void) //test didn't work 
{
	AVL<int> t;
	/*insert 3 to the right of a right subtree calls for a left rotate*/
	t.insert(1);
	t.insert(2);
	t.insert(3); //rotate is inside of insert 
	t.printInOrder();
	//t.leftRotate((t.getRoot()));
}
void testLevelOrderPrint(void)
{
	AVL<int> t;
	std::queue<int> q;
	t.insert(4);
	t.insert(2);
	t.insert(6);
	t.insert(1);
	t.insert(3);
	t.insert(5);
	t.insert(7);

	t.levelOrderPrint();
}

void testHeights(void)
{
	AVL<int>t3;
	std::cout << "inserting 0\n";
	t3.insert(0);

	std::cout << "inserting -50\n";
	t3.insert(-50);

	std::cout << "inserting 50\n";
	t3.insert(50);

	std::cout << "inserting -70\n";
	t3.insert(-70);

	std::cout << "inserting -20\n";
	t3.insert(-20);

	std::cout << "inserting 10\n";
	t3.insert(10);

	std::cout << "inserting 100\n";
	t3.insert(100);
	std::cout << "inserting 8\n";
	t3.insert(8);
	std::cout << "inserting 15\n";
	t3.insert(15);
	std::cout << "inserting 16\n";
	t3.insert(16);

	t3.printInOrder();

}
void testRemove(void)
{
	AVL<int> t;
	t.remove(3);
	/*t.insert(5);
	t.insert(2);
	t.insert(10);
	t.remove(10);
	t.remove(12);*/
	t.printInOrder();
	//std::cout << t.findMax();
}
void testMinAndMax(void)
{
	AVL<int> t;
	std::cout<<"min: "<<t.findMin()<<std::endl;
	std::cout<<"max: "<<t.findMax()<<std::endl; //should output some garbage 
	t.insert(3);
	t.insert(1);
	t.insert(9);
	std::cout<<"min: "<<t.findMin()<<std::endl;
	std::cout<<"max: "<<t.findMax()<<std::endl;
}