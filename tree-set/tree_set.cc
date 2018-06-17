#include "tree_set.h"

template<class Key>
TreeSet<Key>::Leaf::Leaf()
{
	this->parent_ = NULL;
	this->left_ = NULL;
	this->right_ = NULL;
}

template<class Key>
TreeSet<Key>::Leaf::Leaf(Key value)
{
	this->value_ = value;
	this->parent_ = NULL;
	this->left_ = NULL;
	this->right_ = NULL;
}

template<class Key>
TreeSet<Key>::Leaf::~Leaf()
{
	this->parent_ = NULL;
	this->left_ = NULL;
	this->right_ = NULL;
}




template<class Key>
TreeSet<Key>::Iterator::Iterator()
{
	this->leaf_ = NULL;
}

template<class Key>
TreeSet<Key>::Iterator::Iterator(Leaf * leaf)
{
	this->leaf_ = leaf;
}

template<class Key>
TreeSet<Key>::Iterator::Iterator(const Iterator & iterator)
{
	this->leaf_ = iterator.leaf_;
}

template<class Key>
TreeSet<Key>::Iterator::~Iterator()
{
	this->leaf_ = NULL;
}

template<class Key>
typename TreeSet<Key>::Iterator& TreeSet<Key>::Iterator::operator=(Iterator& iterator)
{
	if (this == &iterator) return iterator;
	this->leaf_ = iterator.leaf_;
	return *this;
}

template<class Key>
bool TreeSet<Key>::Iterator::operator==(const Iterator & iterator)
{
	return this->leaf_ == iterator.leaf_;
}

template<class Key>
bool TreeSet<Key>::Iterator::operator!=(const Iterator & iterator)
{
	return *this != iterator;
}

template<class Key>
typename TreeSet<Key>::Iterator& TreeSet<Key>::Iterator::operator++(int)
{
	if (this->leaf_ != NULL) {
		if (this->leaf_->right_ != NULL) {
			this->leaf_ = this->leaf_->right_;
			while (this->leaf_->left_ != NULL)
				this->leaf_ = this->leaf_->left_;
		}
		else {
			while (this->leaf_->parent_->right_ == this->leaf_)
				this->leaf_ = this->leaf_->parent_;
			this->leaf_ = this->leaf_->parent_;
		}
	}
	return *this;
}

template<class Key>
typename TreeSet<Key>::Iterator& TreeSet<Key>::Iterator::operator--(int)
{
	if (this->leaf_ != NULL) {
		if (this->leaf_->left_ != NULL) {
			this->leaf_ = this->leaf_->left_;
			while (this->leaf_->right_ != NULL)
				this->leaf_ = this->leaf_->right_;
		}
		else {
			while (this->leaf_->parent_->left_ == this->leaf_)
				this->leaf_ = this->leaf_->parent_;
			this->leaf_ = this->leaf_->parent_;
		}
	}
	return *this;
}

template<class Key>
Key & TreeSet<Key>::Iterator::operator*()
{
	return this->leaf_->value_;
}

template<class Key>
Key & TreeSet<Key>::Iterator::operator->()
{
	return this->leaf_->value_;
}

template<class Key>
typename TreeSet<Key>::Iterator TreeSet<Key>::head()
{
	Leaf* head = root_;
	while (head->left_)
		head = head->left_;
	return Iterator(head);
}

template<class Key>
typename TreeSet<Key>::Iterator TreeSet<Key>::tail()
{
	Leaf* tail = this->root_;
	while (tail->right_)
		tail = tail->right_;
	return Iterator(tail);
}

template<class Key>
typename TreeSet<Key>::Iterator TreeSet<Key>::find(const Key & value)
{
	Leaf* result = root;
	while (result) {
		if (result->value_ == value) return Iterator(result);
		else if (result->value_ < value) result = result->right_;
		else if (result->value_ > value) result = result->left_;
	}
	return tail();
}





template<class Key>
TreeSet<Key>::TreeSet()
{
	root_ = NULL;
}

template<class Key>
TreeSet<Key>::TreeSet(const TreeSet & set)
{
	root_ = NULL;
	prefix(set.root_);
}

template<class Key>
TreeSet<Key>::~TreeSet()
{
	clear(root_);
}

