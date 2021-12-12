#include <bits/stdc++.h> 
using namespace std; 

class Node
{
public:
	int value, height;
	Node *left;
	Node *right;
	Node(int val, int hei); // Constructor	
};

Node::Node (int val, int hei)
{
	value = val;
	height = hei; 
	left = NULL;
	right = NULL;
}

Node *root = NULL;

void inOrder(Node *tmp)
{
	if (tmp != NULL)
	{
		inOrder(tmp->left);
		cout << tmp->value << " " /*<< "(h=" << tmp->height << ") "*/;
		inOrder(tmp->right);
	}
}

void preOrder(Node *tmp)
{
	if (tmp != NULL)
	{		
		cout << tmp->value << " " /* << "(h=" << tmp->height << ") "*/;
		preOrder(tmp->left);
		preOrder(tmp->right);
	}
}

void postOrder(Node *tmp)
{
	if (tmp != NULL)
	{				
		postOrder(tmp->left);
		postOrder(tmp->right);
		cout << tmp->value << " " /*<< "(h=" << tmp->height << ") "*/;
	}
}


int nodeHeight(Node *node)
{
	if (node == NULL)
	{
		return 0;
	}
	else
	{
		return node->height;
	}
}


Node *leftRotate(Node *node)
{
	Node *oriRight = node->right;
	Node *tmp = oriRight->left; 
	
	// Rotate
	oriRight->left = node;
	node->right = tmp;

	// Update heights
	node->height = max(nodeHeight(node->left), nodeHeight(node->right)) + 1;
	oriRight->height = max(nodeHeight(oriRight->left), nodeHeight(oriRight->right)) + 1;

	return oriRight;
}

Node *rightRotate(Node *node)
{
	Node *oriLeft = node->left;
	Node *tmp = oriLeft->right;

	// Rotate
	oriLeft->right = node;
	node->left = tmp;

	// Update heights
	node->height = max(nodeHeight(node->left), nodeHeight(node->right)) + 1;
	oriLeft->height = max(nodeHeight(oriLeft->left), nodeHeight(oriLeft->right)) + 1;

	return oriLeft;
}


Node* insert(Node* tmpNode, int val)
{
	// Add node
	// if empty
	if (tmpNode == NULL)
	{
		return(new Node(val, 1));
	}
	// if not empty
	if (val < tmpNode->value) // add to left
	{
		tmpNode->left = insert(tmpNode->left, val);
	}
	else if (val > tmpNode->value) // add to right
	{
		tmpNode->right = insert(tmpNode->right, val);
	}
	else // do nothing if already in tree
	{
		return tmpNode;
	}

	// Update height
	tmpNode->height = max(nodeHeight(tmpNode->left), nodeHeight(tmpNode->right)) + 1;

	// Check balance
	int bal = nodeHeight(tmpNode->left) - nodeHeight(tmpNode->right);
/*	// Test:
	cout << "bal = " << bal << endl;
	cout << "Before rotate: "; 
	postOrder(root);
	cout << endl;*/

	// Rebalance if bal != {-1, 0, 1}
	if (bal > 1)
	{
		if (val < tmpNode->left->value)
		{
			return rightRotate(tmpNode);
		}		
		else if (val > tmpNode->left->value)
		{
			tmpNode->left = leftRotate(tmpNode->left);
			return rightRotate(tmpNode);
		}
	}

	if (bal < -1)
	{
		if (val > tmpNode->right->value)
		{
			return leftRotate(tmpNode);
		}		
		else if (val < tmpNode->right->value)
		{
			tmpNode->right = rightRotate(tmpNode->right);
			return leftRotate(tmpNode);
		}
	}

	return tmpNode;
}


Node *maxNode(Node *node)
{
	Node *tmp = node;

	while (tmp->right != NULL)
	{
		tmp = tmp->right;
	}

	return tmp;
}

