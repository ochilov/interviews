#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <string>

struct ListNode {
	ListNode();

	ListNode* prev;
	ListNode* next;
	ListNode* rand;

	std::string data;
};


class List {
public:
	List();
	~List();

	void Clear();

		  ListNode* Front();
	const ListNode* Front() const;
		  ListNode* Back ();
	const ListNode* Back () const;


	void PushFront(const std::string& data);
	void PushBack (const std::string& data);

	ListNode* at(int index);
	int IndexOf(const ListNode*) const;

	bool operator == (const List& b) const;

	void Serialize  (FILE* file);
	void Deserialize(FILE* file);

	void SerializeJSON  (FILE* file);
	void DeserializeJSON(FILE* file);

private:
	void DeserializeNodes(FILE* file);

	ListNode* head;
	ListNode* tail;
	int count;
};

#endif