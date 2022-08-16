#include <iostream>
#include <stdexcept>

struct my_exception : std::exception {
    const char* what() const _NOEXCEPT {
        return "индекс за границами массива";
    }
};

struct smart_array {
    int* m_array;
    int m_size, m_max_size;
    smart_array(const int &n) {
        this->m_size = 0;
        this->m_max_size = n;
        m_array = new int[n];
    }
    ~smart_array() {
        delete[] m_array;
        m_array = nullptr;
    }
    void add_element(const int &n) {
        if (m_size >= 0 && m_size < m_max_size) {
            m_array[m_size] = n;
            m_size++;
        }
        else {
            throw my_exception();
        }
    }
    int get_element(const int &n) {
        if (n >= 0 && n <= m_max_size) {
            return m_array[n];
        }
        else {
            throw my_exception();
        }
    }
    smart_array& operator = (const smart_array &a) {
        this->m_size = a.m_size;
        this->m_max_size = a.m_max_size;

        delete[] m_array;
        m_array = new int[m_max_size];

        for (int i = 0; i < m_size; ++i) {
            m_array[i] = a.m_array[i];
        }

        return *this;
    }
};

int main() {
    try {
        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);

        smart_array new_array(2);
        new_array.add_element(44);
        new_array.add_element(34);

        arr = new_array;

        std::cout << arr.get_element(0) << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}