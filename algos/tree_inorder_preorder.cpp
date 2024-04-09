#include <cstdlib>
#include <deque>
#include <iostream>
#include <queue>
#include <vector>
#include <memory>

struct TreeNode {
	int val;
	std::unique_ptr<TreeNode> left;
	std::unique_ptr<TreeNode> right;

	TreeNode(int x) : val{x}, left{nullptr}, right{nullptr} {}
};

void printTree(const std::unique_ptr<TreeNode>& root) {
	if (!root) {
		return;
	}

	std::queue<const TreeNode*> q;
	q.push(root.get());

	while (!q.empty()) {
		int levelSize = q.size();
		for (int i = 0; i < levelSize; ++i) {
			const auto node = q.front();
			q.pop();

			if (node) {
				std::cout << node->val << ' ';
				q.push(node->left.get());
				q.push(node->right.get());
			} else {
				std::cout << "null ";
			}
		}
		std::cout << '\n';
	}
}

std::unique_ptr<TreeNode> buildTreeHelper(const std::vector<int>& inorder, int inStart, int inEnd,
					  const std::vector<int>& postorder, int posStart, int posEnd) {
	if (inStart > inEnd || posStart > posEnd) {
		return nullptr;
	}

	int rootValue = postorder[posEnd];
	auto rootNode = std::make_unique<TreeNode>(rootValue);

	int rootIndex = inStart;
	while (rootIndex <= inEnd && inorder[rootIndex] != rootValue) {
		rootIndex++;
	}

	int leftSubreeSize = rootIndex - inStart;

	rootNode->left = buildTreeHelper(inorder, inStart, rootIndex - 1, postorder, posStart, posStart + leftSubreeSize - 1);
	rootNode->right = buildTreeHelper(inorder, rootIndex + 1, inEnd, postorder, posStart + leftSubreeSize, posEnd - 1);

	return rootNode;
}

std::unique_ptr<TreeNode> buildTree(const std::vector<int>& inorder, const std::vector<int>& postorder) {
	if (inorder.empty() || postorder.empty() || inorder.size() != postorder.size()) {
		return nullptr;
	}

	return buildTreeHelper(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1);
}

void printInorder(const std::unique_ptr<TreeNode>& root) {
	if (!root) {
		return;
	}
	printInorder(root->left);
	std::cout << root->val << ' ';
	printInorder(root->right);
}

int main() {
	std::vector<int> inorder = { 9, 3, 15, 20, 7 };
	std::vector<int> postorder = { 9, 15, 7, 20, 3 };

	std::unique_ptr<TreeNode> root = buildTree(inorder, postorder);

	printInorder(root);
	std::cout << '\n';

	printTree(root);
	std::cout << '\n';

	return 0;
}
