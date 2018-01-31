#include<iostream>
#include<string.h>

using namespace std;

template<class Key>
class set
{
private:
	class Leaf
	{
	public:
		Key value;
		Leaf *right;
		Leaf *left;
		Leaf *parent;

		Leaf(Key new_value);
		Leaf();
		~Leaf();

		friend ostream &operator<<(ostream &, const Leaf &);
		friend istream &operator>>(istream &, Leaf &);
	};
	Leaf *root;

	int size(Leaf *);
	void clear(Leaf *);

public:
	set();
	~set();
	set(const set &);

	void prefix(Leaf*);

	set& operator=(set&);
	bool operator<(const set&);
	bool operator<=(const set&);
	bool operator>(const set&);
	bool operator>=(const set&);
	bool operator==(set&);
	bool operator!=(set&);

	class iterator
	{
	private:
		friend class set<Key>;
		Leaf *leaf;
	public:
		iterator();
		iterator(Leaf *);
		~iterator();
		iterator(const iterator &);
		iterator& operator=(iterator&);
		bool operator==(const iterator &);
		bool operator!=(const iterator &);
		iterator & operator++(int);
		iterator & operator--(int);
		Key & operator*();
		Key & operator->();
	};

	iterator root_iterator;

	bool empty();
	int size();

	iterator begin();
	iterator end();
	iterator find(const Key&);

	void insert(Key);
	int erase(Key);
	void clear();
	void show();
	void edit(Key);
	template<class F>
	void generate(F);
};