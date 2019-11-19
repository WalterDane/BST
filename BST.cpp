#include <iostream>
#include<fstream> 
#include<vector>
#include<string>
using namespace std;

class Node
{
public:
	unsigned long long Value;
	unsigned long long index = 1; //Really not index, but "number of right subchildren"
	unsigned long long indexTotal; //Will be in addition to a sum counter
	Node* Left;
	Node* Right;
};

class BinaryTree
{
public:
	// Constructor functions
	BinaryTree();
	~BinaryTree();

	// General binary tree operations
	unsigned long long Search(unsigned long long Value);
	bool Insert(unsigned long long Value);
	void Print();

private:
	// Helper functions
	unsigned long long SearchHelper(unsigned long long Value, Node* Tree, unsigned long long &sumCounter);
	bool InsertHelper(unsigned long long Value, Node*& Tree);
	void PrintHelper(Node* Tree);

	// Tree pointer
	Node* Root;
};

BinaryTree::BinaryTree()
{
	Root = NULL;
}

BinaryTree::~BinaryTree()
{
}

unsigned long long BinaryTree::SearchHelper(unsigned long long Value, Node* Tree, unsigned long long &sumCounter)
{
	// Data value not found 
	if (Tree == NULL)
		return 0;

	// Data value found 
	else if (Tree->Value == Value)
	{
		Tree->indexTotal = sumCounter + Tree->index;
		return Tree->indexTotal;
	}

	// Recursively search for data value
	else if (Tree->Value > Value)
	{
		sumCounter += Tree->index;
		return (SearchHelper(Value, Tree->Left, sumCounter));
	}
	else if (Tree->Value < Value)
	{
		return (SearchHelper(Value, Tree->Right, sumCounter));
	}
}

unsigned long long BinaryTree::Search(unsigned long long Value)
{
	unsigned long long sumCounter = 0;
	// Call tree searching function
	//return (SearchHelper(Value, Root, sumCounter));
	unsigned long long index = SearchHelper(Value, Root, sumCounter);
	return index;
}

bool BinaryTree::InsertHelper(unsigned long long Value, Node*& Tree)
{
	// Insert data into the tree
	if (Tree == NULL)
	{
		Tree = new Node;
		Tree->Value = Value;
		Tree->Left = NULL;
		Tree->Right = NULL;
		return true;
	}

	// Data value already inserted
	else if (Tree->Value == Value)
		return false;

	// Recursively search for insertion position
	else if (Tree->Value > Value)
		return (InsertHelper(Value, Tree->Left));
	else if (Tree->Value < Value)
	{
		Tree->index += 1; //since the value is large, increase the current nodes index. aka "right subchildren"
		return (InsertHelper(Value, Tree->Right));
	}
}

bool BinaryTree::Insert(unsigned long long Value)
{
	// Call tree insertion function
	return (InsertHelper(Value, Root));
}

void BinaryTree::Print()
{
	// Call tree printing function
	PrintHelper(Root);
	cout << endl;
}

void BinaryTree::PrintHelper(Node* Tree)
{
	// Check terminating condition
	if (Tree != NULL)
	{
		// Print left subtree
		PrintHelper(Tree->Left);

		// Print node value
		cout << " " << Tree->Value << " ";

		// Print right subtree
		PrintHelper(Tree->Right);
	}
}

int main()
{
	BinaryTree tree;
	vector<string> searchQueries;
	int q; //number of queries
	cin >> q;
	for (int i = 0; i < q; i++)
	{
		int queryType;
		unsigned long long x;
		cin >> queryType >> x;
		if (queryType == 1) //if query type is 1, insert
			tree.Insert(x);
		else //else, if query type is 2, search
		{
			int k = tree.Search(x);
			if (k == false) //if no value is found
			{
				searchQueries.push_back("Data tidak ada");
			}
			else
				searchQueries.push_back(to_string(k));
		}
	}

	for (int i = 0; i < searchQueries.size(); i++)
	{
		cout << searchQueries[i] << endl;
	}

	return 0;
}