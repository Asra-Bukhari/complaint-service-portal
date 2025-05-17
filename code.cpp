#include <iostream>
#include <vector>
#include <string>
using namespace std;

class user {
public:
	int userID;
	string userName;
	string email;
	string country;
	string type;
	static int userIDgen;
	user* prev;
	user* next;

	user(int id, string n, string em, string c, string t, user* p, user* ne)
	{
		userID = id;
		userName = n;
		email = em;
		country = c;
		type = t;

		prev = p;
		next = ne;
	}
	user()
	{
		prev = next = nullptr;
	}
	void print() {
		cout << "_User ID : " << userID << "" << endl;
		cout << "UserName: " << userName << "\t\tEmail: " << email << endl;
		cout << "Country: " << country << "\t\t\tType: " << type << endl;

	}
};
int user::userIDgen = 0;

class singlylist {
private:
	class snode {
	public:
		user* ptr;
		snode* next;
		snode(user* data, snode* ne=nullptr)
		{
			ptr = data;
			next = ne;
		}
		snode()
		{
			next = nullptr;
		}
	};
	snode* head;
	snode* tail;

public:
	singlylist()
	{
		head = tail = nullptr;
	}
	void insert(user* d)
	{
		if (d == nullptr)
			return;
		snode* newnode = new snode(d);
		newnode->next = head;
		if (head == nullptr)
			tail = newnode;
		head = newnode;
	}
	void print()
	{
		snode* c = head;
		while (c != nullptr)
		{
			c->ptr->print();
			c = c->next;
		}
	}
	
	bool isempty() {
		return (head == nullptr);
	}
	user* getdelFirstuser()
	{
		user* s = head->ptr;
		if (head == tail) {
			delete head;
			head = tail = nullptr;
		}
		else {
			snode* temp = head;
			head = head->next;
			delete temp;
		}
		return s;
	}
	void removeuser(user* s) {
		if (isempty()) return;
		snode* c = head;
		snode* p = nullptr;
		while (c != nullptr)
		{
			if (c->ptr == s)
			{
				if (p == nullptr) {
					if (head == tail) {
						delete head;
						head = tail = nullptr;
						return;
					}
					else {
						snode* temp = head;
						head = head->next;
						delete temp;
						return;
					}	
				}
				else {
					p->next = c->next;
					delete c;
					return;
				}
			}
			p = c;
			c = c->next;
		}

	}
	int getnodecount() {
		int count = 0;
		snode* c = head;
		while (c != nullptr)
		{
			count++;
			c = c->next;
		}
		return count;
	}
	user* getindex(int i) {
		int j = 0;
		snode* c = head;
		while (c != nullptr)
		{
			if (j == i)
				return c->ptr;
			j++;
			c = c->next;
		}
	}
	~singlylist()
	{
		snode* c = head, * temp;
		while (c != nullptr)
		{
			temp = c->next;
			delete c;
			c = temp;
		}
	}
};

template <typename T>
class AVL {
	class node {
	public:
		T indData;
		user* userPtr;
		node* left;
		node* right;
		int height;
		node(T d = 0, user* p = nullptr, node* l = nullptr, node* r = nullptr) {
			indData = d;
			userPtr = p;
			left = l;
			right = r;
			height = 0;
		}
	};
	node* root;

public:
	AVL() {
		root = nullptr;
	}

	int getheight(node* r) {
		if (r == nullptr)
			return -1;
		else
			return r->height;
	}
	void rightRotate(node*& x) {
		node* y = x->left;
		x->left = y->right;
		y->right = x;

		x->height = 1 + max(getheight(x->left), getheight(x->right));
		y->height = 1 + max(getheight(y->left), x->height);
		x = y;

	}
	void leftRotate(node*& x) {
		node* y = x->right;
		x->right = y->left;
		y->left = x;

		x->height = 1 + max(getheight(x->left), getheight(x->right));
		y->height = 1 + max(getheight(y->right), x->height);
		x = y;
	}
	void DoubleRR(node*& x) {
		leftRotate(x->left);
		rightRotate(x);
	}
	void DoubleRL(node*& x) {
		rightRotate(x->right);
		leftRotate(x);
	}
	void insert(const T& id, user* ptr, node*& r) {
		if (r == nullptr) {
			r = new node(id, ptr, nullptr, nullptr);
			return;
		}
		if (id < r->indData) {
			insert(id, ptr, r->left);
			if (getheight(r->left) - getheight(r->right) == 2) {
				if (id < r->left->indData)
					rightRotate(r);
				else
					DoubleRR(r);
			}
		}
		else if (id > r->indData) {
			insert(id, ptr, r->right);
			if (getheight(r->left) - getheight(r->right) == -2) {
				if (id > r->right->indData)
					leftRotate(r);
				else
					DoubleRL(r);
			}
		}
		r->height = 1 + max(getheight(r->left), getheight(r->right));
	}
	void insert(const T& id, user* ptr) {
		insert(id, ptr, root);
	}

