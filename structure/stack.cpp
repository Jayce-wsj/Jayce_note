#include <iostream>
#include <vector>
#include <deque>
#include <stack>
using namespace std;

template <class T>
class mStack {
public:
    mStack() {}
    ~mStack(){}
    void pop() {
        if (!que.empty()) {
            que.pop_back();
        }
    }
    void push(T e) {
        que.push_back(e);
    }
    T top() {
        return que.back();
    }
    bool empty() {
        return que.empty();
    }
private:
    deque<T> que;
};

int main() {
    mStack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.pop();
    cout << st.top()<<endl;
    return 0;
}
