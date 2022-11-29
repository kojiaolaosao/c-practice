//
// Created by qiwentao on 22-8-15.
//
#include <bits/stdc++.h>
#include "Person.h"

using namespace std;



int main() {
//    Person person;
//    cout<<__cplusplus<<endl;
//    read(cin, person);
//    print(cout, person);

    static unordered_map< string,int> mp;
    mp["a"]=1;
    mp["c"]=2;
    const string name="a";
    auto it = mp.find(name);
    if (it!=mp.end()){
        auto val=mp[name];
        if (val==1) cout<<"val==1"<<endl;
    }

}

