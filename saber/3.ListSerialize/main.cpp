#include <iostream>
#include <chrono>
#include "mylist.hpp"

// ========================================================
// testing to speed, method - call funcs in loop and compare times
#define TIME_NOW() std::chrono::steady_clock::now()
#define TIME_DIFF_MS(begin, end) std::chrono::duration_cast<std::chrono::milliseconds>((end) - (begin)).count()

// ========================================================
List* GenerateList(int count);
void Print(List* list);

// ========================================================
int main() {
	using namespace std;

	cout << "Serialize and Deserialize the \'List\' structure" << endl;

	cout << endl << "  SERIALIZE: ";
	List* list = GenerateList(7);
	Print(list);
	string time1, time2;

	if (FILE* file = fopen("list.bin", "wb")) {
		auto begin = TIME_NOW();
		list->Serialize(file);
		auto end = TIME_NOW();
		time1 = to_string(TIME_DIFF_MS(begin, end));
		fclose(file);
	}
	else {
		cout << "Cannot create / open file";
	}
	cout << endl;

	cout << endl << "DESERIALIZE: ";
	List* list2 = nullptr;
	if (FILE* file = fopen("list.bin", "rb")) {
		list2 = new List();
		auto begin = TIME_NOW();
		list2->Deserialize(file);
		auto end = TIME_NOW();
		time2 = to_string(TIME_DIFF_MS(begin, end));
		fclose(file);
		Print(list2);
	}
	else {
		cout << "Cannot open file";
	}
	cout << endl;

	cout << endl << "Finish";
	cout << endl << "serialized at " << time1 << " ms, deserialized at " << time2 << " ms";
	cout << ( (*list == *list2) ? " ok" : " FAIL");

	cout << endl;

	delete list;
	delete list2;

	return 0;
}

// ========================================================
List* GenerateList(int count) {
	std::srand (std::time(NULL));
	List* list = new List();
	for (int i = 0; i < count; ++i) {
		list->PushBack(std::to_string(i));
	}

	ListNode* node = list->Front();
	while (node) {
		int rand_index = std::rand() % count;
		node->rand = list->at(rand_index);
		node = node->next;
	}

	return list;
}

// ========================================================
void Print(List* list) {
	if (list == nullptr)
		return;

	ListNode* node = list->Front();
	for (int count = 0; node != nullptr; ++count) {
		if (count)
			std::cout << ", ";
		std::cout << "[";
		if (node->prev) std::cout << "*" << node->prev->data;
		std::cout << "; "<< node->data << "; ";
		if (node->next) std::cout << "*" << node->next->data;
		std::cout << "; ";
		if (node->rand) std::cout << "*" << node->rand->data;
		std::cout << "]";

		node = node->next;
	}
}