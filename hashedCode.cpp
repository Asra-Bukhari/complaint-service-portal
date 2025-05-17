#include<iostream>
#include<string>
#include<list>
#include<algorithm>
#include<queue>
using namespace std;

class User
{
public:
	int UserId;
	string UserName;
	string Email;
	string Country;
	string Type;

	User(int id = -1, string name = " ", string email = " ", string country = " ", string type = " ")
	{
		UserId = id;
		UserName = name;
		Email = email;
		Country = country;
		Type = type;

	}

	~User()
	{

	}

};

class Complaint
{
private:
	static int NextComplaintId;
public:
	int UserId;
	int ComplaintId;
	string Type;
	string Text;

	Complaint(int id, string type, string txt)
	{
		UserId = id;
		ComplaintId = NextComplaintId;
		NextComplaintId++;
		Text = txt;
		Type = type;
	}
	int GetPriority() const {
		if (Type == "Platinum")
			return 5;
		if (Type == "Gold")
			return 4;
		if (Type == "Silver")
			return 3;
		if (Type == "Regular")
			return 2;
		return 1;
	}
	void Print()
	{
		cout << "Complain Id : " << ComplaintId << endl;
		cout << "User Id : " << UserId << endl;
		cout << "Type : " << Type << endl;
		cout << "Complaint : " << Text << endl;
	}
	void Display()
	{
		cout << "Complain Id : " << ComplaintId << endl;
		cout << "User Id : " << UserId << endl;
		cout << "Type : " << Type << endl;
		cout << "Complaint : " << Text << endl;
	}
};
int Complaint::NextComplaintId = 0;


template<class T>
class HashTableforID
{
private:
	class Node
	{
	public:
		int key;
		T data;
		Node()
		{
			key = -1;
			data = nullptr;
		}

	};

	int TableSize;  // Size of the hash table (odd number)
	Node* Table;     // Array to store elements
	int CurrentElementsCount;

	void resizeTable()
	{


		int oldSize = TableSize;
		TableSize *= 2;
		Node* OldTable = Table;
		Table = new Node[TableSize];
		CurrentElementsCount = 0;

		for (int i = 0; i < TableSize; i++) {
			Table[i].key = -1;
		}

		for (int i = 0; i < oldSize; i++) {
			if (OldTable[i].key != -1) {
				add(OldTable[i].key, OldTable[i].data);
			}
		}

		delete[] OldTable;
	}
	int computeHash(int key)
	{
		return key % TableSize;
	}

public:
	HashTableforID(int size = 13)
	{
		TableSize = size;
		CurrentElementsCount = 0;
		Table = new Node[TableSize];
		for (int i = 0; i < TableSize; i++) {
			Table[i].key = -1;
		}
	}
	void add(int key, T node)
	{
		if ((double)CurrentElementsCount / TableSize > 0.5) {
			resizeTable();
		}

		int hashIndex = computeHash(key);
		int secondHash = 1 + key % (TableSize - 2);

		for (int i = 0;; i++)
		{
			int index;

			index = (hashIndex + i * secondHash) % TableSize;


			if (Table[index].key == -1)
			{
				Table[index].key = key;
				Table[index].data = node;
				CurrentElementsCount++;
				break;
			}
		}
	}
	void remove(int key) {
		int hashIndex = computeHash(key);
		int secondHash = 1 + key % (TableSize - 2);
		for (int i = 0;; i++) {
			int index;
			index = (hashIndex + i * secondHash) % TableSize;


			if (Table[index].key == -1) {
				cout << "Error: UserId " << key << " not found." << endl;
				return;
			}

			if (Table[index].key == key) {
				Table[index].key = -1;
				Table[index].data = nullptr;
				CurrentElementsCount--;
				cout << "UserId " << key << " removed successfully." << endl;
				break;
			}
		}
	}
	T get(int key)
	{
		int hashIndex = computeHash(key);
		int secondHash = 1 + key % (TableSize - 2);

		for (int i = 0;; i++) {
			int index;
			index = (hashIndex + i * secondHash) % TableSize;


			if (Table[index].key == -1) {
				cout << "Error: Key " << key << " not found." << endl;
				return nullptr;
			}

			if (Table[index].key == key) {
				return Table[index].data;
			}
		}
	}

