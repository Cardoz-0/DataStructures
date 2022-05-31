//! Copyright [2018] <Copyright ...>


#ifndef STRUCTURES_STRING_LIST_H
#define STRUCTURES_STRING_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ exceptions
#include <cstring>



namespace structures {


//! ...
template<typename T>
class ArrayList {
 public:
    //! construtor
    ArrayList();
    //! construtor com parametro de tamanho
    explicit ArrayList(std::size_t max_size);
    //! destrutor
    ~ArrayList();

    //! metodo limpa lista
    void clear();
    //! metodo insere no fim da lista
    void push_back(const T& data);
    //! metodo insere no inicio da lista
    void push_front(const T& data);
    //! metodo insere em um index especifico da lista
    void insert(const T& data, std::size_t index);
    //! metodo insere alocando o parametro em ordem crescente
    void insert_sorted(const T& data);
    //! metodo retira e retorna o valor de um index especifico
    T pop(std::size_t index);
    //! metodo retira o ultimo elemento da lista
    T pop_back();
    //! metodo retira o primeiro elemento da lista
    T pop_front();
    //! metodo retira o elemento da lista, nao importando seu index
    void remove(const T& data);
    //! metodo verifica se a lista esta cheia
    bool full() const;
    //! metodo verifica se a lista esta vazia
    bool empty() const;
    //! metodo verifica se aquele valor esta na lista e
    //! garante que nenhum valor sera alterado
    bool contains(const T& data) const;
    //! metodo acha em que posição esta aquele valor
    //! garante que nenhum valor sera alterado
    std::size_t find(const T& data) const;
    //! metodo retorna o tamanho da variavel size
    //! garante que nenhum valor sera alterado
    std::size_t size() const;
    //! metodo retorna o tamanho da variavel max_size
    //! garante que nenhum valor sera alterado
    std::size_t max_size() const;
    //! metodo retorna o valor que esta presente no index
    T& at(std::size_t index);
    //! metodo retorna o valor que esta presente no index
    T& operator[](std::size_t index);
    //! metodo retorna o valor que esta presente no index
    //! garante que nenhum valor sera alterado
    const T& at(std::size_t index) const;
    //! metodo retorna o valor que esta presente no index
    //! garante que nenhum valor sera alterado
    const T& operator[](std::size_t index) const;

 protected:
    //! contents
    T* contents;
    //! tamanho atual
    std::size_t size_;
    //! tamahno maximo
    std::size_t max_size_;
    //! topo
    std::size_t top_;
    //! tamanho maximo padrão
    static const auto DEFAULT_MAX = 10u;
};



//-------------------------------------



//! ...
//! ArrayListString e' uma especializacao da classe ArrayList
class ArrayListString : public ArrayList<char *> {
 public:
    //! construtor
    ArrayListString() : ArrayList() {}
    //! construtor com parametro max_size_
    explicit ArrayListString(std::size_t max_size) : ArrayList(max_size) {}
    //! destrutor
    ~ArrayListString() {
        for (std::size_t i = 0; (unsigned)i < size_ ; i++) {
            delete[] contents[i];
        }
    }