Node *remove(Node *subRoot, int val)
{

	if (subRoot == NULL)
	{
		return subRoot;
	}

	if (val < subRoot->value) // remove left side
	{
		subRoot->left = remove(subRoot->left, val);
	}
	else if (val > subRoot->value) // remove right side
	{
		subRoot->right = remove(subRoot->right, val);
	}
	else // remove root
	{
		// if less than 2 children
		if ((subRoot->left == NULL) || (subRoot->right == NULL))
		{
			Node *tmp = NULL;
			if (subRoot->left != NULL)
			{
				tmp = subRoot->left;
			}
			else if (subRoot->right != NULL)
			{
				tmp = subRoot->right;
			}
			// if 0 child
			if (tmp == NULL)
			{
				tmp = subRoot;
				subRoot = NULL;
			}
			// if 1 child
			else
			{
				*subRoot = *tmp;
			}
			free(tmp);
		}
		// if 2 children
		else
		{
			Node *tmp = maxNode(subRoot->left);
			subRoot->value = tmp->value;
			subRoot->left = remove(subRoot->left, tmp->value);			
		}		
	}

	// if tree has only 1 node
	if (subRoot == NULL)
	{
		return subRoot;
	}

	// Update height
	subRoot->height = max(nodeHeight(subRoot->left), nodeHeight(subRoot->right)) + 1;

	// ChecK balance
	int bal = nodeHeight(subRoot->left) - nodeHeight(subRoot->right);
	int balL = 0;
	int balR = 0;

	if (subRoot->left != NULL)
	{
		balL = nodeHeight(subRoot->left->left) - nodeHeight(subRoot->left->right);
	}

	if (subRoot->right != NULL)
	{
		balR = nodeHeight(subRoot->right->left) - nodeHeight(subRoot->right->right);
	}

	// Rebalance if bal != {-1, 0, 1}
	if (bal < -1)
	{
		if (balR > 0)
		{
			subRoot->right = rightRotate(subRoot->right);
			return leftRotate(subRoot);
		}
		else
		{
			return leftRotate(subRoot);
		}
	}
	if (bal > 1)
	{
		if (balL < 0)
		{
			subRoot->left = leftRotate(subRoot->left);
			return rightRotate(subRoot);
		}
		else
		{
			return rightRotate(subRoot);
		}
	}

	return subRoot;
}


int main(int argc, char const *argv[])
{
	
	vector<string> moves;
	vector<string> modifications;
	vector<int> values;
	string line, tmpMove, tmpMod;
	int tmpVal;
	getline(cin, line);
	stringstream ss(line);

	while (ss >> tmpMove) 
	{
		moves.push_back(tmpMove);
	}

/*	// Test:
	for (int i = 0; i < moves.size(); ++i)
	{
		cout << moves[i] << " ";
	}
	cout << endl;*/

	for (int i = 0; i < moves.size() - 1; ++i)
	{
		tmpMod = moves[i].substr(0, 1);
		modifications.push_back(tmpMod);
		moves[i].erase(0, 1);
		istringstream iss(moves[i]);
		iss >> tmpVal;
		values.push_back(tmpVal);
	}

	for (int i = 0; i < values.size(); ++i)
	{
		if (modifications[i].compare("A") == 0)
		{
			//cout << "----------\n";
			//cout << "add " << values[i] << ":\n";
			root = insert(root, values[i]);
			//postOrder(root);
			//cout << endl;
		}
		else if (modifications[i].compare("D") == 0)
		{
			//cout << "----------\n";
			//cout << "delete " << values[i] << ":\n";
			root = remove(root, values[i]);
			//postOrder(root);
			//cout << endl;
		}		
	}

	if (root == NULL)
	{
		cout << "EMPTY\n";
	}
	else
	{
		if (moves[moves.size() - 1] == "PRE")
		{
			preOrder(root);
		}
		else if (moves[moves.size() - 1]  == "POST")
		{
			postOrder(root);
		}
		else if (moves[moves.size() - 1]  == "IN")
		{
			inOrder(root);
		}
		cout << endl;
	}

	return 0;
}