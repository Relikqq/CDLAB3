#include <iostream>
#include <vector>
#include <stack>
#include <cassert>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

// Реализация A: стек на массиве
class ArrayStack {
private:
    int* data;
    int capacity;
    int topIndex;
public:
    ArrayStack(int size) : capacity(size), topIndex(-1) {
        data = new int[capacity];
    }
    ~ArrayStack() {
        delete[] data;
    }
    void push(int val) {
        if (topIndex < capacity - 1) {
            data[++topIndex] = val;
        }
    }
    void pop() {
        if (topIndex >= 0) {
            topIndex--;
        }
    }
    int top() const {
        return data[topIndex];
    }
    bool isEmpty() const {
        return topIndex == -1;
    }
};

vector<int> solveWithArrayStack(const vector<int>& A) {
    int n = A.size();
    vector<int> result(n, 0);
    ArrayStack s(n);
    for (int i = n - 1; i >= 0; --i) {
        while (!s.isEmpty() && s.top() <= A[i]) {
            s.pop();
        }
        result[i] = s.isEmpty() ? 0 : s.top();
        s.push(A[i]);
    }
   
    return result;
}

// Реализация Б: стек на связанном списке
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v) : val(v), next(nullptr) {}
};

class LinkedListStack {
private:
    ListNode* head;
public:
    LinkedListStack() : head(nullptr) {}
    ~LinkedListStack() {
        while (!isEmpty()) {
            pop();
        }
    }
    void push(int val) {
        ListNode* newNode = new ListNode(val);
        newNode->next = head;
        head = newNode;
    }
    void pop() {
        if (head) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
    int top() const {
        return head->val;
    }
    bool isEmpty() const {
        return head == nullptr;
    }
};

vector<int> solveWithLinkedListStack(const vector<int>& A) {
    int n = A.size();
    vector<int> result(n, 0);
    LinkedListStack s;
    for (int i = n - 1; i >= 0; --i) {
        while (!s.isEmpty() && s.top() <= A[i]) {
            s.pop();
        }
        result[i] = s.isEmpty() ? 0 : s.top();
        s.push(A[i]);
    }
    return result;
}

// Реализация В: стек из STL
vector<int> solveWithSTLStack(const vector<int>& A) {
    int n = A.size();
    vector<int> result(n, 0);
    stack<int> s;
    for (int i = n - 1; i >= 0; --i) {
        while (!s.empty() && s.top() <= A[i]) {
            s.pop();
        }
        result[i] = s.empty() ? 0 : s.top();
        s.push(A[i]);
    }
    return result;
}

// Тестирование и бенчмарк
vector<int> generateLargeArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 1000000;
    }
    return arr;
}

int main() {
    // Тесты корректности
    vector<int> test1 = { 5,4,3,2,1 };
    vector<int> expected1 = { 0,0,0,0,0 };
    assert(solveWithArrayStack(test1) == expected1);
    assert(solveWithLinkedListStack(test1) == expected1);
    assert(solveWithSTLStack(test1) == expected1);

    vector<int> test2 = { 1,2,3,4,5 };
    vector<int> expected2 = { 2,3,4,5,0 };
    assert(solveWithArrayStack(test2) == expected2);
    assert(solveWithLinkedListStack(test2) == expected2);
    assert(solveWithSTLStack(test2) == expected2);

    vector<int> test3 = { 4,5,2,25 };
    vector<int> expected3 = { 5,25,25,0 };
    assert(solveWithArrayStack(test3) == expected3);
    assert(solveWithLinkedListStack(test3) == expected3);
    assert(solveWithSTLStack(test3) == expected3);

    // Замер производительности
    int n = 1000000;
    vector<int> largeArray = generateLargeArray(n);
    cout << "largeArray: ";
    for (int i = 0; i < 10; i++)
    {
        cout << largeArray[i] << " ";
    }
    cout << endl;
    auto start = high_resolution_clock::now();
    auto resArray = solveWithArrayStack(largeArray);
    auto stop = high_resolution_clock::now();
    auto durationArray = duration_cast<milliseconds>(stop - start).count();
    cout << "Result Array";
    for (int i = 0; i < 10; i++)
    {
        cout << resArray[i] << " ";
    }
    cout << endl;
    start = high_resolution_clock::now();
    auto resLinkedList = solveWithLinkedListStack(largeArray);
    stop = high_resolution_clock::now();
    auto durationLinkedList = duration_cast<milliseconds>(stop - start).count();
    cout << "Result List";
    for (int i = 0; i < 10; i++)
    {
        cout << resArray[i] << " ";
    }
    cout << endl;
    start = high_resolution_clock::now();
    auto resSTL = solveWithSTLStack(largeArray);
    stop = high_resolution_clock::now();
    auto durationSTL = duration_cast<milliseconds>(stop - start).count();
    cout << "Result STL";
    for (int i = 0; i < 10; i++)
    {
        cout << resArray[i] << " ";
    }
    cout << endl;
    cout << "ArrayStack: " << durationArray << " ms\n";
    cout << "LinkedListStack: " << durationLinkedList << " ms\n";
    cout << "STLStack: " << durationSTL << " ms\n";

    // Проверка совпадения результатов
    assert(resArray == resLinkedList);
    assert(resArray == resSTL);

    return 0;
}