    //! metodo limpa lista
    void clear() {
        for (std::size_t i = 0; (unsigned)i < size_ ; i++) {
            delete[] contents[i];
        }
        delete[] contents;
        contents = new char*[max_size_];
        top_ = -1;
        size_ = 0;
    }
    //! metodo insere no fim da lista
    void push_back(const char *data) {
        if (full()) {
            throw std::out_of_range("lista cheia");
        }
        top_ += 1;
        size_ += 1;
        char* newdata = new char[strlen(data)+1];
        snprintf(newdata, strlen(data)+1, "%s", data);
        contents[top_] = newdata;
    }
    //! metodo insere no inicio da lista
    void push_front(const char *data) {
        if ((unsigned)top_ == max_size_ - 1) {
            throw std::out_of_range("lista cheia");
        }
        top_ += 1;
        std::size_t c = top_;
        for (std::size_t i = 0; i < size_; i++) {
            contents[c] = contents[c - 1];
            c--;
        }
        size_ += 1;
        char* newdata = new char[strlen(data)+1];
        snprintf(newdata, strlen(data)+1, "%s", data);
        contents[0] = newdata;
    }
    //! metodo insere em um index especifico da lista
    void insert(const char *data, std::size_t index) {
        if (full()) {
            throw std::out_of_range("lista cheia");
        }
        if (index < 0 || index > max_size_-1) {
            throw std::out_of_range("index inválido");
        }
        top_ +=1;
        size_ +=1;
        for (std::size_t c = top_; c > index; c--) {
            contents[c] = contents[c - 1];
        }
        char* newdata = new char[strlen(data)+1];
        snprintf(newdata, strlen(data)+1, "%s", data);
        contents[index] = newdata;
    }
    //! metodo insere alocando o parametro em ordem crescente
    void insert_sorted(const char *data) {
        if (full()) {
            throw std::out_of_range("lista cheia");
        }
        std::size_t i;
        if (empty()) {
            push_back(data);
        } else {
            for (i = 0; i <= top_; i++) {
                if (strcmp(contents[i], data) > 0) {
                    insert(data, i);
                    break;
                } else if (strcmp(contents[i], data) < 0) {
                    push_back(data);
                }
            }
        }
    }
    //! metodo retira e retorna o valor de um index especifico
    char *pop(std::size_t index) {
        std::size_t var = -1;
        if (top_ == var) {
            throw std::out_of_range("lista vazia");
        }
        if (index > top_ || index < 0) {
            throw std::out_of_range("posição inválida");
        }
        top_ -= 1;
        size_ -= 1;
        char* remain = contents[index];
        for (std::size_t i = index; i <= top_; i++) {
            contents[i] = contents[i+1];
        }
        return remain;
    }
    //! metodo retira o ultimo elemento da lista
    char *pop_back() {
        std::size_t var = -1;

        if (top_ == var) {
            throw std::out_of_range("lista vazia");
        }
        top_ -= 1;
        size_ -= 1;
        return contents[top_+1];
    }
    //! metodo retira o primeiro elemento da lista
    char *pop_front() {
        std::size_t var = -1;
        if (top_ == var) {
            throw std::out_of_range("lista vazia");
        }
        char* remain = contents[0];
        top_ -=1;
        size_ -= 1;
        for (std::size_t i = 0; i < size_; i++) {
            contents[i] = contents[i+1];
        }
        return remain;
    }
    //! metodo retira o elemento da lista, nao importando seu index
    void remove(const char *data) {
        if (!contains(data)) {
            throw std::out_of_range("data not found");
        }
        std::size_t index = find(data);
        pop(index);
    }
    //! metodo verifica se aquele valor esta na lista
    bool contains(const char *data) {
        for (std::size_t i = 0; i <= top_; i++) {
            if (!strcmp(contents[i], data)) {
                return true;
            }
        }
        return false;
    }
    //! metodo acha em que posição esta aquele valor e
    //! retorna o indice em que ela se encontra
    std::size_t find(const char *data) {
        std::size_t i;
        for (i = 0; i <= top_; i++) {
            if (!strcmp(contents[i], data)) {
                break;
            }
        }
        return i;
    }
};

}  // namespace structures

#endif


template<typename T>
structures::ArrayList<T>:: ArrayList() {
    max_size_ = DEFAULT_MAX;
    contents = new T[DEFAULT_MAX];
    top_ = -1;
    size_ = 0;
}

template<typename T>
structures::ArrayList<T>:: ArrayList(std::size_t size) {
    max_size_ = size;
    size_ = 0;
    contents = new T[size];
    top_ = -1;
}

template<typename T>
structures::ArrayList<T>:: ~ArrayList() {
    delete [] contents;
}

template<typename T>
void structures::ArrayList<T>:: clear() {
    delete [] contents;
    contents = new T[max_size_];
    top_ = -1;
    size_ = 0;
}

template<typename T>
void structures::ArrayList<T>:: push_back(const T& data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    }
    top_ += 1;
    size_ += 1;
    contents[top_] = data;
}