template<class Key>
void TreeSet<Key>::prefix(Leaf * leaf)
{
	if (!leaf) return;
	insert(leaf->value_);
	prefix(leaf->left_);
	prefix(leaf->right_);
}

template<class Key>
TreeSet<Key>& TreeSet<Key>::operator=(TreeSet & set)
{
	if (this == &set) return set;
	prefix(set.root_);
	return *this;
}

template<class Key>
bool TreeSet<Key>::operator==(TreeSet & set)
{
	if (this->size() != set.size()) return false;

	Iterator this_iterator = head();
	Iterator set_iterator = set.head();
	Iterator this_tail = tail();
	Iterator set_tail = set.tail();

	while (this_iterator != this_tail || set_iterator != set_tail) {
		if (*this_iterator != *set_iterator) return false;
		this_iterator++;
		set_iterator++;
	}

	return this_tail == set_tail;
}

template<class Key>
bool TreeSet<Key>::operator!=(TreeSet & set)
{
	return !(this == set);
}

template<class Key>
bool TreeSet<Key>::empty()
{
	return !(this->root_);
}

template<class Key>
int TreeSet<Key>::size()
{
	return size(this->root_);
}

template<class Key>
void TreeSet<Key>::insert(Key value)
{
	if (empty()) {
		this->root_ = new Leaf;
		this->root_->value_ = value;
		this->root_iterator_ = Iterator(this->root_);
	}
	else {
		Leaf* leaf = this->root_;
		Leaf* parent = NULL;

		while (leaf) {
			parent = leaf;
			if (value < leaf->value_) leaf = leaf->left_;
			else if (value > leaf->value_) leaf = leaf->right_;
			else return;
		}

		leaf = new Leaf;
		leaf->value_ = value;
		leaf->parent_ = parent;

		if (value < parent->value_) parent->left_ = leaf;
		else parent->right_ = leaf;
	}
}

template<class Key>
int TreeSet<Key>::remove(Key value)
{
	Leaf* leaf_to_remove = root;

	while (leaf_to_remove != NULL && leaf_to_remove->value_ != value)
		leaf_to_remove = leaf_to_remove->value_ > value ? leaf_to_remove->left_ : leaf_to_remove->right_;

	if (leaf_to_remove == NULL) return 0;

	Leaf* helper_leaf;

	if (leaf_to_remove->right_ == NULL)
		helper_leaf = leaf_to_remove->left_;
	else if (leaf_to_remove->left_ == NULL)
		helper_leaf = leaf_to_remove->right_;
	else {
		helper_leaf = leaf_to_remove->right_;

		while (helper_leaf->right_)
			helper_leaf = helper_leaf->right_;

		if (helper_leaf->parent_ == leaf_to_remove)
			helper_leaf->right_ = leaf_to_remove->right_;
		else {
			helper_leaf = leaf_to_remove->right_;
			helper_leaf->parent_->right_ = helper_leaf->left_;
			helper_leaf->left_ = helper_leaf->parent_;
		}
	}

	if (leaf_to_remove == this->root_) root = helper_leaf;
	else if (leaf_to_remove->value_ < leaf_to_remove->parent_->value_)
		leaf_to_remove->parent_->left = helper_leaf;
	else leaf_to_remove->parent_->right_ = helper_leaf;

	if (helper_leaf) helper_leaf->parent_ = leaf_to_remove->parent_;

	delete leaf_to_remove;

	this->root_iterator_ = Iterator(this->root_);

	return 1;
}

template<class Key>
void TreeSet<Key>::clear()
{
	if (!empty()) {
		clear(this->root_);
		this->root_ = NULL;
	}
}


template<class Key>
int TreeSet<Key>::size(Leaf * leaf)
{
	if (!leaf) return 0;

	if (leaf->left_ == NULL && leaf->right_ == NULL)
		return 1;

	int left_size = 0;
	if (leaf->left_ != NULL)
		left_size = size(leaf->left_);

	int right_size = 0;
	if (leaf->right_ != NULL)
		right_size = size(leaf->right_);

	return left_size + right_size + 1;
}

template<class Key>
void TreeSet<Key>::clear(Leaf * leaf)
{
	if (!leaf) return;

	if (leaf->left_) {
		clear(leaf->left_);
		leaf->left_ = NULL;
	}

	if (leaf->right_) {
		clear(leaf->right_);
		leaf->right_ = NULL;
	}

	delete leaf;
}
