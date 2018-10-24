#include "tree.hpp"

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

template<class K, class T>
bool tree<K, T>::eq(K k1, K k2)
{
    return (!(rule(k1, k2) || rule(k2, k1)));
}

template<class K, class T>
typename tree<K, T>::Node * tree<K, T>::locate(K k, Node* t)
{
	while (t != nullptr && !eq(k, t->key))
		if (rule(t->key, k))
			t = t->right;
		else
			t = t->left;
	return t;
}




template <class K, class T>
void tree<K, T>::insert(K k, T d)
{
	bool h = root == nullptr;
	insert(k, d, root, h);
}

template<class K, class T>
void tree<K, T>::insert(K k, T d, Node *& p, bool & h)
{
	if (p == nullptr)
	{
		p = new Node(k, d);
		h = true;
	}
	else
	{
		if (rule(k, p->key))
		{
			insert(k, d, p->left, h);
			if (h)
			{
				switch (p->balance)
				{
				case 1:
					p->balance = 0;
					h = false;
					break;
				case 0:
					p->balance = -1;
					break;
				case -1:
					Node* p1 = p->left;
					if (p1->balance == -1)
					{
						p->left = p1->right;
						p1->right = p;
						p->balance = 0;
						p = p1;
					}
					else
					{
						Node* p2 = p1->right;
						p1->right = p2->left;
						p2->left = p1;
						p->left = p2->right;
						p2->right = p;
					}
					p->balance = 0;
					h = false;
					break;
				}
			}
		}
		else
		{
			if (rule(p->key,k))
			{
				insert(k, d, p->right, h);
				if (h)
				{
					switch (p->balance)
					{
						case -1:
							p->balance = 0;
							h = false;
							break;
						case 0:
							p->balance = 1;
							break;
						case 1:
							Node* p1 = p->right;
							if (p1->balance==1)
							{
								p->right = p1->left;
								p1->left = p;
								p->balance = 0;
								p = p1;
							}
							else
							{
								Node* p2 = p1->left;
								p1->left = p2->right;
								p2->right = p1;
								p->right = p2->left;
								p2->left = p;
								if (p2->balance == 1)
									p->balance = -1;
								else
									p->balance = 0;
								if (p2->balance == -1)
									p1->balance = 1;
								else
									p1->balance = 0;
								p = p2;

							}
							p->balance = 0;
							h = false;
							break;
					}
				}
			}
		}
	}
}

template<class K, class T>
T tree<K,T>::search(K k)
{
	Node* node = locate(k, root);
	if (node != nullptr)
		return node;
	else
		throw "not found";
        
}

template<class K, class T>
void tree<K, T>::traverse(void(*f)(K k, T d))
{
	_traverse(root, f);
}

template<class K, class T>
void tree<K, T>::traverse(void(*f)(Node *))
{
	_traverse(root, f);
}

template<class K, class T>
void tree<K, T>::_traverse(Node *p, void(*f)(K k, T d))
{
	if (p==nullptr)
	{
		return;
	}
	_traverse(p->left, f);
	f(p->key, p->data);
	_traverse(p->right, f);
}

template<class K, class T>
void tree<K, T>::_traverse(Node* node, void(*f)(Node *))
{
	if (node==nullptr)
		return;
	_traverse(node->left, f);
	f(node);
	_traverse(node->right, f);
}


template<class K, class T>
unsigned int tree<K, T>::height(Node *target)
{
	if (target==nullptr)
	{
		return 0;
	}
	unsigned int l = 0;
	unsigned int r = 0;

	if (target->left != nullptr)
		l = height(target->left);

	if (target->right != nullptr)
		r = height(target->right);

	if (l < r)
		return r+1;
	else
		return l+1;
}

template<class K, class T>
void tree<K, T>::printinfo()
{
	traverse([](Node* s) {std::cout << s->key << " : " << s->data << "; " << s->balance << std::endl; });
}

template<class K, class T>
void tree<K, T>::_Balance(Node* node)
{
	if (node == nullptr)
		return;
	_Balance(node->left);
	node->balance=height(node->right) - height(node->left);
	_Balance(node->right);
}



template<class K, class T>
void tree<K, T>::Balance()
{
	_Balance(root);
	
}