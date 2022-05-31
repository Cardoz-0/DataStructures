#define ALPHABET_SIZE 26

/**
 * 
 * @brief Declaração das funções usadas para implementar uma Trie.
 * 
*/
namespace trie {

    /**
     * @brief Struct que contém os dados do TrieNode
    */
    struct TrieNode {
        char data;
        unsigned long position;
        unsigned long length;
        struct TrieNode *children[ALPHABET_SIZE];
        bool leaf;
    };

    /**
     * 
     * @brief Retorna um nodo com filhos nulos e o dado recebido.
     * 
    */
    TrieNode* getNode(const char data);

    /**
    * @brief Retorna um nodo raiz
    */
    TrieNode* getRoot();

    /**
    * @brief Insere uma chave na raiz da trie, com dado, posição e comprimento.
    */
    void insert(TrieNode* root, std::string key, size_t position, size_t length);

    /**
    * @brief Verifica se uma dada chave está representada na Trie
    */
    bool contains(TrieNode* root, std::string key);

    /**
    * @brief Conta a quantidade de palavras para qual a string "key" é prefixo
    */
    int prefix_count(TrieNode* root, std::string key);

    /**
    * @brief Conta a quantidade de nós que finalizam uma palavra abaixo de um dado nó
    */
    int count_leaf_children(TrieNode* root);

    /**
    * @brief Retorna o último nó do percurso de uma chave. Exemplo: na chave "stock", retorna
    * o nó correspondente ao caractere "k"
    */
    TrieNode* get(TrieNode* root, std::string key);
}  // namespace trie