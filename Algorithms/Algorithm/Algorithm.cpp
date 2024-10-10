#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

using NodeRef = shared_ptr<struct Node>;

struct Node
{
	Node() {}
	Node(const string& data) : data(data){}
	std::string data;
	vector<NodeRef> children;
	bool visted = false;
};

NodeRef CreateTree()
{
	NodeRef root = make_shared<Node>("R1 개발실");
	{
		NodeRef node = make_shared<Node>("디자인팀");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("전투");
			node->children.push_back(leaf);
		}

		{
			NodeRef leaf = make_shared<Node>("경제");
			node->children.push_back(leaf);
		}

		{
			NodeRef leaf = make_shared<Node>("스토리");
			node->children.push_back(leaf);
		}

		node = make_shared<Node>("프로그래밍팀");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("서버");
			node->children.push_back(leaf);
		}

		{
			NodeRef leaf = make_shared<Node>("클라");
			node->children.push_back(leaf);
		}

		{
			NodeRef leaf = make_shared<Node>("엔진");
			node->children.push_back(leaf);
		}

		node = make_shared<Node>("아트");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("배경");
			node->children.push_back(leaf);
		}

		{
			NodeRef leaf = make_shared<Node>("케릭터");
			node->children.push_back(leaf);
		}

		{
			NodeRef leaf = make_shared<Node>("스토리");
			node->children.push_back(leaf);
		}
	}
	return root;
}

void PrintTree(NodeRef root,int depth)
{
	for (int i = 0; i < depth; i++)
		cout << "-";
	cout << root->data << '\n';

	for (NodeRef& child : root->children)
		PrintTree(child, depth +1);
}

int GetHeight(NodeRef root)
{
	int height = 1;
	
	for (NodeRef& child : root->children)
	{
		height = GetHeight(child) + 1;

		cout << height << '\n';
	}

	return height;
}

int main()
{
	NodeRef parent = CreateTree();
	PrintTree(parent,0);
	GetHeight(parent);
	return 0;
}