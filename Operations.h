
#include <string>

std::string operation_list = "*/+-";

template <typename T> struct addition {
    T operator()(const T& t1, const T& t2) const {
        return t1 + t2;
    }
};

template <typename T> struct subtraction {
    T operator()(const T& t1, const T& t2) const {
        return t1 - t2;
    }
};

template <typename T> struct multiplication {
    T operator()(const T& t1, const T& t2) const {
        return t1 * t2;
    }
};

template <typename T> struct division {
    T operator()(const T& t1, const T& t2) const {
        return t1 / t2;
    }
};
