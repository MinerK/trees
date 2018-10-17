#include "tree.h"

template <class K, class T>
tree<K, T>::tree()
{
	root = nullptr;
	rule = nullptr;
}

template<class K,class T>
tree<K,T>::tree(bool(*f)(K, K))
{
	root = nullptr;
	rule = f;
}


template<class K, class T>
tree<K,T>::tree(bool(*f)(K, K), K k, T d) : tree(f)
{
	root = new Node(k, d);
}

template <class K, class T>
tree<K, T>::~tree()
{
	
}

template <class K, class T>
void tree<K, T>::insert(K k, T d)
{
	Node* cursor = root;
	bool stop = false;
	while (!stop)
	{
		if (rule(k, cursor->key))
			if (cursor->left != nullptr)
				cursor = cursor->left;
			else
			{
				cursor->left = new Node(k, d);
				stop = true;
			}
		else
			if (cursor->right != nullptr)
				cursor = cursor->right;
			else
			{
				cursor->right = new Node(k, d);
				stop = true;
			}
	}
}

template<class K, class T>
bool tree<K, T>::intree(K k)
{
	if (isequal(root->key,k))
		return true;
	bool t = false;
	for (Node* cursor = root; !(isleaf(*cursor) || t); cursor=rule(cursor->left->key, k)?cursor->left:cursor->right)
	{
		t = isequal(cursor->key, k);
	}
	return t;
}

template<class K, class T>
bool tree<K, T>::isleaf(Node & a)
{
	return (a.left == nullptr && a.right == nullptr);
}

template<class K, class T>
bool tree<K, T>::isequal(K k1, K k2)
{
	return (!(rule(k1, k2) || rule(k2, k1)));
}
