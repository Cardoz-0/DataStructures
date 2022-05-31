// copyright Gabriel da Silva Cardoso
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>

/*!
* Lista genérica que pode ter um elemento adicionado e retirado em qualquer
* ponto do array
*/
class ArrayList {
 public:
    /*!
    * Inicializa a lista sem elementos de tamanho "DEFAULT_MAX"
    */
    ArrayList();

    /*!
    * Inicializa a lista sem elementos de tamanho "max_size"
    */
    explicit ArrayList(std::size_t max_size);

    /*!
    * Deleta o array dos elementos também
    */
    ~ArrayList();

    /*!
    * limpa a lista atribuindo 0 ao "size_"
    */
    void clear();

    /*!
    * Adiciona "data" ao final da lista
    */
    void push_back(const T& data);

    /*!
    * Move todos os elementos um slot acima
    * Insere "data" ao começo da lista
    */
    void push_front(const T& data);

    /*!
    * Move todos os elementos a partir do "index" um slot acima
    * Insere "data" no slot de "index"
    */
    void insert(const T& data, std::size_t index);

    /*!
    * Move todos elementos a partir slot destinado ao "data" um slot acima
    * Insere "data" no slot seguinte ao maior elemento menor que "data"
    */
    void insert_sorted(const T& data);

    /*!
    * retira o elemento na posição "index"
    */
    T pop(std::size_t index);

    /*!
    * retira o último elemento da lista
    */
    T pop_back();

    /*!
    * retira o primeiro elemento da lista
    */
    T pop_front();

    /*!
    * exclui o elemento equivalente ao "data"
    */
    void remove(const T& data);

    /*!
    * retorna se a lista está cheia
    */
    bool full() const;

    /*!
    * retorna se a lista está vazia
    */
    bool empty() const;

    /*!
    * retorna se a lista contém "data"
    */
    bool contains(const T& data) const;

    /*!
    * retorna a posição de "data" na lista
    */
    std::size_t find(const T& data) const;

    /*!
    * retorna "size_"
    */
    std::size_t size() const;

    /*!
    * retorna "max_size_"
    */
    std::size_t max_size() const;

    /*!
    * verifica se index está fora dos limites
    * retorna elemento na posição "index"
    */
    T& at(std::size_t index);

    /*!
    * retorna elemento na posição "index"
    */
    T& operator[](std::size_t index);

    /*!
    * verifica se index está fora dos limites
    * retorna elemento na posição "index" como constante
    */
    const T& at(std::size_t index) const;

    /*!
    * retorna elemento na posição "index" como constante
    */
    const T& operator[](std::size_t index) const;

 private:
    T* contents;
    std::size_t size_ = 0;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};  // ArrayList

template<typename T>
ArrayList<T>::ArrayList() : ArrayList(DEFAULT_MAX) {}

template<typename T>
ArrayList<T>::ArrayList(std::size_t max_size):
    contents {new T[max_size]},
    max_size_ {max_size} {}

template<typename T>
ArrayList<T>::~ArrayList() {
    delete[] contents;
}

template<typename T>
void ArrayList<T>::clear() {
    size_ = 0;
}

template<typename T>
void ArrayList<T>::push_back(const T& data) {
    if (full())
        throw std::out_of_range("List is full!");
    contents[size_++] = data;
}

template<typename T>
void ArrayList<T>::push_front(const T& data) {
    if (full())
        throw std::out_of_range("List is full!");
    size_++;
    for (std::size_t position = size_-1; position > 0; position--)
        contents[position] = contents[position-1];
    contents[0] = data;
}

template<typename T>
void ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full())
        throw std::out_of_range("List is full!");
    if ((index < 0 || index >= size_) && (empty() && index != 0))
        throw std::out_of_range("Index invalid!");
    for (std::size_t position = size_; position > index; position--)
        contents[position] = contents[position-1];
    contents[index] = data;
    size_++;
}
template<typename T>
void ArrayList<T>::insert_sorted(const T& data) {
    if (full())
        throw std::out_of_range("List is full!");
    std::size_t position = 0;
    while (position < size_ && data > contents[position])
        position++;
    insert(data, position);
}

template<typename T>
T ArrayList<T>::pop(std::size_t index) {
    if (empty())
        throw std::out_of_range("List is empty!");
    if (index < 0 || index >= size_)
        throw std::out_of_range("List is empty!");
    auto data = contents[index];
    size_--;
    for (std::size_t position = index; position < size_; position++)
        contents[position] = contents[position+1];
    return data;
}

template<typename T>
T ArrayList<T>::pop_back() {
    if (empty())
        throw std::out_of_range("List is empty!");
    return contents[--size_];
}

template<typename T>
T ArrayList<T>::pop_front() {
    return pop(0);
}

template<typename T>
void ArrayList<T>::remove(const T& data) {
    pop(find(data));
}

template<typename T>
bool ArrayList<T>::full() const {
    return size_ == max_size_;
}

template<typename T>
bool ArrayList<T>::empty() const {
    return size_ == 0;
}

template<typename T>
bool ArrayList<T>::contains(const T& data) const {
    for (std::size_t position = 0; position < size_; position++)
        if (contents[position] == data)
            return true;
    return false;
}

template<typename T>
std::size_t ArrayList<T>::find(const T& data) const {
    for (std::size_t position = 0; position < size_; position++)
        if (contents[position] == data)
            return position;
    return size_;
}

template<typename T>
std::size_t ArrayList<T>::size() const {
    return size_;
}

template<typename T>
std::size_t ArrayList<T>::max_size() const {
    return max_size_;
}

template<typename T>
T& ArrayList<T>::at(std::size_t index) {
    if (index < 0 || index >= size_)
        throw std::out_of_range("Index invalid!");
    return contents[index];
}

template<typename T>
T& ArrayList<T>::operator[](std::size_t index) {
    return contents[index];
}

template<typename T>
const T& ArrayList<T>::at(std::size_t index) const {
    return at(index);
}

template<typename T>
const T& ArrayList<T>::operator[](std::size_t index) const {
    return operator[](index);
}

}  // namespace structures

#endif