	user* searchindexforinsertion(int id) {
		node* current = root;
		node* closest = nullptr;

		while (current != nullptr) {
			if (current->indData < id) {
				closest = current;
				current = current->right;
			}
			else {
				current = current->left;
			}
		}

		if (closest)
			return closest->userPtr;
		else
			return nullptr;
	}
	user* search(T d, node*& r) {
		if (r == nullptr)
			return nullptr;
		if (r->indData == d)
			return r->userPtr;
		else if (r->indData > d)
			return search(d, r->left);
		else if (r->indData < d)
			return search(d, r->right);
	}
	user* search(T d) {
		return search(d, root);
	}

	T getmaxid(node* r,user*& s) {
		if (r->right == nullptr)
		{
			s = r->userPtr;
			return r->indData;
		}
		else
			return getmaxid(r->right,s);
	}
	int BalanceF(node* r) {
		return (getheight(r->left) - getheight(r->right));
	}
	void deletee(node*& r, T d)
	{
		if (r)
		{
			if (r->indData == d)
			{
				if (r->left == nullptr && r->right == nullptr)
				{
					delete r;
					r = nullptr;
					return;
				}
				else if (r->left == nullptr)
				{
					node* temp = r->right;
					delete r;
					r = temp;
				}
				else if (r->right == nullptr)
				{
					node* temp = r->left;
					delete r;
					r = temp;
				}
				else
				{
					user* s;
					T temp = getmaxid(r->left,s);
					r->indData = temp;
					r->userPtr = s;
					deletee(r->left, temp);
					
				}
			}
			else if (r->indData > d)
			{
				deletee(r->left, d);
			}
			else
				deletee(r->right, d);
		}

		if (root == nullptr)
			return;

		r->height = 1 + max(getheight(r->left), getheight(r->right));

		int balance = BalanceF(r);

		if (balance == 2)
		{
			if (BalanceF(r->left) >= 0)
			{
				rightRotate(r);
			}
			else
				DoubleRR(r);
		}
		if (balance == -2)
		{
			if (BalanceF(r->right) <= 0)
			{
				leftRotate(r);
			}
			else
				DoubleRL(r);
		}

	}
	void deletee(T d) {
		deletee(root, d);
	}
	void Destroy(node* r) {
		if (r != nullptr) {
			Destroy(r->left);
			Destroy(r->right);
			delete r;
		}
	}
	void print(node* r) {
		if (r != nullptr) {
			print(r->left);
			cout << "->" << r->indData ;
			print(r->right);
		}
	}
	void print() {
		print(root);
		cout << endl;
	}
	~AVL() {
		Destroy(root);
	}
};

template <typename T>
class AVLgroup {
	class Gnode {
	public:
		T data;
		singlylist* userptrs;
		Gnode* left;
		Gnode* right;
		int height;
		Gnode(T d = 0, user* p = nullptr, Gnode* l = nullptr, Gnode* r = nullptr) {
			data = d;
			userptrs = new singlylist();
			//this singlylist pointer will be deleted in AVLgroup destructor & in some functions where a whole node is being deleted if list becomes empty due to deletion
			
			userptrs->insert(p);
			left = l;
			right = r;
			height = 0;
		}
		
	};
	Gnode* root;

public:
	AVLgroup() {
		root = nullptr;
	}

