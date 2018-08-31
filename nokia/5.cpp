#include <iostream>

struct TreeNode {
    ~TreeNode() {
        delete leftChild;
        delete rightChild;
    }

    TreeNode * leftChild;
    TreeNode * rightChild;
    int id;
};

TreeNode* generateTree() {
	TreeNode* tree = new TreeNode();

	TreeNode* node0 = tree;
	node0->id = 8;

	node0->leftChild = new TreeNode();
	node0->leftChild->id = 4;
	node0->rightChild = new TreeNode();
	node0->rightChild->id = 10;

	TreeNode* node1L = node0->leftChild;
	node1L->leftChild = new TreeNode();
	node1L->leftChild->id = 2;
	node1L->rightChild = new TreeNode();
	node1L->rightChild->id = 6;

	TreeNode* node2L = node1L->leftChild;
	node2L->leftChild = new TreeNode();
	node2L->leftChild->id = 1;
	node2L->rightChild = new TreeNode();
	node2L->rightChild->id = 3;

	TreeNode* node2R = node1L->leftChild;
	node2R->leftChild = new TreeNode();
	node2R->leftChild->id = 5;
	node2R->rightChild = new TreeNode();
	node2R->rightChild->id = 7;

	return tree;
};

int getHeight(TreeNode* node) {
	if (node == nullptr)
		return 0;
	return 1 + std::max(getHeight(node->leftChild), getHeight(node->rightChild));
}


int main() {
    using namespace std;
    std::string text;

    cout << "Height of tree" << endl;

    TreeNode* tree = generateTree();
    int h = getHeight(tree);
    cout << h << endl;

    delete tree;

    return 0;
}