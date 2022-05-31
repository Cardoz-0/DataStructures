#include <iostream>
#include <fstream>
#include <sstream>

#include "trie.hpp"

int main() {
    
    std::ifstream file;
    std::string file_name;
    std::string word;

    std::cin >> file_name;

    file.open(file_name);
    
    if (!file.is_open()) {
        std::cout << "error\n";
        return -1;
    }
    
    struct trie::TrieNode *root = trie::getRoot();

    std::string line;
    size_t char_count = 0;

    while (std::getline(file, line)) {
        std::string word = line.substr(1, line.find_first_of(']') - 1);
        trie::insert(root, word, char_count, line.length());
        char_count += line.length() + 1;
    }

    file.close();
    
    while(1) {
        std::cin >> word;

        if (word.compare("0") == 0) {
            break;
        }

        int count = trie::prefix_count(root, word);

        if (count > 0) {
            std::cout << word << " is prefix of " << count << " words" << std::endl;
        } else {
            std::cout << word << " is not prefix" << std::endl;
        }

        if (trie::contains(root, word)) {
            trie::TrieNode* node = trie::get(root, word);

            std::cout << word << " is at (" << node->position << "," << node->length << ")" << std::endl; 
        }
    }

    return 0;
}   