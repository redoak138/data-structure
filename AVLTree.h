#ifndef AVLTREE_H
#define AVLTREE_H

template<typename Type>
struct Node {
	Node(Type);
	Type key;
	int height;
	Node *left, *right;
};

template<typename Type>
class AVLTree {
public:
	AVLTree();
	void insert(Type);
	void erase(Type);
	bool find(Type);
	bool empty();
	int height();
	size_t size();
	~AVLTree();
private:
	Node<Type>* root;
	size_t treeSize;
};

template<typename Type>
AVLTree<Type>::AVLTree() : root(nullptr), treeSize(0) {}

template<typename Type>
void AVLTree<Type>::insert(Type value) {
	root = insertNode(root, value);
	++treeSize;
}

template<typename Type>
void AVLTree<Type>::erase(Type value) {
	if (findNode(root, value)) {
		root = eraseNode(root, value);
		--treeSize;
	}
}

template<typename Type>
bool AVLTree<Type>::find(Type value) {
	return findNode(root, value);
}

template<typename Type>
bool AVLTree<Type>::empty() {
	return emptyNode(root);
}

template<typename Type>
int AVLTree<Type>::height() {
	return heightNode(root);
}

template<typename Type>
size_t AVLTree<Type>::size() {
	return treeSize;
}

template<typename Type>
AVLTree<Type>::~AVLTree() {
	destroyTree(root);
	root = nullptr;
	treeSize = 0;
}

// Node structure methods

template<typename Type>
Node<Type>::Node(Type value) : key(value), left(nullptr), right(nullptr), height(1) {}

template<typename Type>
bool emptyNode(Node<Type>* node) {
	return (node == nullptr);
}

template<typename Type>
int heightNode(Node<Type>* node) {
	return emptyNode(node) ? 0 : node->height;
}

template<typename Type>
int diffHeight(Node<Type>* node) {
	return heightNode(node->right) - heightNode(node->left);
}

template<typename Type>
void updateHeight(Node<Type>* node) {
	int leftHeight = heightNode(node->left);
	int rightHeight = heightNode(node->right);
	node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

template<typename Type>
Node<Type>* leftRotate(Node<Type>* node) {
	Node<Type>* tmpNode = node->right;
	node->right = tmpNode->left;
	tmpNode->left = node;
	updateHeight(node);
	updateHeight(tmpNode);
	return tmpNode;
}

template<typename Type>
Node<Type>* rightRotate(Node<Type>* node) {
	Node<Type>* tmpNode = node->left;
	node->left = tmpNode->right;
	tmpNode->right = node;
	updateHeight(node);
	updateHeight(tmpNode);
	return tmpNode;
}

template<typename Type>
Node<Type>* balanceNode(Node<Type>* node) {
	int diff = diffHeight(node);
	if (diff == 2) {
		if (diffHeight(node->right) < 0)
			node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	if (diff == -2) {
		if (diffHeight(node->left) > 0)
			node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	return node;
}

template<typename Type>
Node<Type>* insertNode(Node<Type>* node, Type value) {
	if (emptyNode(node))
		return new Node<Type>(value);
	if (value < node->key)
		node->left = insertNode(node->left, value);
	else
		node->right = insertNode(node->right, value);
	return balanceNode(node);
}


template<typename Type>
Node<Type>* getMinNode(Node<Type>* node) {
	while (!emptyNode(node->left))
		node = node->left;
	return node;
}

template<typename Type>
Node<Type>* withoutMinNode(Node<Type>* node) {
	if (emptyNode(node->left))
		return node->right;
	node->left = withoutMinNode(node->left);
	return balanceNode(node);
}

template<typename Type>
Node<Type>* eraseNode(Node<Type>* node, Type value) {
	if (emptyNode(node))
		return nullptr;
	if (value < node->key)
		node->left = eraseNode(node->left, value);
	else if (value > node->key)
		node->right = eraseNode(node->right, value);
	else {
		Node<Type>* leftNode = node->left;
		Node<Type>* rightNode = node->right;
		delete node;
		if (emptyNode(rightNode))
			return leftNode;
		Node<Type>* minNode = getMinNode(rightNode);
		minNode->right = withoutMinNode(rightNode);
		minNode->left = leftNode;
		return balanceNode(minNode);
	}
	return balanceNode(node);
}

template<typename Type>
bool findNode(Node<Type>* node, Type value) {
	while (!emptyNode(node) && node->key != value)
		if (value < node->key)
			node = node->left;
		else
			node = node->right;
	return !emptyNode(node) && (node->key == value);
}

template<typename Type>
void destroyTree(Node<Type>* node) {
	if (emptyNode(node))
		return;
	destroyTree(node->left);
	destroyTree(node->right);
	delete node;
}

#endif
