#include <bits/stdc++.h>
#include <mcheck.h>

#pragma GCC optimize(2)
using namespace std;
//#define int long long
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

int dp[maxn][3];
int f[maxn];
int aaa[maxn];


void backtracking(string &s1, string &s2, int start, int current,int &depth) {
    if (current >= depth) return;
    if (start == s1.size() - 1) {
        depth = min(depth, current);
        return;
    }
    for (int i = start; i < s1.size(); i++) {
        if (s1[i] != s2[i]) {
            for (int j = i + 1; j < s2.size(); j++) {
                if (s2[j] == s1[i]) {
                    swap(s2[i], s2[j]);
                    backtracking(s1, s2, start + 1, current + 1, depth);
                    swap(s2[i], s2[j]);
                }
            }
            return;
        }
    }
    depth = min(depth, current);
}

int kSimilarity(string s1, string s2) {
    int depth = INT_MAX;
    backtracking(s1, s2, 0, 0, depth);
    return depth;
}

bool solve() {
    vector<vector<int>> v;
    vector<int> ve{-1, 0, 1};
    do {
        v.emplace_back(ve);
    } while (next_permutation(ve.begin(), ve.end()));
    for (const auto &x: v) {
        for (auto y: x) {
            cout << y << " ";
        }
        cout << endl;
    }
    return 0;
}

signed main() {
    //ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
//    cin >> _;
    while (_--) {
        solve();//cout<<"\n";
    }
    return 0;
}
