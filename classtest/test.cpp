//
// Created by qiwentao on 22-8-15.
//
#include <bits/stdc++.h>
#include <mysql/mysql.h>
#include "Person.h"

using namespace std;


int main() {
    MYSQL mysql;
    mysql_init(&mysql);

    if (mysql_real_connect(&mysql, "localhost", "root", "123456789", "test", 3306, nullptr, 0) == nullptr)
        cout << "fail" << endl;
    else cout << "connect success!" << endl;

    string sql = "select * from test_table";
    int mysqlQuery = mysql_query(&mysql, sql.c_str());
    MYSQL_RES *result = mysql_store_result(&mysql);
    if (result == nullptr) {
        cout << "nothing!" << endl;
    } else {
        int numFields = mysql_num_fields(result);
        for (int i = 0; i < numFields; i++) {
            MYSQL_ROW row = mysql_fetch_row(result);
//            if (i<=0)break;
            for (int j = 0; j < numFields; ++j) {
                cout << row[j] << " ";
            }
            cout << endl;
        }
    }


//    Person person;
//    cout<<__cplusplus<<endl;
//    read(cin, person);
//    print(cout, person);

//    static unordered_map< string,int> mp;
//    mp["a"]=1;
//    mp["c"]=2;
//    const string name="a";
//    auto it = mp.find(name);
//    if (it!=mp.end()){
//        auto val=mp[name];
//        if (val==1) cout<<"val==1"<<endl;
//    }

}