	~HashTableforID()
	{
		delete[] Table;
	}
};


template <class T>
class HashTableforchaining
{
private:
	class Node
	{
	public:
		string key;
		T data;
		Node* next;

		Node()
		{
			key = " ";
			data = nullptr;
			next = nullptr;
		}
		Node(string k, T d)
		{
			key = k;
			data = d;
			next = nullptr;
		}


	};

	int capacity;
	Node** array;

	int computeHash(const string& key)
	{
		int hashCode = 0;
		int factor = 1;
		for (int i = 0; i < key.length(); i++)
		{
			hashCode = (hashCode + key[i] * factor) % capacity;
			factor = (factor * 33) % capacity;
		}
		return (hashCode + capacity) % capacity;
	}

public:
	HashTableforchaining(int tableSize = 13) : capacity(tableSize)
	{
		array = new Node * [capacity];
		for (int i = 0; i < capacity; i++) {
			array[i] = nullptr;
		}
	}
	void add(const string& key, T value)
	{
		int index = computeHash(key);
		Node* newEntry = new Node(key, value);

		if (array[index] == nullptr) {
			array[index] = newEntry;
		}
		else {
			Node* current = array[index];
			while (current->next != nullptr) {
				current = current->next;
			}
			current->next = newEntry;
		}
	}
	void remove(const string& key) {
		int index = computeHash(key);
		Node* current = array[index];
		Node* prev = nullptr;

		while (current != nullptr && current->key != key) {
			prev = current;
			current = current->next;
		}

		if (current == nullptr) {
			cout << "Key not found.\n";
			return;
		}

		if (prev == nullptr) {
			array[index] = current->next;
		}
		else {
			prev->next = current->next;
		}

		delete current;
	}
	T get(const string& key) {
		int index = computeHash(key);
		Node* current = array[index];

		while (current != nullptr) {
			if (current->key == key) {
				return current->data;
			}
			current = current->next;
		}

		cout << "Key not found.\n";
		return nullptr;
	}
	void DisplayIndices()
	{
		if (array == nullptr)
		{
			cout << "Index is Empty.\n";
			return;
		}
		Node* current;
		for (int i = 0; i < capacity; i++)
		{
			if (array[i] != nullptr)
			{
				current = array[i];

				while (current != nullptr) {
					current->data->Print();
					current = current->next;
				}

			}
		}
	}
	void DeleteIndices()
	{
		for (int i = 0; i < capacity; i++)
		{
			Node* current = array[i];
			while (current != nullptr) {
				Node* next = current->next;
				delete current;
				current = next;
			}
			array[i] = nullptr;
		}
		delete[] array;
		array = nullptr;

	}

	~HashTableforchaining() {
		if (array == nullptr)
		{
			return;
		}
		for (int i = 0; i < capacity; i++) {
			Node* current = array[i];
			while (current != nullptr) {
				Node* next = current->next;
				delete current;
				current = next;
			}
		}
		delete[] array;
		array = nullptr;
	}
};
template<class T1, class T2>
class HashTableforGroup {
public:

	class Node {
	public:
		T1 key;
		T2 data;
		Node* next;

		Node() : key(" "), next(nullptr) {}
		Node(T1 k, T2 d) : key(k), data(d), next(nullptr) {}
	};

	int capacity;
	Node** array;
	int collisionMethod;

	int computeHash(string key) {
		int hashCode = 0;
		for (char c : key) {
			hashCode = (hashCode * 31 + c) % capacity;
		}
		return hashCode;
	}
	int computeHash(int key)
	{
		return key % capacity;
	}

	int probeLinear(int hashIndex, int i) {
		return (hashIndex + i) % capacity;
	}

	int probeQuadratic(int hashIndex, int i) {
		return (hashIndex + i * i) % capacity;
	}


	HashTableforGroup(int tableSize = 13, int method = 1) : capacity(tableSize), collisionMethod(method) {
		array = new Node * [capacity];
		for (int i = 0; i < capacity; i++) {
			array[i] = nullptr;
		}
	}



