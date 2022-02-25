#pragma once

struct Node
{
	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
	int key = {};
};

class BinarySearchTree
{
public:
	void Print() { Print(mRoot, 10, 0); }
	void Print(Node* node, int x, int y);

	void Print_Preorder() { Print_Preorder(mRoot); }
	void Print_Preorder(Node* node);

	void Print_Inorder() { Print_Inorder(mRoot); }
	void Print_Inorder(Node* node);

	void Print_Postorder() { Print_Postorder(mRoot); }
	void Print_Postorder(Node* node);

	Node* Search(Node* node, int key);
	Node* Search2(Node* node, int key);

	Node* Min(Node* node);
	Node* Max(Node* node);
	Node* Next(Node* node);

	void Insert(int key);

	void Delete(int key);
	void Delete(Node* node);

	void Replace(Node* u, Node* v);

private:
	Node* mRoot = nullptr;
};

