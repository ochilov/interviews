#include "mylist.hpp"
#include <map>

// ========================================================
ListNode::ListNode() : prev(nullptr), next(nullptr), rand(nullptr) {

};


// ========================================================
List::List() : head(nullptr), tail(nullptr), count(0) {
};

List::~List() {
	Clear();
};

void List::Clear() {
	while (ListNode* node = this->head) {
		this->head = node->next;
		delete node;
	}
	this->tail = this->head;
	this->count = 0;
};

	  ListNode* List::Front()		{ return this->head; };
const ListNode* List::Front() const	{ return this->head; };
	  ListNode* List::Back ()		{ return this->tail; };
const ListNode* List::Back () const	{ return this->tail; };

void List::PushFront(const std::string& data) {
	ListNode* node = new ListNode();
	node->data = data;
	if (this->head != nullptr) {
		this->head->prev = node;
		node->next = this->head;
	}
	this->head = node;

	if (this->tail == nullptr) {
		this->tail = node;
	}
	this->count++;
};

void List::PushBack (const std::string& data) {
	ListNode* node = new ListNode();
	node->data = data;
	if (this->tail != nullptr) {
		this->tail->next = node;
		node->prev = this->tail;
	}
	this->tail = node;

	if (this->head == nullptr) {
		this->head = node;
	}
	this->count++;
};


ListNode* List::at(int index) {
	ListNode* node = this->head;
	for (int i = 0; i < index && node; ++i) {
		node = node->next;
	}
	return node;
};

int List::IndexOf(const ListNode* data) const {
	int index = -1;
	if (data == nullptr)
		return index;

	ListNode* node = this->head;
	for (int i = 0; node != nullptr; ++i) {
		if (data == node) {
			index = i;
			break;
		}
		node = node->next;
	}
	return index;
};

bool List::operator == (const List& b) const {
	const ListNode* node_a = this->Front();
	const ListNode* node_b = b.Front();
	while (node_a && node_b) {
		if (node_a->data != node_b->data)
			return false;
		if (node_a->rand || node_b->rand) {
			if (!node_a->rand || !node_b->rand)
				return false;
			if (node_a->rand->data != node_b->rand->data)
				return false;
		}
		node_a = node_a->next;
		node_b = node_b->next;
	}

	return (!node_a && !node_b);
}

void List::Serialize  (FILE* file) {
	if (file == nullptr)
		return;

	// count
	std::size_t type_size = sizeof(this->count);
	fwrite(&type_size, sizeof(type_size), 1, file);	// field_size
	fwrite(&this->count, type_size, 1, file); 		// field_value

	// nodes
	ListNode* node = this->head;
	for (int i = 0; node != nullptr; ++i) {
		// rand
		int rand_index = this->IndexOf(node->rand);
		type_size = sizeof(rand_index);
		fwrite(&type_size, sizeof(type_size), 1, file);	// field_size
		fwrite(&rand_index, type_size, 1, file); 		// field_value

		// data
		type_size = sizeof(std::string::value_type);
		std::size_t len = node->data.length();
		std::size_t len_size = sizeof(len);
		fwrite(&len_size , sizeof(len_size) , 1, file);	// length field_size
		fwrite(&len      , len_size         , 1, file);	// length field_value
		fwrite(&type_size, sizeof(type_size), 1, file);	// data field_size
		fwrite(&node->data[0], type_size, len, file);	// data field_value

		node = node->next;
	}
};