	void add(T1 key, T2 value) {
		int hashIndex = computeHash(key);
		for (int i = 0;; i++) {
			int index = -1;

			if (collisionMethod == 1) {
				index = probeLinear(hashIndex, i);
			}
			else if (collisionMethod == 2) {
				index = probeQuadratic(hashIndex, i);
			}

			Node* newEntry = new Node(key, value);

			if (array[index] == nullptr) {
				array[index] = newEntry;
				return;
			}
			else if (array[index]->key == key) {
				Node* current = array[index];
				while (current->next != nullptr) {
					current = current->next;
				}
				current->next = newEntry;
				return;
			}
		}
	}
	void removecomplaint(int key1, int key2)
	{
		int hashIndex = computeHash(key1);
		for (int i = 0;; i++) {
			int index = -1;

			if (collisionMethod == 1) {
				index = probeLinear(hashIndex, i);
			}
			else if (collisionMethod == 2) {
				index = probeQuadratic(hashIndex, i);
			}

			Node* current = array[index];
			Node* prev = nullptr;

			while ((current != nullptr) && (current->key == key1) && (current->data->ComplaintId != key2))
			{
				prev = current;
				current = current->next;
			}

			if (current == nullptr) {
				std::cout << "Key not found.\n";
				return;
			}

			if (prev == nullptr) {
				array[index] = current->next;
			}
			else {
				prev->next = current->next;
			}

			delete current;
			return;
		}
	}
	void remove(T1 key, T2 node) {
		int hashIndex = computeHash(key);
		for (int i = 0;; i++) {
			int index = -1;

			if (collisionMethod == 1) {
				index = probeLinear(hashIndex, i);
			}
			else if (collisionMethod == 2) {
				index = probeQuadratic(hashIndex, i);
			}

			Node* current = array[index];
			Node* prev = nullptr;

			while ((current != nullptr) && (current->key == key) && (current->data != node))
			{
				prev = current;
				current = current->next;
			}

			if (current == nullptr) {
				std::cout << "Key not found.\n";
				return;
			}

			if (prev == nullptr) {
				array[index] = current->next;
			}
			else {
				prev->next = current->next;
			}

			delete current;
			return;
		}
	}
	Node* getlist(T1 key)
	{
		int hashIndex = computeHash(key);
		bool found = false;

		for (int i = 0;; i++) {
			int index = -1;

			if (collisionMethod == 1) {
				index = probeLinear(hashIndex, i);
			}
			else if (collisionMethod == 2) {
				index = probeQuadratic(hashIndex, i);
			}

			Node* current = array[index];


			while (current != nullptr) {
				if (current->key == key) {
					return current;
				}
				current = current->next;
			}

			if (!found)
			{
				std::cout << "Key not found.\n";
				return nullptr;
			}
		}
	}
	bool search(T1 key)
	{
		int hashIndex = computeHash(key);
		bool found = false;

		for (int i = 0;; i++) {
			int index = -1;

			if (collisionMethod == 1) {
				index = probeLinear(hashIndex, i);
			}
			else if (collisionMethod == 2) {
				index = probeQuadratic(hashIndex, i);
			}

			Node* current = array[index];


			while (current != nullptr) {
				if (current->key == key) {
					found = true;
					return found;
				}
				current = current->next;
			}

			if (!found)
			{
				std::cout << "Key not found.\n";
				return found;
			}
		}
	}
	void printallfor(T1 key) {

		int hashIndex = computeHash(key);
		bool found = false;

		for (int i = 0;; i++) {
			int index = -1;

			if (collisionMethod == 1) {
				index = probeLinear(hashIndex, i);
			}
			else if (collisionMethod == 2) {
				index = probeQuadratic(hashIndex, i);
			}

			Node* current = array[index];
			if (current != nullptr)
			{
				if (current->key == key)
				{
					cout << "Printing For " << key << endl;
				}
			}

			while (current != nullptr) {
				if (current->key == key) {
					found = true;
					current->data->Print();
				}
				current = current->next;
			}

			if (found) {
				return;
			}

			if (!found)
			{
				std::cout << "Key not found.\n";
				return;
			}
		}


	}