	int getheight(Gnode* r) {
		if (r == nullptr)
			return -1;
		else
			return r->height;
	}
	void rightRotate(Gnode*& x) {
		Gnode* y = x->left;
		x->left = y->right;
		y->right = x;

		x->height = 1 + max(getheight(x->left), getheight(x->right));
		y->height = 1 + max(getheight(y->left), x->height);
		x = y;

	}
	void leftRotate(Gnode*& x) {
		Gnode* y = x->right;
		x->right = y->left;
		y->left = x;

		x->height = 1 + max(getheight(x->left), getheight(x->right));
		y->height = 1 + max(getheight(y->right), x->height);
		x = y;
	}
	void DoubleRR(Gnode*& x) {
		leftRotate(x->left);
		rightRotate(x);
	}
	void DoubleRL(Gnode*& x) {
		rightRotate(x->right);
		leftRotate(x);
	}
	Gnode* searchnode(T d, Gnode*& r) {
		if (r == nullptr)
			return nullptr;
		if (r->data == d)
			return r;
		else if (r->data > d)
			return searchnode(d, r->left);
		else if (r->data < d)
			return searchnode(d, r->right);
	}
	void insert(const T& d, user* ptr, Gnode*& r) {
		if (r == nullptr) {
			r = new Gnode(d, ptr, nullptr, nullptr);
			return;
		}
		if (d < r->data) {
			insert(d, ptr, r->left);
			if (getheight(r->left) - getheight(r->right) == 2) {
				if (d < r->left->data)
					rightRotate(r);
				else
					DoubleRR(r);
			}
		}
		else if (d > r->data) {
			insert(d, ptr, r->right);
			if (getheight(r->left) - getheight(r->right) == -2) {
				if (d > r->right->data)
					leftRotate(r);
				else
					DoubleRL(r);
			}
		}
		r->height = 1 + max(getheight(r->left), getheight(r->right));
	}
	void insert(const T& d, user* ptr) {
		Gnode* n = searchnode(d,root);
		if (n == nullptr)
			insert(d, ptr, root);
		else
			n->userptrs->insert(ptr);
		
	}

	T getmax(Gnode* r,singlylist*& s) {
		if (r->right == nullptr)
		{
			s = r->userptrs;
			return r->data;
		}
		else
			return getmax(r->right,s);
	}
	int BalanceF(Gnode* r) {
		return (getheight(r->left) - getheight(r->right));
	}
	void deletegroup(Gnode*& r, T d)
	{
		if (r)
		{
			if (r->data == d)
			{
				if (r->left == nullptr && r->right == nullptr)
				{
					delete r;
					r = nullptr;
					return;
				}
				else if (r->left == nullptr)
				{
					Gnode* temp = r->right;
					delete r;
					r = temp;
				}
				else if (r->right == nullptr)
				{
					Gnode* temp = r->left;
					delete r;
					r = temp;
				}
				else
				{
					singlylist* s;
					T temp = getmax(r->left,s);
					r->data = temp;
					r->userptrs = s;
					deletegroup(r->left, temp);

				}
			}
			else if (r->data > d)
			{
				deletegroup(r->left, d);
			}
			else
				deletegroup(r->right, d);
		}

		if (root == nullptr)
			return;

		r->height = 1 + max(getheight(r->left), getheight(r->right));

		int balance = BalanceF(r);

		if (balance == 2)
		{
			if (BalanceF(r->left) >= 0)
			{
				rightRotate(r);
			}
			else
				DoubleRR(r);
		}
		if (balance == -2)
		{
			if (BalanceF(r->right) <= 0)
			{
				leftRotate(r);
			}
			else
				DoubleRL(r);
		}

	}
	void deletegroup(T d) {
		deletegroup(root, d);
	}

	singlylist* getdeluserslist(T d) {
		Gnode* n = searchnode(d,root);
		if (n == nullptr)
			return nullptr;
		else
		{
			singlylist* s= n->userptrs;
			deletegroup(root, d);
			return s;
		}
	}
	singlylist* getuserslist(T d) {
		Gnode* n = searchnode(d, root);
		if (n == nullptr)
			return nullptr;
		else
			return n->userptrs;
	}
	void deletecertainuser(T d,user* s) {
		Gnode* n = searchnode(d,root);
		if (n == nullptr)
			return;
		n->userptrs->removeuser(s);
		if (n->userptrs->isempty())
			deletegroup(d);
	}
	void printusers(T d) {
		Gnode* n = searchnode(d,root);
		if (n == nullptr)
			cout << "Not Found" << endl;
		else
			n->userptrs->print();
	}
	void print(Gnode* r) {
		if (r != nullptr) {
			print(r->left);
			cout << "->" << r->data;
			print(r->right);
		}
	}
	void print() {
		print(root);
		cout << endl;
	}
	void Destroy(Gnode* r) {
		if (r != nullptr) {
			Destroy(r->left);
			Destroy(r->right);
			if (r->userptrs)
				delete r->userptrs;
			delete r;
		}
	}
	~AVLgroup() {
		Destroy(root);
	}
};

class complaint {
public:

	int compID;
	int userID;
	string text;
	string type;
	bool prSet;    //1 for highest ,0 for normal
	static int IDgenerator;

