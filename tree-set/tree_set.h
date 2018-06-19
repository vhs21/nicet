#pragma once

template <class Key>
class TreeSet
{
  private:
	class Leaf
	{
	  public:
		Key value_;
		Leaf *right_;
		Leaf *left_;
		Leaf *parent_;

		Leaf();
		Leaf(Key value);
		~Leaf();
	};

	Leaf *root_;

	int size(Leaf *leaf);
	void clear(Leaf *leaf);

	void prefix_copy(Leaf *leaf);

  public:
	TreeSet();
	TreeSet(const TreeSet &set);
	~TreeSet();

	TreeSet &operator=(TreeSet &set);

	bool operator==(TreeSet &set);
	bool operator!=(TreeSet &set);

	bool empty();
	int size();

	void insert(Key value);
	int remove(Key value);
	void clear();

	class Iterator
	{
	  public:
		Iterator();
		Iterator(Leaf *leaf);
		Iterator(const Iterator &iterator);
		~Iterator();

		Iterator &operator=(Iterator iterator);

		bool operator==(const Iterator &iterator);
		bool operator!=(const Iterator &iterator);

		Iterator &operator++(int);
		Iterator &operator--(int);

		Key &operator*();
		Key &operator->();

	  private:
		friend class TreeSet<Key>;
		Leaf *leaf_;
	};

	Iterator root_iterator_;

	Iterator head();
	Iterator tail();
	Iterator find(const Key &value);
};