	void DisplayIndices() {
		if (array == nullptr) {
			std::cout << "Index is Empty.\n";
			return;
		}
		Node* current;
		for (int i = 0; i < capacity; i++) {
			if (array[i] != nullptr) {
				current = array[i];

				while (current != nullptr) {

					current->data->Print();
					current = current->next;
				}
			}
		}
	}

	void DeleteIndices()
	{

		for (int i = 0; i < capacity; i++) {
			Node* current = array[i];

			while (current != nullptr)
			{
				Node* next = current->next;
				delete current;
				current = next;
			}
			array[i] = nullptr;
		}
		delete[] array;
		array = nullptr;
	}
	~HashTableforGroup() {
		DeleteIndices();
	}
};
class PriorityQueue
{
private:
	vector<Complaint>heap;


	int Parent(int i)
	{
		return i / 2;
	}
	int LeftChild(int i)
	{
		return 2 * i;
	}
	int RightChild(int i)
	{
		return 2 * i + 1;
	}

	bool Compare(const Complaint& left, const Complaint& right)
	{
		if (left.GetPriority() == right.GetPriority())
		{
			return left.ComplaintId < right.ComplaintId;
		}
		else
		{
			return left.GetPriority() > right.GetPriority();
		}
	}

	void HeapifyDown(int i)
	{
		int left = LeftChild(i);
		int right = RightChild(i);
		int largest = i;

		if (left < heap.size() && Compare(heap[left], heap[largest]))
		{
			largest = left;
		}
		if (right < heap.size() && Compare(heap[right], heap[largest]))
		{
			largest = right;
		}
		if (largest != i)
		{
			swap(heap[i], heap[largest]);
			HeapifyDown(largest);
		}
	}
	void HeapifyUp(int i)
	{
		while (i > 1 && Compare(heap[i], heap[Parent(i)]))
		{

			swap(heap[i], heap[Parent(i)]);
			i = Parent(i);
		}
	}

public:
	PriorityQueue()
	{
		heap.push_back(Complaint(-1, "", ""));
	}
	void RegisterComplaint(const Complaint& complaint)
	{
		heap.push_back(complaint);
		HeapifyUp(heap.size() - 1);
	}
	int size()
	{
		return heap.size();
	}
	void DisplayAllIssues()
	{
		for (int i = 1; i < heap.size(); i++) {
			heap[i].Display();
			cout << "------------------------\n";
		}
	}
	Complaint ServiceComplaint()
	{
		Complaint c = heap[1];
		heap[1] = heap.back();
		heap.pop_back();
		if (heap.size() > 1)
		{
			HeapifyDown(1);
		}
		return c;

	}
	void DisplayHeap()
	{
		for (int i = 1; i < heap.size(); i++)
		{
			heap[i].Display();
		}
	}
	void IncreasePriority(int cmpid)
	{
		int i = 1;
		bool check = false;
		for (; i < heap.size(); i++)
		{
			if (heap[i].ComplaintId == cmpid)
			{
				check = true;
				break;
			}
		}
		if (check == true)
		{
			swap(heap[1], heap[i]);
			HeapifyDown(2);


		}
		else
		{
			cout << "Complain not found.\n";
		}
	}

};