	complaint(int cid = 0, int uid = 0, string t = "", string ty = "") {
		compID = cid;
		userID = uid;
		text = t;
		type = ty;
		prSet = 0;
	}

};

int complaint::IDgenerator = 0;
template <typename T>
class AVLComplaints {
	class Cnode {
	public:
		T data;
		vector<complaint> allcomplaints;
		Cnode* left;
		Cnode* right;
		int height;
		Cnode(T d , complaint& c, Cnode* l = nullptr, Cnode* r = nullptr) {
			data = d;
			allcomplaints.push_back(c);
			left = l;
			right = r;
			height = 0;
		}

	};
	Cnode* root;

public:
	AVLComplaints() {
		root = nullptr;
	}

	int getheight(Cnode* r) {
		if (r == nullptr)
			return -1;
		else
			return r->height;
	}
	void rightRotate(Cnode*& x) {
		Cnode* y = x->left;
		x->left = y->right;
		y->right = x;

		x->height = 1 + max(getheight(x->left), getheight(x->right));
		y->height = 1 + max(getheight(y->left), x->height);
		x = y;

	}
	void leftRotate(Cnode*& x) {
		Cnode* y = x->right;
		x->right = y->left;
		y->left = x;

		x->height = 1 + max(getheight(x->left), getheight(x->right));
		y->height = 1 + max(getheight(y->right), x->height);
		x = y;
	}
	void DoubleRR(Cnode*& x) {
		leftRotate(x->left);
		rightRotate(x);
	}
	void DoubleRL(Cnode*& x) {
		rightRotate(x->right);
		leftRotate(x);
	}
	Cnode* searchnode(int d, Cnode*& r) {
		if (r == nullptr)
			return nullptr;
		if (r->data == d)
			return r;
		else if (r->data > d)
			return searchnode(d, r->left);
		else if (r->data < d)
			return searchnode(d, r->right);
	}
	void insert(const T& d, complaint& c, Cnode*& r) {
		if (r == nullptr) {
			r = new Cnode(d, c, nullptr, nullptr);
			return;
		}
		if (d < r->data) {
			insert(d, c, r->left);
			if (getheight(r->left) - getheight(r->right) == 2) {
				if (d < r->left->data)
					rightRotate(r);
				else
					DoubleRR(r);
			}
		}
		else if (d > r->data) {
			insert(d, c, r->right);
			if (getheight(r->left) - getheight(r->right) == -2) {
				if (d > r->right->data)
					leftRotate(r);
				else
					DoubleRL(r);
			}
		}
		r->height = 1 + max(getheight(r->left), getheight(r->right));
	}
	void insert(const T& d, complaint& c) {
		Cnode* n = searchnode(d, root);
		if (n == nullptr)
			insert(d, c, root);
		else
			n->allcomplaints.push_back(c);

	}

	T getmax(Cnode* r, vector<complaint>& s) {
		if (r->right == nullptr)
		{
			s = r->allcomplaints;
			return r->data;
		}
		else
			return getmax(r->right, s);
	}
	int BalanceF(Cnode* r) {
		return (getheight(r->left) - getheight(r->right));
	}
	void deletegroup(Cnode*& r, T d)
	{
		if (r)
		{
			if (r->data == d)
			{
				if (r->left == nullptr && r->right == nullptr)
				{
					delete r;
					r = nullptr;
					return;
				}
				else if (r->left == nullptr)
				{
					Cnode* temp = r->right;
					delete r;
					r = temp;
				}
				else if (r->right == nullptr)
				{
					Cnode* temp = r->left;
					delete r;
					r = temp;
				}
				else
				{
					vector<complaint> s;
					T temp = getmax(r->left, s);
					r->data = temp;
					r->allcomplaints = s;
					deletegroup(r->left, temp);

				}
			}
			else if (r->data > d)
			{
				deletegroup(r->left, d);
			}
			else
				deletegroup(r->right, d);
		}

		if (root == nullptr)
			return;

		r->height = 1 + max(getheight(r->left), getheight(r->right));

		int balance = BalanceF(r);

		if (balance == 2)
		{
			if (BalanceF(r->left) >= 0)
			{
				rightRotate(r);
			}
			else
				DoubleRR(r);
		}
		if (balance == -2)
		{
			if (BalanceF(r->right) <= 0)
			{
				leftRotate(r);
			}
			else
				DoubleRL(r);
		}

	}
	void deletegroup(T d) {
		deletegroup(root, d);
	}

