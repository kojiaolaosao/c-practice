//
// Created by qiwentao on 22-8-12.
//
#include <bits/stdc++.h>
#include "Chapter6.h"

using namespace std;

int add(const int a[10]) {
    return a[20];
}

void print(const int ia[10]) {
    for (size_t i = 0; i != 10; ++i)
        cout << ia[i] << endl;
}

void error_msg(int e, initializer_list<string> il) {
    cout << e << endl;
    for (const auto &x: il) {
        cout << x << " ";
    }
    cout << endl;
}

int add(int a, int b) { return a + b; }

int subtract(int a, int b) { return a - b; }

int multiply(int a, int b) { return a * b; }

int divide(int a, int b) { return b != 0 ? a / b : 0; }

int main() {
    int func(int, int);
    vector<decltype(func) *> v;

    v.push_back(add);
    v.push_back(subtract);
    v.push_back(multiply);
    v.push_back(divide);

    for (auto f: v) {
        cout << f(6, 2) << " ";
    }
    cout << endl;

//    string s1="1",s2="21";
//    error_msg(42,{"wqwq",s1,s2});

//    int a[100];
//    print(a);
//    return 0;

}