void List::Deserialize(FILE* file) {
	if (file == nullptr)
		return;
	std::map<ListNode*, int> mapRands;

	// count
	int count;
	std::size_t type_size = 0;
	fread(&type_size, sizeof(type_size), 1, file);	// field_size
	fread(&count, type_size, 1, file);				// field_value

	// nodes
	for (int i = 0; i < count; ++i) {
		this->PushBack("");
		ListNode* node = this->Back();

		// rand
		int rand_index = 0;
		fread(&type_size, sizeof(type_size), 1, file);	// field_size
		fread(&rand_index, type_size, 1, file); 		// field_value
		if (0 <= rand_index && rand_index < count)
			mapRands[node] = rand_index;

		// data
		std::size_t len;
		fread(&type_size, sizeof(type_size), 1, file);	// length field_size
		fread(&len      , type_size        , 1, file);	// length field_value
		node->data.assign(len, 0);
		fread(&type_size, sizeof(type_size), 1, file);	// data field_size
		fread(&node->data[0], type_size, len, file);	// data field_value
	}

	if (!mapRands.empty()) {
		ListNode* node = this->head;
		while (node) {
			std::map<ListNode*, int>::iterator finded = mapRands.find(node);
			if (finded != mapRands.end()) {
				node->rand = this->at(finded->second);
			}
			node = node->next;
		}
	}
}

const unsigned int BUFF_SIZE = 256;
void List::SerializeJSON  (FILE* file) {
	if (file == nullptr)
		return;

	// count
	fprintf(file, "\"count\" : %d,\n", this->count);

	// nodes
	fprintf(file, "\"nodes\" : [\n");
	ListNode* node = this->head;
	for (int i = 0; node != nullptr; ++i) {
		fprintf(file, "{\n");
		if (node->rand) {
			fprintf(file, "\"randIx\" : %d,\n", this->IndexOf(node->rand));
		}
		fprintf(file, "\"data\" : \"%s\",\n", node->data.c_str());
		fprintf(file, "},\n");

		node = node->next;
	}
	fprintf(file, "],\n");
};

void List::DeserializeJSON(FILE* file) {
	if (file == nullptr)
		return;

	using std::string;
	using std::size_t;
	string buff(BUFF_SIZE, 0);

	while (fgets(&buff[0], BUFF_SIZE, file)) {
		size_t pos = buff.find(" : ");
		if (pos != string::npos) {
			string key = buff.substr(0, pos);
			string val = buff.substr(pos + 3, buff.length());
			if (!val.empty() && val[val.length()-1] == '\n') {
				val[val.length()-1] = 0;
			}

			if (key == "\"count\"") {
				this->count = std::atoi(val.c_str());
			}
			else if (key == "\"nodes\"") {
				this->DeserializeNodes(file);
			}
		}
	}
};

void List::DeserializeNodes(FILE* file) {
	using std::string;
	using std::size_t;
	using std::map;
	char buff[BUFF_SIZE];
	map<ListNode*, int> mapRands;

	ListNode * node = nullptr;
	string* current_data = nullptr;	// чтобы подцеплять невместившиеся в буфер данные
	this->count = 0;
	while (fgets(buff, BUFF_SIZE, file)) {
		if (buff[0] == ']') {
			break;
		}
		if (buff[0] == '{') {
			this->PushBack("");
			node = this->Back();
			current_data = nullptr;
			continue;
		}
		if (buff[0] == '}') {
			continue;
		}
		string line = buff;
		size_t pos = line.find(" : ");
		if (pos != string::npos) {
			current_data = nullptr;
			string key = line.substr(0, pos);
			string val = line.substr(pos + 3, line.length());
			if (!val.empty()) {
				if (val[0] == '\"') {
					size_t p1 = 0;
					size_t p2 = val.rfind("\"");
					if (p2 != string::npos && p1 != p2) {
						val.erase(p2, val.length() - p2);
					}
					val.erase(p1, 1);
				}
			}
			if (key == "\"randIx\"") {
				mapRands[node] = std::atoi(val.c_str());
			}
			else if (key == "\"data\"") {
				node->data = val;
				current_data = &node->data;
			}
		}
		else if (current_data != nullptr) {
			string val = buff;
			size_t p1 = 0;
			size_t p2 = val.rfind("\"");
			if (p2 != string::npos && p1 != p2) {
				val.erase(p2, val.length() - p2);
			}
			current_data->append(val);
		}
	}

	if (!mapRands.empty()) {
		ListNode* node = this->head;
		while (node) {
			map<ListNode*, int>::iterator finded = mapRands.find(node);
			if (finded != mapRands.end()) {
				node->rand = this->at(finded->second);
			}
			node = node->next;
		}
	}
};