class UsersDLL
{
private:
	class Node
	{
	public:
		User data;
		Node* prev;
		Node* next;
		Node(const User& user, Node* p = nullptr, Node* n = nullptr)
		{
			data = user;
			next = n;
			prev = p;
		}
		Node()
		{
			prev = nullptr;
			next = nullptr;
		}
		void Print()
		{
			cout << endl;
			cout << "User Id : " << data.UserId << endl;
			cout << "User Name : " << data.UserName << endl;
			cout << "User Email : " << data.Email << endl;
			cout << "User Country : " << data.Country << endl;
			cout << "User Type : " << data.Type << endl << endl;
		}
		void PrintUsername()
		{
			cout << "User Id : " << data.UserId;
		}
	};
	Node* head;
	Node* tail;
	PriorityQueue ComplaintQueue;
	HashTableforID<Node*>UserIdIndex;
	HashTableforchaining<Node*>EmailIndex;
	HashTableforchaining<Node*>UsernameIndex;
	HashTableforGroup<string, Node*>* CountryIndex;
	HashTableforGroup<string, Node*>* TypeIndex;
	HashTableforGroup<int, Complaint*>* ComplaintIndex;
public:
	UsersDLL()
	{
		head = new Node(User());
		tail = new Node(User());
		head->next = tail;
		tail->prev = head;
		CountryIndex = new HashTableforGroup<string, Node*>(13, 1);
		TypeIndex = new HashTableforGroup<string, Node*>(13, 2);
		ComplaintIndex = new HashTableforGroup<int, Complaint*>(13, 1);
	}
	void RegisterComplaint(int id, string txt)
	{
		if (UserIdIndex.get(id) != nullptr)
		{
			Node* temp = UserIdIndex.get(id);
			Complaint* complaint = new Complaint(id, temp->data.Type, txt);
			ComplaintIndex->add(id, complaint);
			ComplaintQueue.RegisterComplaint(*complaint);
		}
		else
		{
			cout << "User Not Found.\n";
		}
	}
	void ServiceComplaint()
	{
		if (ComplaintQueue.size() != 1)
		{
			Complaint temp = ComplaintQueue.ServiceComplaint();
			temp.Display();
			ComplaintIndex->removecomplaint(temp.UserId, temp.ComplaintId);
			cout << endl;
		}
		else
		{
			cout << "All Complaints Processed.\n";
		}

	}
	void DisplayComplaints(int id)
	{
		ComplaintIndex->printallfor(id);
	}
	void DisplayComplaintForCountry(string country)
	{
		if (CountryIndex->search(country) == true)
		{
			HashTableforGroup<string, Node*>::Node* current = CountryIndex->getlist(country);

			cout << "Dispalying Comments For Users With : " << country << endl << endl;
			while (current != nullptr)
			{
				(current->data)->PrintUsername();
				cout << endl;
				ComplaintIndex->printallfor(current->data->data.UserId);
				current = current->next;
			}

		}
		else
		{
			cout << "Country Not Found.\n";
		}
	}

