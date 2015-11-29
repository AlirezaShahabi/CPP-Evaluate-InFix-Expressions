
#include <iostream>

template <typename T> class Stack {
// friend functions
friend void print(const Stack& obj, std::ostream& os) {
    if (obj.cap == -1) {
        std::cout << "Empty Stack\n";
    } else {
        for (size_t i = 0; i <= obj.cap; ++i) {os << obj.data[i] << " ";}
        os << "\n\n";
    }
}
public:
    // constructor-operator-destructor
    Stack();
    Stack(const Stack&);
    Stack& operator=(Stack);
    ~Stack();
    // swap
    void swap(Stack& rhs);
    // add-remove-top
    Stack& push(const T&);
    Stack& pop();
    T& top();
    // get information
    bool is_empty() const {return cap == -1 ? 1:0;}
    size_t size() const {return cap+1;}
private:
    T* data;
    size_t cap;
    size_t capacity;
    // private utility functions
    void check_n_alloc();
    void reallocate();
    void free_up();
};



// constructor - operator - destructor

template <typename T> Stack<T>::Stack():data(nullptr),cap(-1),capacity(0) {}

template <typename T> Stack<T>::Stack(const Stack& rhs):
data(new T[rhs.capacity]),cap(rhs.cap),capacity(rhs.capacity) {
    std::copy(rhs.data, rhs.data + rhs.capacity, this->data);
}

template <typename T> Stack<T>& Stack<T>::operator=(Stack rhs) {
    swap(rhs);
    return *this;
}

template <typename T> Stack<T>::~Stack() {free_up();}

// swap
template <typename T> void Stack<T>::swap(Stack& rhs) {
    using std::swap;
    swap(data, rhs.data);
    swap(cap, rhs.cap);
    swap(capacity, rhs.capacity);
}

// add/remove element - return/update top

template <typename T> Stack<T>& Stack<T>::push(const T& obj) {
    check_n_alloc();
    data[++cap] = obj;
    return *this;
}

template <typename T> Stack<T>& Stack<T>::pop() {
    if (cap == 0) {
        cap = -1;
        capacity = 0;
        delete[] data;
        data = nullptr;
    } else if (cap > 0) {
        --cap;
    }
    return *this;
}

template <typename T> T& Stack<T>::top() {return data[cap];}

// private utility functions

template <typename T> void Stack<T>::check_n_alloc() {
    if (cap == -1) {
        capacity = 1;
        data = new T[capacity];
    } else if (cap == capacity-1) {
        reallocate();
    }
}

template <typename T> void Stack<T>::reallocate() {
    T* new_data = new T[2*capacity];
    std::copy(data, data+capacity, new_data);
    free_up();
    data = new_data;
    capacity = 2 * capacity;
}

template <typename T> void Stack<T>::free_up() {
    if (cap != -1) {delete[] data;}
}


