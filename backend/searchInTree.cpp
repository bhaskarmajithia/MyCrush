#define cerr1(a)					cerr << "[ " << a << " ]\n"
#define cerr2(a,b)					cerr << "[ " << a << " , " << b << " ]\n"
#define cerr3(a,b,c)				cerr << "[ " << a << " , " << b << " , " << c << " ]\n"
#include <bits/stdc++.h>
using namespace std;

/*
	This file would only get called if
	
	1) User is logged in without FbID

	2) If user has fbId but current search returns less than 5 objects

	3) User wants to know list of all users?
			get successors from
*/
/*
	functions
	getSuccessors(int number_of_successors)
	find(string name, int id)
	getSuccessor(node*, int id)
	insert(string name, int id)

	class node
	{
		string currentName
		set <person>
		char current
		bool isTerminal()
		{
			return set.size != 0;
		}
		void insert(person p)
		{
			set.insert(p);
		}
	};
	class person
	{
		int id
		string lopp
	};
*/
class Person
{

public:
	int id;
	string lopp;
	Person(){}
	Person(int id, string lopp)
	{
		this -> id = id;
		this -> lopp = lopp;
	}
	bool operator<(const Person & rhs) const 
	{
   		return id < rhs.id; 
	}
};

class Node
{

public:	
	Node* left;
	Node* right;
	Node* center;
	Node* parent;
	char curr;
	string currentName;
	set <Person> personWithSameNames;
	Node()
	{
		left = NULL;
		right = NULL;
		center = NULL;
		parent = NULL;
	}

	Node(char curr, string previousName)
	{
		this -> curr = curr;
		currentName = previousName + curr;
		left = NULL;
		right = NULL;
		center = NULL;
		parent = NULL;
	}
 
	bool isTerminal()
	{
		return personWithSameNames.size() != 0;
	}
};

void insert(Node* &root, Node* &parent, Person p, string &name, int it)
{

	if (root == NULL)
	{

		root = new Node(name[it], "");
		root -> parent = parent;
	}
	
	if (name[it] < root -> curr)
	{
		insert(root -> left, root, p, name, it);
	}

	else if(name[it] > root -> curr)
	{
		insert(root -> right, root, p, name, it);
	}

	else 
	{
		if(it < name.length())
		{
			insert(root -> center, root, p, name, it + 1);
		}

		else 
		{
			root -> personWithSameNames.insert(p);
		}
	}
}

void traverse(Node* &root, string buffer)
{
	if(root != NULL)
	{
		traverse(root -> left, buffer);
		buffer += root -> curr; 
		
		if (root -> isTerminal())
		{
			cerr2(buffer, root -> parent -> curr);
			for (auto i = root -> personWithSameNames.begin(); i != root -> personWithSameNames.end(); ++i)
			{
				cerr2(i -> id, i -> lopp);				
			}
		}

		traverse(root -> center, buffer);

		buffer.erase(buffer.end() - 1);
		traverse(root -> right, buffer);
	}

}

Node* searchPrefix(Node* &root, string name, int it = 0)
{	
	if (root == NULL)
	{
		return root;
	}	

	if (it < name.length())
	{
		if (name[it] < root -> curr)
		{
			return searchPrefix(root -> left, name, it);
		}	
		
		else if (name[it] > root -> curr)
		{
			return searchPrefix(root -> right, name, it); 
		}

		else
		{
			return searchPrefix(root -> center, name, it + 1);
		}	
	}

	else
	{
		return root;
	}
}

Node* getLeftMost(Node* &root, string &str)
{
	
	if (root -> isTerminal())
	{
		return root;
	}

	else if (root -> left != NULL)
	{
		getLeftMost(root -> left, str);
	}

	else if(root -> center != NULL)
	{
		str += root -> curr;
		getLeftMost(root -> center, str);
	}

	else
	{
		getLeftMost(root -> right, str);
	}

}

Node* getSuccessor(Node* &curr, string str)
{
	//while parent ka left child 
	//check if it is terminal or not
	// if not terminal

	if (curr -> left)
	{
		cerr1('.'); 
		str.erase(str.end() - 1);
		str += curr -> left -> curr;
		cerr1(str);
		Node* temp = getLeftMost(curr -> left, str);
	
		cerr1(temp -> curr);

		return temp;
	}

	/*if(curr -> parent -> right)
	{
		curr = curr -> parent -> right;

	}*/

}

void bfs(Node* &root)
{
	queue<Node*> q;
	q.push(root);
	while (!q.empty())
	{
		Node* front = q.front();
		q.pop();
		if (front -> left)
			q.push(front -> left);
		if (front -> center)
			q.push(front -> center);
		if (front -> right)
			q.push(front -> right);
		cerr3(front -> curr, front -> currentName, front -> parent -> curr);
	}
}

int main(int argc, char const *argv[])
{

	Node* maleTree = new Node('m', "");
	Node* godFather = new Node('g', "godFather");
	maleTree -> parent = godFather;
	godFather -> right =  maleTree;
	int queries;
	cin >> queries;
	while (queries--)
	{
		int type;
		cin >> type;
		if (type == 1)
		{
			//insert()
			string name;
			int id;
			int it = 0;
			string lopp;
			cin >> name >> id >> lopp;
			Person p(id, lopp);
			insert(maleTree, godFather, p, name, it);  

		}

		else if (type == 2)
		{
			traverse(maleTree, "");
		}

		else if (type == 3)
		{
			string prefix;
			cin >>  prefix;
			Node* curr = searchPrefix(maleTree, prefix);
			if(curr == NULL)
			{
				cout << "NO user";
			}
			else
			{
				Node* leftMost = getLeftMost(curr, prefix);
				cerr1(leftMost -> curr);
				cout << prefix;
				getSuccessor(leftMost, prefix);
			}
		}
		else if (type == 4)
		{
			bfs (maleTree);
		}
	}

	return 0;
}