#include"set.h"

template<class Key>
set<Key>::Leaf::Leaf()
{
	this->parent = 0;
	this->right = 0;
	this->left = 0;
}

template<class Key>
set<Key>::Leaf::~Leaf()
{
	this->left = 0;
	this->right = 0;
	this->parent = 0;
}

template<class Key>
set<Key>::Leaf::Leaf(Key value)
{
	this->value = value;
	this->right = 0;
	this->left = 0;
}

template<class Key>
set<Key>::iterator::iterator()
{
	this->leaf = 0;
}

template<class Key>
set<Key>::iterator::iterator(Leaf * leaf)
{
	this->leaf = leaf;
}

template<class Key>
set<Key>::iterator::iterator(const iterator & it)
{
	this->leaf = it.leaf;
}

template<class Key>
typename set<Key>::iterator& set<Key>::iterator::operator=(iterator & it)
{
	if (this == &it) return it;
	this->leaf = it.leaf;
	return *this;
}

template<class Key>
set<Key>::iterator::~iterator() {}

template<class Key>
bool set<Key>::iterator::operator==(const iterator & it)
{
	return (this->leaf == it.leaf);
}

template<class Key>
bool set<Key>::iterator::operator!=(const iterator & it)
{
	return !(*this == it);
}

template<class Key>
typename set<Key>::iterator& set<Key>::iterator::operator++(int)
{
	if (this->leaf != 0)
	{
		if (this->leaf->right != 0)
		{
			this->leaf = this->leaf->right;
			while (this->leaf->left != 0) this->leaf = this->leaf->left;
		}
		else
		{
			while (this->leaf->parent->right == this->leaf) this->leaf = this->leaf->parent;
			this->leaf = this->leaf->parent;
		}
	}
	return *this;
}

template<class Key>
typename set<Key>::iterator& set<Key>::iterator::operator--(int)
{
	if (this->leaf != 0)
	{
		if (this->leaf->left != 0)
		{
			this->leaf = this->leaf->left;
			while (this->leaf->right != 0) this->leaf = this->leaf->right;
		}
		else
		{
			while (this->leaf->parent->left == this->leaf) this->leaf = this->leaf->parent;
			this->leaf = this->leaf->parent;
		}
	}
	return *this;
}

template<class Key>
Key & set<Key>::iterator::operator*()
{
	return leaf->value;
}

template<class Key>
Key & set<Key>::iterator::operator->()
{
	return leaf->value;
}

template<class Key>
set<Key>::set()
{
	root = 0;
}

template<class Key>
set<Key>::~set()
{
	clear(root);
}

template<class Key>
set<Key>::set(const set<Key> & st)
{
	root = 0;
	prefix(st.root);
}

template<class Key>
void set<Key>::prefix(Leaf *temp)
{
	if (!temp) return;
	insert(temp->value);
	prefix(temp->left);
	prefix(temp->right);
}

template<class Key>
set<Key>& set<Key>::operator=(set<Key>& st)
{
	if (this == &st) return st;
	prefix(st.root);
	return *this;
}

template<class Key>
bool set<Key>::operator<(const set<Key>& st)
{
	if (this->size() < st.size()) return true;
	return false;
}

template<class Key>
bool set<Key>::operator<=(const set<Key>& st)
{
	if (this->size() <= st.size()) return true;
	return false;
}

template<class Key>
bool set<Key>::operator>(const set<Key>& st)
{
	if (this->size() > st.size()) return true;
	return false;
}

template<class Key>
bool set<Key>::operator>=(const set<Key>& st)
{
	if (this->size() >= st.size()) return true;
	return false;
}

template<class Key>
bool set<Key>::operator==(set<Key>& st)
{
	if (this->size() != st.size()) return false;
	iterator head = begin(), tail = end();
	iterator st_head = st.begin(), st_tail = st.end();
	iterator temp = head, st_temp = st_head;
	for (temp; temp != tail; temp++)
	{
		if (*temp != *st_temp) return false;
		st_temp++;
	}
	if (*tail != *st_tail) return false;
	return true;
}

template<class Key>
bool set<Key>::operator!=(set<Key>& st)
{
	if (this->size() != st.size()) return true;
	iterator head = begin(), tail = end();
	iterator st_head = st.begin(), st_tail = st.end();
	iterator temp = head, st_temp = st_head;
	for (temp; temp != tail; temp++)
	{
		if (*temp != *st_temp) return true;
		st_temp++;
	}
	if (*tail != *st_tail) return true;
	return false;
}

