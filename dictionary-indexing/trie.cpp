#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H
#define ALPHABET_SIZE 26

#include <iostream>
#include "trie.hpp"

namespace trie {
    /**
    * Retorna um nodo com filhos nulos e o dado recebido
    */
    TrieNode* getNode(const char data) {
        TrieNode* newNode = new TrieNode; 
        
        newNode->data = data;
        newNode->leaf = false;
        newNode->position = 0;
        newNode->length = 0;
        
        for (int i = 0; i < ALPHABET_SIZE; i++) 
            newNode->children[i] = nullptr;
        
        return newNode;
    }

    /**
    * Retorna um nodo raiz
    */
    TrieNode* getRoot() {
        TrieNode* newNode = new TrieNode; 
        
        newNode->data = '\0';
        newNode->leaf = false;
        newNode->position = 0;
        newNode->length = 0;
        
        for (int i = 0; i < ALPHABET_SIZE; i++) 
            newNode->children[i] = nullptr; 

        return newNode;
    }

    /**
    * Insere uma chave na raiz da trie, com dado, posição e comprimento.
    */
    void insert(TrieNode* root, std::string key, std::size_t position, std::size_t length) {
        TrieNode* crawlerNode = root;

        for (std::size_t i = 0; i < key.length(); i++) {
            int charIndex = key[i] - 'a';
            
            if (crawlerNode->children[charIndex] == nullptr) {
                crawlerNode->children[charIndex] = getNode(key[i]);
            }
            
            crawlerNode = crawlerNode->children[charIndex];
        }
        
        crawlerNode->leaf = true;
        crawlerNode->position = position;
        crawlerNode->length = length;
    }

    /**
    * Verifica se uma dada chave está representada na Trie
    */
    bool contains(TrieNode* root, std::string key) {
        TrieNode* crawlerNode = root;

        for (std::size_t i = 0; i < key.length(); i++) {
            int charIndex = key[i] - 'a';
            
            if (crawlerNode->children[charIndex] == nullptr)
                return false;
            
            crawlerNode = crawlerNode->children[charIndex];
        }
        
        return (crawlerNode != nullptr && crawlerNode->leaf);
    }

    /**
    * Conta a quantidade de palavras para qual a string "key" é prefixo
    */
    TrieNode* get(TrieNode* root, std::string key) {
        TrieNode* crawlerNode = root;

        for (std::size_t i = 0; i < key.length(); i++) {
            int charIndex = key[i] - 'a';
            
            if (crawlerNode->children[charIndex] == nullptr)
                return root;
            
            crawlerNode = crawlerNode->children[charIndex];
        }

        if ((crawlerNode != nullptr && crawlerNode->leaf)) {
            return crawlerNode;
        } else {
            return root;
        }
    }

    /**
    * Conta a quantidade de nós que finalizam uma palavra abaixo de um dado nó
    */
    int count_leaf_children(TrieNode* root) {
        int count = 0;

        for (std::size_t i = 0; i < ALPHABET_SIZE; i++) {
            if (root->children[i] == nullptr) {
                continue;
            } else {
                if (root->children[i]->leaf)
                    count += 1;
                
                count += count_leaf_children(root->children[i]);
            }
        }

        return count;
    }

    /**
    * Retorna o último nó do percurso de uma chave. Exemplo: na chave "stock", retorna
    * o nó correspondente ao caractere "k"
    */
    int prefix_count(TrieNode* root, std::string key) {
        TrieNode* crawlerNode = root;
        int count = 0;

        for (std::size_t i = 0; i < key.length(); i++) {
            int charIndex = key[i] - 'a';
            
            if (crawlerNode->children[charIndex] == nullptr)
                return 0;
            
            crawlerNode = crawlerNode->children[charIndex];
        }

        if (crawlerNode->leaf)
            count += 1;

        return count + count_leaf_children(crawlerNode);
    }

}  // namespace trie

#endif