	void PrintQueue()
	{
		ComplaintQueue.DisplayHeap();
	}
	void IncreasePriority(int cmpid)
	{
		ComplaintQueue.IncreasePriority(cmpid);
	}
	void PrintUserDetails(Node* n)
	{
		if (n != nullptr)
		{
			n->Print();
		}
	};
	void PrintAllUserDetails()
	{

		Node* temp = head->next;
		if (temp == tail)
		{
			cout << "NoUserFound.\n";
			return;
		}
		cout << "All USER DETAILS";
		while (temp != tail)
		{
			PrintUserDetails(temp);
			temp = temp->next;
		}

	}
	void PrintUsersForCountry(string country)
	{
		CountryIndex->printallfor(country);
	}
	void PrintUsersForType(string type)
	{
		TypeIndex->printallfor(type);
	}
	void DisplayIndices()
	{
		cout << "Username Index: \n";
		UsernameIndex.DisplayIndices();
		cout << endl;
		cout << "Email Index: \n";
		EmailIndex.DisplayIndices();
		cout << endl;
	}
	void DeleteIndices()
	{
		cout << "Deleting Username Index\n";
		UsernameIndex.DeleteIndices();
		cout << endl;
		cout << "Deleting Email Index\n";
		EmailIndex.DeleteIndices();
		cout << endl;
	}
	void DeleteGroupIndices()
	{
		cout << "Deleting Country Index\n";
		CountryIndex->DeleteIndices();
		cout << endl;
		cout << "Deleting Type Index\n";
		TypeIndex->DeleteIndices();
		cout << endl;
	}
	void DisplayGroupIndices()
	{
		cout << "Country Index: \n";
		CountryIndex->DisplayIndices();
		cout << endl;
		cout << "Type Index: \n";
		TypeIndex->DisplayIndices();
		cout << endl;
	}
	void InsertUser(const User& user)
	{

		Node* newNode = new Node(user, head, head->next);
		head->next->prev = newNode;
		head->next = newNode;
		UserIdIndex.add(user.UserId, newNode);
		UsernameIndex.add(user.UserName, newNode);
		EmailIndex.add(user.Email, newNode);
		CountryIndex->add(user.Country, newNode);
		TypeIndex->add(user.Type, newNode);

	}
	void SearchByUserId(int userid)
	{
		if (UserIdIndex.get(userid) != nullptr)
		{
			cout << "USER DETAILS";
			PrintUserDetails(UserIdIndex.get(userid));
		}
		else
		{
			cout << "UserNotFound.\n";
		}
	}
	void SearchByUserEmail(string email)
	{
		if (EmailIndex.get(email) != nullptr)
		{
			cout << "USER DETAILS";
			PrintUserDetails(EmailIndex.get(email));
		}
		else
		{
			cout << "UserNotFound.\n";
		}
	}
	void SearchByUserName(string name)
	{
		if (UsernameIndex.get(name) != nullptr)
		{
			cout << "USER DETAILS";
			PrintUserDetails(UsernameIndex.get(name));
		}
		else
		{
			cout << "UserNotFound.\n";
		}
	}
	void DeleteUser(int userid)
	{
		if (UserIdIndex.get(userid) != nullptr)
		{
			Node* temp = UserIdIndex.get(userid);
			EmailIndex.remove(temp->data.Email);
			UsernameIndex.remove(temp->data.UserName);
			CountryIndex->remove(temp->data.Country, temp);
			TypeIndex->remove(temp->data.Type, temp);
			UserIdIndex.remove(userid);
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete temp;
		}
		else
		{
			cout << "UserNotFound.\n";
		}
	}
	void DisplayPendingComp()
	{
		ComplaintQueue.DisplayAllIssues();
	}
	~UsersDLL()
	{
		Node* temp = head->next;
		while (temp != tail) {
			Node* toDelete = temp;
			temp = temp->next;
			delete toDelete;
		}
		delete head;
		delete tail;
	}
};

void DisplayMenu()
{
	cout << "\n--- Customer Support Management System ---\n";
	cout << "1. Add Customer\n";
	cout << "2. Register Issue\n";
	cout << "3. Process Next Issue\n";
	cout << "4. Display All Customers\n";
	cout << "5. Display Pending Issues\n";
	cout << "6. Exit\n";
	cout << "Enter your choice: ";
}

int main()
{
	UsersDLL supportSystem;
	int choice;

	supportSystem.InsertUser(User(25, "John Doe", "john@example.com", "USA", "New"));
	supportSystem.InsertUser(User(42, "Jane Smith", "jane@example.com", "Canada", "Platinum"));
	supportSystem.InsertUser(User(77, "Mike Johnson", "mike@example.com", "UK", "Gold"));

	do {
		DisplayMenu();
		cin >> choice;
		cin.ignore();

		switch (choice) {
		case 1: {
			int id;
			string name, email, country, type;

			cout << "Enter Customer ID: ";
			cin >> id;
			cin.ignore();

			cout << "Enter Name: ";
			getline(cin, name);

			cout << "Enter Email: ";
			getline(cin, email);

			cout << "Enter Country: ";
			getline(cin, country);

			cout << "Enter Customer Type: ";
			getline(cin, type);

			supportSystem.InsertUser(User(id, name, email, country, type));
			break;
		}
		case 2: {
			int customerId;
			string description;

			cout << "Enter Customer ID: ";
			cin >> customerId;
			cin.ignore();

			cout << "Enter Issue Description: ";
			getline(cin, description);
			supportSystem.RegisterComplaint(customerId, description);
			break;
		}
		case 3:
			supportSystem.ServiceComplaint();
			break;
		case 4:
			supportSystem.PrintAllUserDetails();
			break;
		case 5:
			supportSystem.DisplayPendingComp();
			break;
		case 6:
			cout << "Exiting the system...\n";
			break;
		default:
			cout << "Invalid choice. Please try again.\n";
		}
	} while (choice != 6);

	return 0;
}



