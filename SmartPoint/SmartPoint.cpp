#include <iostream>
using namespace std;

template<class t>
class my_unique_ptr {
    t* ptr;
public:
    my_unique_ptr() : ptr(nullptr) {}
    my_unique_ptr(const my_unique_ptr& sp) = delete;
    my_unique_ptr(t* p) {
        ptr = p;
    }
    ~my_unique_ptr() {
        delete ptr;
    }

    t& operator* () {
        return *ptr;
    }

    t* get() {
        return ptr;
    }
    void reset() {
        delete ptr;
        ptr = nullptr;
    }
    void realese() {
        ptr = nullptr;
    }
    void swap(my_unique_ptr<t>& up) {
        std::swap(ptr, up.ptr);
    }
};

template<class t>
class my_shared_ptr {
    t* ptr = nullptr;
    size_t* count = nullptr;
public:
    my_shared_ptr() : ptr(nullptr), count(nullptr) {}
    my_shared_ptr(const my_shared_ptr& sp) {
        ptr = sp.ptr;
        count = sp.count;
        *count++;
    };
    my_shared_ptr(t* p) {
        ptr = p;
        count = new size_t(1);
    }

    ~my_shared_ptr() {
        if ((*count) > 0 ) {
            (*count)--;
            return;
        }
        delete ptr;
        delete count;
    }

    t& operator* () {
        return *ptr;
    }
    t* operator->() {
        return ptr;
    }
    void operator == (my_shared_ptr<t>& up) {
        up.ptr = ptr;
        *(count)++;
    }

    t* get() {
        return ptr;
    }
    void reset() {
        delete ptr;
        ptr = nullptr;
    }
    void swap(my_shared_ptr<t>& up) {
        std::swap(ptr, up.ptr);
    }
    size_t use_count() {
        return *count;
    }
};


int main()
{

    shared_ptr<int> p(new int(5));
    shared_ptr<int> p2;
    cout << p.use_count() << endl;
    p2 = p;
    cout << p.use_count() << endl;

    shared_ptr<int> y;
    cout << p.use_count() << endl;
    y = p2;
    cout << p.use_count() << endl;

    cout << "---------------------------------------------------\n";
    my_shared_ptr<int> p3(new int(5));
    my_shared_ptr<int> p4;
    cout << p3.use_count() << endl;
    p4 = p3;
    cout << p3.use_count() << endl;

    my_shared_ptr<int> x;
    cout << p.use_count() << endl;
    x = p4;
    cout << p3.use_count() << endl;

    return 0;
}