	vector<complaint>& getcomplist(T d) {
		Cnode* n = searchnode(d, root);
		vector<complaint> s;
		if (n)
			s = n->allcomplaints;
		return s;
	}

	void deletecertaincomp(T d, complaint& c) {
		Cnode* n = searchnode(d, root);
		if (n == nullptr)
			return;
		for(int i = 0; i < n->allcomplaints.size() - 1; i++) {
			if (n->allcomplaints[i].compID == c.compID) {
				n->allcomplaints.erase(n->allcomplaints.begin() + i);
			}
		}
		if (n->allcomplaints.empty())
			deletegroup(d);
	}
	void printcomplaints(T d) {
		Cnode* n = searchnode(d, root);
		if (n == nullptr)
			return;
		else
		{
			cout << "Complaints registered by user Id " << n->data << " : " << endl;
			for (int i = 0; i < n->allcomplaints.size(); i++) {
				cout << "Complaint ID: " << n->allcomplaints[i].compID << endl;
				cout << "Issue: " << n->allcomplaints[i].text << endl << endl;
			}
		}
	}
	void Destroy(Cnode* r) {
		if (r != nullptr) {
			Destroy(r->left);
			Destroy(r->right);
			delete r;
		}
	}
	~AVLComplaints() {
		Destroy(root);
	}
};


class priorityHeap {
	vector<complaint> arr;
	AVLComplaints<int> usercompInd;

	bool compare(complaint& a, complaint& b) {
		if (b.prSet)
			return false;
		if (a.type == b.type) {
			if (b.compID < a.compID)
				return false;
			else return true;
		}
		else {
			if (a.type == "platinum")
				return true;
			else if ((a.type == "gold") && ((b.type == "silver") || (b.type == "new") || (b.type == "regular")))
				return true;
			else if ((a.type == "silver") && ((b.type == "new") || (b.type == "regular")))
				return true;
			else if ((a.type == "new") && (b.type == "regular"))
				return true;
			else
				return false;
		}
	}

	void bubbleup(int i) {
		if (i <= 1)
			return;
		if (compare(arr[i / 2], arr[i]))
			return;
		swap(arr[i / 2], arr[i]);
		bubbleup(i / 2);
	}

	void bubbledown(int i) {
		int left = 2 * i;
		int right = 2 * i + 1;
		int max = i;

		if (left < arr.size() && compare(arr[left], arr[max])) {
			max = left;
		}
		if (right < arr.size() && compare(arr[right], arr[max])) {
			max = right;
		}
		if (max != i) {
			swap(arr[i], arr[max]);
			bubbledown(max);
		}
	}

public:
	priorityHeap() {
		arr.push_back(complaint());
	}

	void registercomp(complaint& comp) {
		arr.push_back(comp);
		bubbleup(arr.size() - 1);
		usercompInd.insert(comp.userID, comp);

		cout << "\nYour complaint is registered with complaint ID "<<comp.compID << endl << endl;
	}
	void servicecomp() {
		cout << "\nProcessing highest priority complaint...." << endl;
		if (arr.size()==1) {
			cout << "No complaint registered" << endl;
			return;
		}
		complaint c = arr[1];
		arr[1] = arr[arr.size() - 1];
		arr.pop_back();
		bubbledown(1);
		usercompInd.deletecertaincomp(c.userID, c);
		cout << "Complaint " << c.compID << " by user " << c.userID << " is processed" << endl;
	}

	void displaycompByID(int id) {

		usercompInd.printcomplaints(id);

	}
	complaint* getcomplaint(int id) {
		for (int i = 1; i < arr.size() ; i++) {
			if (arr[i].compID == id)
				return &arr[i];
		}
		return nullptr;
	}
	void increasepriority(complaint* c) {
		if (c == nullptr) {
			cout << "No complaint registered with this id" << endl;
			return;
		}
		for (int i = 1; i < arr.size();i++) {
			if (&arr[i] == c) {
			    arr[i].type = "platinum"; 
				arr[i].prSet = 1;
				bubbleup(i);
				arr[i].prSet = 0;
				cout << "Complaint " << arr[i].compID << " by user ID " << arr[i].userID << " is at highest priority now" << endl;
				return;
			}
		}
	}
	void displayallcomplaints() {
		cout << "All registered complaints: " << endl;
		for (int i = 1; i < arr.size(); i++) {
			cout << "Complaint ID_" << arr[i].compID << endl;
			cout << "By user " << arr[i].userID << endl;
			cout << "Issues: " << arr[i].text << endl << endl;

		}
	}

};

