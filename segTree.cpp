//
// Created by qiwentao on 22-9-20.
//
#include <bits/stdc++.h>
#include "yaml.h"
//#include <mcheck.h>

//#pragma GCC optimize(2)
using namespace std;
#define int long long
typedef long long LL;
typedef long long ll;
const int INF = 0x3f3f3f3f;
//const int inf = 1e18;
const int mod = 998244353;
//const int mod = 1e9 + 7;
#define PI 3.1415926

int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }

const int maxn = 1e4 + 10;
const int N = 6e6 + 100;

int d[maxn];
int m[maxn];
#define name(x) (#x)
void solve() {
//    int n, m;
//    cin >> n >> m;
    int age;
    int name;

    cout<<name(name)<<":";

    YAML::Node yaml = YAML::LoadFile("../config/config.yaml");
    cout << yaml["name"].as<string>() << endl;
    cout << yaml["age"].as<int>() << endl;
}

signed main() {
//    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
//    cout << hex;//16进制
//    cout   <<fixed<<setprecision(3)  << endl;//保留小数
    int _ = 1;
//    cin >> _;
    while (_--) {
        solve();//cout<<"\n";
    }
    return 0;
}
///==============================
