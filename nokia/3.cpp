#include <iostream>

typedef struct List {
    struct List * next;
    int payload;

} List_t;

List_t* generateData() {
    List_t* data = nullptr, *item = nullptr;
    for (int i = 0; i < 25; i++) {
        if (!item) {
            item = new List_t;
            data = item;
        }
        else {
            item->next = new List_t;
            item = item->next;
        }
        item->payload = i;
    }
    return data;
}

void clear(List_t*& data) {
    while (data) {
        List_t* next = data->next;
        delete data;
        data = next;
    }
}

void print(const List_t* data) {
    while (data) {
        std::cout << data->payload << " ";
        data = data->next;
    }
    std::cout << std::endl;    
}

List_t* erase(List_t* item, std::size_t index, std::size_t count) {
    for (std::size_t i = 0; item != nullptr && i < index-1; i++)
        item = item->next;

    if (item == nullptr || item->next == nullptr)
        return nullptr;
    
    List_t* delete_item = item->next;
    for (std::size_t i = 0; delete_item != nullptr && i < count; i++) {
        List_t* next = delete_item->next;
        delete delete_item;
        delete_item = next;
    }
    item->next = delete_item;
    return delete_item;
}

List_t* erase_loop(List_t* item, std::size_t index, std::size_t count) {
    while (item) {
        item = erase(item, index, count);
    }
    return item;
}


int main() {
	using namespace std;
    std::string text;

    cout << "Delete items from quelist" << endl;

    auto data = generateData();
    print(data);
    erase_loop(data, 5, 1);
    print(data);
    clear(data);

	return  0;
}