class userslist {

	user* head;
	user* tail;
	AVL<int> idIndex;
	AVL<string> nameIndex;
	AVL<string> emailIndex;
	AVLgroup<string> countryGroup;
	AVLgroup<string> typeGroup;

public:

	userslist()
	{
		head = new user();
		tail = new user();
		head->next = tail;
		tail->prev = head;
	}

	void insertuser(int id, string n, string em, string c, string t) {
		if (id == 0) {
			srand(time(0));
			user::userIDgen += rand() % 20 + 1;
			id = user::userIDgen;
		}
		user* newUser = new user(id, n, em, c, t, nullptr, nullptr);
		user* closestUser = idIndex.searchindexforinsertion(id);

		if (closestUser == nullptr) {
			newUser->next = head->next;
			newUser->prev = head;
			head->next->prev = newUser;
			head->next = newUser;
		}
		else {
			newUser->next = closestUser->next;
			newUser->prev = closestUser;
			closestUser->next->prev = newUser;
			closestUser->next = newUser;
		}

		idIndex.insert(id, newUser);
		nameIndex.insert(n, newUser);
		emailIndex.insert(em, newUser);
		countryGroup.insert(c, newUser);
		typeGroup.insert(t, newUser);

	}
	void registerusers() {
		string n, em, t, c;
		cout << "Enter your username: ";
		cin >> n;
		while (nameIndex.search(n)) {
			cout << "Username already exists.Select another name: ";
			cin >> n;
		}
		cout << "Enter your email: ";
		cin >> em;
		while (emailIndex.search(n)) {
			cout << "Email already exists.Register by another email:  ";
			cin >> em;
		}
		cout << "Enter your country: ";
		cin >> c;
		cout << "Enter account type: ";
		cin >> t;
		srand(time(0));
		user::userIDgen += rand() % 20 + 1;
		insertuser(user::userIDgen, n, em, "UK", t);
		cout << "User registered successfully !" << endl;
	}
	void print() {
		user* c = head->next;
		while (c != tail) {
			c->print();
			c = c->next;
		}
	}
	bool searchuserid(int d) {
		user* s = idIndex.search(d);
		if (s == nullptr) {
			cout << "User Id not found " << endl;
			return false;
		}
		else {
			cout << "User found " << endl;
			s->print();
			return true;
		}
	}
	bool searchusername(string n) {
		user* s = nameIndex.search(n);
		if (s == nullptr) {
			cout << "User Name not found " << endl;
			return false;
		}
		else {
			cout << "User found " << endl;
			s->print();
			return true;
		}
	}
	bool searchuseremail(string e) {
		user* s = emailIndex.search(e);
		if (s == nullptr) {
			cout << "User email not found " << endl;
			return false;
		}
		else {
			cout << "User found " << endl;
			s->print();
			return true;
		}
	}
	bool deleteuserid(int d) {
		user* s = idIndex.search(d);
		if (s == nullptr) {
			cout << "User Id not found " << endl;
			return false;
		}
		else {
			if (s->prev)
				s->prev->next = s->next;
			if (s->next)
				s->next->prev = s->prev;
			idIndex.deletee(d);
			nameIndex.deletee(s->userName);
			emailIndex.deletee(s->email);
			countryGroup.deletecertainuser(s->country, s);
			typeGroup.deletecertainuser(s->type, s);
			delete s;
			cout << "User Id Deleted" << endl;
			return true;
		}
	}
	void deleteuser(user* s) {
		if (s->prev)
			s->prev->next = s->next;
		if (s->next)
			s->next->prev = s->prev;
		idIndex.deletee(s->userID);
		nameIndex.deletee(s->userName);
		emailIndex.deletee(s->email);
		delete s;
	}
	bool deleteusername(string n) {
		user* s = nameIndex.search(n);
		if (s == nullptr) {
			cout << "User Name not found " << endl;
			return false;
		}
		else {
			if (s->prev)
				s->prev->next = s->next;
			if (s->next)
				s->next->prev = s->prev;
			nameIndex.deletee(n);
			idIndex.deletee(s->userID);
			emailIndex.deletee(s->email);
			countryGroup.deletecertainuser(s->country, s);
			typeGroup.deletecertainuser(s->type, s);
			delete s;

			cout << "User Name Deleted" << endl;
			return true;
		}
	}
	bool deleteuseremail(string e) {
		user* s = emailIndex.search(e);
		if (s == nullptr) {
			cout << "User email not found " << endl;
			return false;
		}
		else {
			if (s->prev)
				s->prev->next = s->next;
			if (s->next)
				s->next->prev = s->prev;
			emailIndex.deletee(e);
			nameIndex.deletee(s->userName);
			idIndex.deletee(s->userID);
			countryGroup.deletecertainuser(s->country, s);
			typeGroup.deletecertainuser(s->type, s);
			delete s;
			cout << "User email Deleted" << endl;
			return true;
		}
	}
	void deletecountrygroup(string d) {
		singlylist* ulist;
		ulist = countryGroup.getdeluserslist(d);
		if (ulist == nullptr) {
			cout << "No user under this country" << endl;
			return;
		}
		else {
			while (!(ulist->isempty())) {
				user* s = ulist->getdelFirstuser();
				typeGroup.deletecertainuser(s->type, s);
				deleteuser(s);
			}
			if (ulist)
				delete ulist;
			cout << "Users users deleted that belong to " << d << endl;
		}

	}
	void deletetypegroup(string d) {
		singlylist* ulist;
		ulist = typeGroup.getdeluserslist(d);
		if (ulist == nullptr) {
			cout << "No user under this country" << endl;
			return;
		}
		else {
			while (!(ulist->isempty())) {
				user* s = ulist->getdelFirstuser();
				countryGroup.deletecertainuser(s->country, s);
				deleteuser(s);	
			}
			if (ulist)
				delete ulist;
			cout << "All users of type " << d << " deleted" << endl;
		}

	}
	void printindices() {
		cout << "\nIndices on ID:" << endl;
		idIndex.print();
		cout << "Indices on Username:" << endl;
		nameIndex.print();
		cout << "Indices on Email:" << endl;
		emailIndex.print();
	}
	void printgroupindices() {
		cout << "\nGroup Indices on Country:" << endl;
		countryGroup.print();
		cout << "Group Indices on Type:" << endl;
		typeGroup.print();
	}
	void listcountryusers(string d) {
		countryGroup.printusers(d);
	}
	void listtypeusers(string d) {
		typeGroup.printusers(d);
	}
	void registercomplaint(priorityHeap& queue) {
		
		int id;
		cout << "Enter your user Id:";
		cin >> id;
		user* s = idIndex.search(id);
		if (!s) {
			cout << "User Not Registered" << endl;
			return;
		}
		string t;
		cout << "Submit complaint: ";
		cin.ignore();
		getline(cin, t);
		srand(time(0));
		complaint::IDgenerator += rand() % 50 + 1;
		complaint c(complaint::IDgenerator, id, t, s->type);
		queue.registercomp(c);
	}
	void printcompbycountry(string c,priorityHeap& queue) {
		singlylist* slist = countryGroup.getuserslist(c);
		if (slist == nullptr) {
			cout << "No user of this country registered" << endl;
			return;
		}
		for(int i=0;i < slist->getnodecount();i++)
		{
			user* s = slist->getindex(i);
			queue.displaycompByID(s->userID);
		}
	}
	~userslist()
	{
		while (head->next != tail)
		{
			user* temp = head->next;
			head->next = temp->next; temp->next->prev = head;
			delete temp;
		}
		delete head;
		delete tail;
	}
};