template<typename T>
void structures::ArrayList<T>:: push_front(const T& data) {
    if (top_ == max_size_ - 1) {
        throw std::out_of_range("lista cheia");
    }
    top_ += 1;
    std::size_t c = top_;
    for (std::size_t i = 0; i < size_; i++) {
        contents[c] = contents[c - 1];
        c--;
    }
    size_ += 1;
    contents[0] = data;
}

template<typename T>
void structures::ArrayList<T>:: insert(const T& data, std::size_t index) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    }
    if (index < 0 || index > max_size_-1) {
        throw std::out_of_range("index inválido");
    }
    top_ +=1;
    size_ +=1;
    for (std::size_t c = top_; c > index; c--) {
        contents[c] = contents[c - 1];
    }
    contents[index] = data;
}

template<typename T>
void structures::ArrayList<T>:: insert_sorted(const T& data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    }
    std::size_t i;
    if (empty()) {
        push_back(data);
    } else {
        for (i = 0; i <= top_; i++) {
            if ( contents[i] > data ) {
                insert(data, i);
                break;
            } else if (contents[top_] < data) {
                push_back(data);
            }
        }
    }
}

template<typename T>
T structures::ArrayList<T>:: pop(std::size_t index) {
    if (top_ == -1) {
        throw std::out_of_range("lista vazia");
    }
    if (index > top_ || index < 0) {
        throw std::out_of_range("posição inválida");
    }
    top_ -= 1;
    size_ -= 1;
    T remain = contents[index];
    for (std::size_t i = index; i <= top_; i++) {
        contents[i] = contents[i+1];
    }
    return remain;
}

template<typename T>
T structures::ArrayList<T>:: pop_back() {
    if (top_ == -1) {
        throw std::out_of_range("lista vazia");
    }
    top_ -= 1;
    size_ -= 1;
    return contents[top_+1];
}

template<typename T>
T structures::ArrayList<T>:: pop_front() {
    if (top_ == -1) {
        throw std::out_of_range("lista vazia");
    }
    T remain = contents[0];
    top_ -=1;
    size_ -= 1;
    for (std::size_t i = 0; i < size_; i++) {
        contents[i] = contents[i+1];
    }
    return remain;
}

template<typename T>
void structures::ArrayList<T>:: remove(const T& data) {
    if (!contains(data)) {
        throw std::out_of_range("data not found");
    }
    std::size_t index = find(data);
    pop(index);
}

template<typename T>
bool structures::ArrayList<T>:: full() const {
    if (top_ == max_size_ -1) {
        return true;
    }
    return false;
}

template<typename T>
bool structures::ArrayList<T>:: empty() const {
    std::size_t var = -1;

    if (top_ == var) {
        return true;
    }
    return false;
}

template<typename T>
bool structures::ArrayList<T>:: contains(const T& data) const {
    for (std::size_t i = 0; i <= top_; i++) {
        if (contents[i] == data) {
            return true;
        }
    }
    return false;
}

template<typename T>
std::size_t structures::ArrayList<T>:: find(const T& data) const {
    std::size_t i;
    for (i = 0; i <= top_; i++) {
        if (contents[i] == data) {
            break;
        }
    }
    return i;
}

template<typename T>
std::size_t structures::ArrayList<T>:: size() const {
    return size_;
}

template<typename T>
std::size_t structures::ArrayList<T>:: max_size() const {
    return max_size_;
}

template<typename T>
T& structures::ArrayList<T>:: at(std::size_t index) {
    if (index < 0 || index > top_) {
        throw std::out_of_range("index inválido");
    }
    return contents[index];
}

template<typename T>
T& structures::ArrayList<T>:: operator[](std::size_t index) {
    if (index < 0 || index > top_) {
        throw std::out_of_range("Undefined behaviour");
    }
    return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>:: at(std::size_t index) const {
    if (index < 0 || index > top_) {
        throw std::out_of_range("index inválido");
    }
    return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>:: operator[](std::size_t index) const {
    if (index < 0 || index > top_) {
        throw std::out_of_range("Undefined behaviour");
    }
    return contents[index];
}

