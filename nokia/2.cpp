#include <iostream>
#include <string>
#include <sstream>
#include <map>

std::map<int, int> getCountWords(const std::string& text) {
    std::map<int, int> result;
    std::string word;
    
    for (std::size_t i = 0, len = text.length(); i <= len; ++i) {
        if (i == len || !isalnum(text[i])) {
            if (!word.empty()) {
                result[word.length()]++;
            }
            word.clear();
            continue;
        }
        word += text[i];
    }
    return result;
}

int main() {
	using namespace std;
    std::string text;

    cout << "Group and count words with equal length" << endl;
    cout << "Please enter text or [g] for generate: ";
    getline(cin, text);
    if (text == "g") {
        text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    }

    auto result = getCountWords(text);
    for (auto item : result)
        cout << "[" << item.first << "] " << item.second << " times" << endl;

	return  0;
}