int main() {
	
	userslist mylist;
	mylist.insertuser(0, "Ali", "ali98@gmail.com", "UK", "gold");
	mylist.insertuser(0, "Sana", "sana24@gmail.com", "USA", "platinum");
	mylist.insertuser(0, "Amna", "amna93@gmail.com", "UK", "silver");
	mylist.insertuser(0, "Saad", "saad56@gmail.com", "Canada", "diamond");
	mylist.insertuser(0, "Isha", "isha77@gmail.com", "USA", "gold");

	{
		cout << "Question 01:" << endl << endl;
		int choice;
		
		while (true) {
			cout << "0 - to exit\n1 - to register user\n2 - to search user by ID\n3 - to delete user by ID\n4 - to view all registered users\nEnter :";
			cin >> choice;
			cout << "_________________________________" << endl;
			if (choice == 0)
			{
				system("cls");
				break;
			}
			if (choice == 1)
				mylist.registerusers();
			else if (choice == 2) {
				cout << "\nEnter User ID to search : ";
				cin >> choice;
				mylist.searchuserid(choice);
			}
			else if (choice == 3) {
				cout << "\nEnter User ID to delete : ";
				cin >> choice;
				mylist.deleteuserid(choice);
			}
			else if (choice == 4) {
				cout << "Registered Users List :" << endl;
				mylist.print();
			}
			cout << "Enter 1 to go back to menu..." << endl;
			cin >> choice;
			system("cls");
		}
	}

	{
		cout << "Question 02:" << endl << endl;
		string n;
		int choice;

		while (true) {
			cout << "0 - to exit\n1 - to register user\n2 - to search user by name\n3 - to delete user by name\n4 - to search user by email\n5 - to delete user by email\n6 - to print indices\n7 - to view all registered users\nEnter :";
			cin >> choice;
			cout << "_________________________________" << endl;
			if (choice == 0)
			{
				system("cls");
				break;
			}
			if (choice == 1)
				mylist.registerusers();
			else if (choice == 2) {
				cout << "\nEnter User name to search : ";
				cin >> n;
				mylist.searchusername(n);
			}
			else if (choice == 3) {
				cout << "\nEnter User Name to delete : ";
				cin >> n;
				mylist.deleteusername(n);
			}
			else if (choice == 4) {
				cout << "\nEnter User email to search : ";
				cin >> n;
				mylist.searchuseremail(n);
			}
			else if (choice == 5) {
				cout << "\nEnter User email to delete : ";
				cin >> n;
				mylist.deleteuseremail(n);
			}
			else if (choice == 6) {
				mylist.printindices();
			}
			else if (choice == 7) {
				cout << "Registered Users List :" << endl;
				mylist.print();
			}
			cout << "Enter 1 to go back to menu..." << endl;
			cin >> choice;
			system("cls");
		}
	}

	{
		cout << "Question 03:" << endl << endl;
		string n;
		int choice;

		while (true) {
			cout << "0 - to exit\n1 - to register user\n2 - to list all users of a country\n3 - to delete all users of a country\n4 - to list all users of a type\n5 - to delete all users of a type\n6 - to print group indices\n7 - to view all registered users\nEnter :";
			cin >> choice;
			cout << "_________________________________" << endl;
			if (choice == 0)
			{
				system("cls");
				break;
			}
			if (choice == 1)
				mylist.registerusers();
			else if (choice == 2) {
				cout << "\nEnter Country : ";
				cin >> n;
				mylist.listcountryusers(n);
			}
			else if (choice == 3) {
				cout << "\nEnter Country  : ";
				cin >> n;
				mylist.deletecountrygroup(n);
			}
			else if (choice == 4) {
				cout << "\nEnter type : ";
				cin >> n;
				mylist.listtypeusers(n);
			}
			else if (choice == 5) {
				cout << "\nEnter type : ";
				cin >> n;
				mylist.deletetypegroup(n);
			}
			else if (choice == 6) {
				mylist.printgroupindices();
			}
			else if (choice == 7) {
				cout << "Registered Users List :" << endl;
				mylist.print();
			}
			cout << "Enter 1 to go back to menu..." << endl;
			cin >> choice;
			system("cls");
		}
	}

	priorityHeap compQueue;
	{
		cout << "Question 04:" << endl << endl;
		string n;
		int choice;

		while (true) {
			cout << "0 - to exit\n1 - to register user\n2 - to register complaint\n3 - to service complaint\n4 - to increase priority of a complaint\n5 - to view all complaints of a user\n6 - to view all complaints of a country\n7 - to view all registered users\n8 - to view all registered Complaints\nEnter :";
			cin >> choice;
			cout << "________________________________" << endl;
			if (choice == 0)
			{
				system("cls");
				break;
			}
			if (choice == 1)
				mylist.registerusers();
			else if (choice == 2) {
				mylist.registercomplaint(compQueue);
			}
			else if (choice == 3) {
				compQueue.servicecomp();
			}
			else if (choice == 4) {
				cout << "Enter complaint id to increase priority: ";
				cin >> choice;
				complaint* c = compQueue.getcomplaint(choice);
				compQueue.increasepriority(c);
			}
			else if (choice == 5) {
				cout << "Enter user Id to see complaints: ";
				cin >> choice;
				compQueue.displaycompByID(choice);
			}
			else if (choice == 6) {
				cout << "Enter country to see complaints: ";
				cin >> n;
				mylist.printcompbycountry(n, compQueue);
			}
			else if (choice == 7) {
				cout << "Registered Users List :" << endl;
				mylist.print();
			}
			else if (choice == 8) {
				compQueue.displayallcomplaints();
			}
			cout << "Enter 1 to go back to menu..." << endl;
			cin >> choice;
			system("cls");
		}
	}

	system("pause");
	return 0;
}