template<class Key>
bool set<Key>::empty()
{
	return !(this->root);
}

template<class Key>
int set<Key>::size(Leaf * leaf)
{
	if (!leaf) return 0;
	if (leaf->left == 0 && leaf->right == 0) return 1;
	int left, right;
	if (leaf->left != NULL) left = size(leaf->left);
	else left = 0;
	if (leaf->right != NULL) right = size(leaf->right);
	else right = 0;
	return left + right + 1;
}

template<class Key>
int set<Key>::size()
{
	return size(root);
}

template<class Key>
typename set<Key>::iterator set<Key>::begin()
{
	Leaf * begin = root;
	while (begin->left)
	{
		begin = begin->left;
	}
	return iterator(begin);
}

template<class Key>
typename set<Key>::iterator set<Key>::end()
{
	Leaf * end = root;
	while (end->right)
	{
		end = end->right;
	}
	return iterator(end);
}

template<class Key>
void set<Key>::insert(Key value)
{
	if (empty())
	{
		root = new Leaf;
		root->value = value;
		root->parent = 0;
		root->left = 0;
		root->right = 0;
		root_iterator = iterator(root);
	}
	else
	{
		Leaf *temp = root, *parent = 0;
		while (temp)
		{
			parent = temp;
			if (value < temp->value) temp = temp->left;
			else if (value > temp->value)  temp = temp->right;
			else return;
		}
		temp = new Leaf;
		temp->value = value;
		temp->left = temp->right = 0;
		temp->parent = parent;
		if (value < parent->value) parent->left = temp;
		else parent->right = temp;
	}
}

template<class Key>
int set<Key>::erase(Key value)
{
	Leaf *leaf_to_del = root, *temp;
	while (leaf_to_del != 0 && leaf_to_del->value != value)
	{
		if (leaf_to_del->value > value) leaf_to_del = leaf_to_del->left;
		else leaf_to_del = leaf_to_del->right;
	}
	if (leaf_to_del == 0)
	{
		cout << "no such element in the container" << endl;
		return 0;
	}
	if (leaf_to_del->right == 0) temp = leaf_to_del->left;
	else if (leaf_to_del->left == 0) temp = leaf_to_del->right;
	else
	{
		temp = leaf_to_del->left;
		while (temp->right != 0) temp = temp->right;
		if (temp->parent == leaf_to_del) temp->right = leaf_to_del->right;
		else
		{
			temp->right = leaf_to_del->right;
			temp->parent->right = temp->left;
			temp->left = temp->parent;
		}
	}

	if (leaf_to_del == root) root = temp;
	else if (leaf_to_del->value < leaf_to_del->parent->value) leaf_to_del->parent->left = temp;
	else leaf_to_del->parent->right = temp;
	if (temp) temp->parent = leaf_to_del->parent;
	delete leaf_to_del;
	root_iterator = iterator(root);
	return 1;
}

template<class Key>
void set<Key>::clear(Leaf * leaf)
{
	if (!leaf) return;
	if (leaf->left)
	{
		clear(leaf->left);
		leaf->left = 0;
	}
	if (leaf->right)
	{
		clear(leaf->right);
		leaf->right = 0;
	}
	delete leaf;
}

template<class Key>
void set<Key>::clear()
{
	if (!empty())
	{
		clear(root);
		root = 0;
		cout << "сontainer cleared" << endl;
	}
	else cout << "сontainer is empty" << endl;
}

template<class Key>
void set<Key>::show()
{
	if (!empty())
	{
		iterator head = begin();
		iterator tail = end();
		for (iterator temp = head; temp != tail; temp++)
		{
			cout << *temp << endl;
		}
		cout << *tail << endl;
	}
}

template<class Key>
typename set<Key>::iterator set<Key>::find(const Key& key)
{
	Leaf *res = root;
	while (res)
	{
		if (res->value == key) return iterator(res);
		else if (res->value < key) res = res->right;
		else if (res->value > key) res = res->left;
	}
	return end();
}

template<class Key>
void set<Key>::edit(Key key)
{
	if (!empty())
	{
		if (erase(key))
		{
			Key new_key;
			cin >> new_key;
			insert(new_key);
		}
	}
}

template<class Key>
template<class F>
void set<Key>::generate(F random)
{
	insert(random());
}