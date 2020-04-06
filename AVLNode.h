
template <class T>
class AVLNode
{
	template <typename U>
	friend class AVL; //avoid getters for AVL class
private:
	T val;
	int height; //just a single height
	AVLNode<T>* mpRight;
	AVLNode<T>* mpLeft;

public:
	friend std::ostream & operator <<(std::ostream & lhs, AVLNode<T>* & rhs)
	{
		lhs << rhs->val;
		return lhs;
	}
	void setLeft(AVLNode<T>* setLeftNode) //don't remember how to do this, may not work
	{
		this->mpLeft = setLeftNode; 
	}
	void setRight(AVLNode<T>*setRightNode)
	{
		this->mpRight = setRightNode;
	}

	AVLNode<T>(T newData) //default constructor 
	{
		this->val = newData; 
		this->height = 0;
		this->mpLeft = nullptr;
		this->mpRight = nullptr;
	}
	const T getVal()
	{
		return this->val;
	}
	bool removeNode()
	{
		return false;
	}
	AVLNode<T>(AVLNode<T> &newvalcopy) //deep copy constructor //may be an error
	{
		this->val = new T;
		this->val = newvalcopy.val;
		this->height = newvalcopy.height; 
		this->mpLeft = newvalcopy->mpLeft;
		this->mpRight = newvalcopy->mpRight;
	}
	AVLNode<T> * makeNode(T val)
	{
		AVLNode<T>* pNewNode = new AVLNode<T>;
		pNewNode->val = val;
		pNewNode->mpLeft = nullptr;
		pNewNode->mpRight = nullptr;
		pNewNode->heightLeft = 0;
		pNewNode->heightRight = 0; 
		return pNewNode;
	}
};