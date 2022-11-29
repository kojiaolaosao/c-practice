#include <bits/stdc++.h>
//#include <filesystem>

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

const int maxn = 3e5 + 10;
const int N = 6e6 + 100;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    explicit ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void dfs8(int i, int j, vector<vector<int>> &vector, queue<pair<int, int>> queue1);

void pre(TreeNode *root, int d, vector<vector<int>> &ve) {
    if (!root) return;
    if (d >= ve.size()) ve.emplace_back();
    ve[d].push_back(root->val);
    pre(root->left, d + 1, ve);
    pre(root->right, d + 1, ve);
}

vector<vector<int>> levelOrder(TreeNode *root) {
    vector<vector<int>> ve;
    pre(root, 0, ve);
    return ve;
}


TreeNode *dfs(int pl, int pr, vector<int> &postorder, int il, int ir, vector<int> &inorder) {
    if (pl > pr || il > ir) return nullptr;
    auto root = new TreeNode(postorder[pr]);
    int inx = -1;
    for (int i = il; i <= ir; ++i) {
        if (postorder[pr] == inorder[i]) {
            inx = i;
            break;
        }
    }
    root->left = dfs(pl, pl + inx - il - 1, postorder, il, inx - 1, inorder);
    root->right = dfs(pl + inx - il, pr - 1, postorder, inx + 1, ir, inorder);
    return root;
}

TreeNode *buildTree(vector<int> &postorder, vector<int> &inorder) {
    return dfs(0, postorder.size() - 1, postorder, 0, inorder.size() - 1, inorder);
}


void dfs1(TreeNode *root, int d, vector<vector<int>> &ve) {
    if (!root) return;
    dfs1(root->left, d + 1, ve);
    dfs1(root->right, d + 1, ve);
    ve.begin()->push_back(root->val);
}

vector<vector<int>> levelOrderBottom(TreeNode *root) {
    vector<vector<int>> res;
    dfs1(root, 0, res);
    return res;
}

int isPrefixOfWord(const string &sentence, const string &searchWord) {
    stringstream ss(sentence);
    string s;
    int i = 1;
    while (ss >> s) {
        if (s.find(searchWord) == 0) return i;
        i++;
    }
    return -1;
}

vector<int> findClosestElements(vector<int> &arr, int k, int x) {
    int l = 0, r = arr.size() - k;
    int mid;
    while (l < r) {
        mid = (l + r) >> 1;
        if (x - arr[mid] > arr[l] - x) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return vector<int>(arr.begin() + l, arr.begin() + l + k);
}

bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
    vector<int> in(numCourses);
    unordered_map<int, vector<int>> mp;
    for (int i = 0; i < prerequisites.size(); ++i) {
        int c = prerequisites[i][0];
        in[c]++;
        mp[prerequisites[i][1]].push_back(c);
    }
    queue<int> q;
    int count = 0;
    for (int i = 0; i < in.size(); ++i) {
        if (in[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int temp = q.front();
        q.pop();
        count++;
        for (int i = 0; i < mp[temp].size(); ++i) {
            int u = mp[temp][i];
            in[u]--;
            if (in[u] == 0) q.push(u);
        }
    }
    if (count == numCourses) return true;
    return false;
}


TreeNode *dfs3(vector<int> &nums, int l, int r) {
    if (l >= r) return nullptr;
    int mid = (l + r) >> 1;
    auto *root = new TreeNode(nums[mid]);
    root->left = dfs3(nums, l, mid);
    root->right = dfs3(nums, mid + 1, r);
    return root;
}

TreeNode *sortedArrayToBST(vector<int> &nums) {
    int len = nums.size();
    dfs3(nums, 0, len);
}

ListNode *rotateRight(ListNode *head, int k) {
    ListNode *p = head;
    ListNode *cur = head;
    int l = 0;
    while (p->next) {
        p = p->next;
        l++;
    }
    k %= l + 1;
    if (!k) return head;
    while (l > k++) {
        cur = cur->next;
    }
    p->next = head;
    p = cur->next;
    cur->next = nullptr;
    return p;
}


int maxl = 0;

int dfs4(TreeNode *r, int val) {
    if (!r)return 0;
    int ln = dfs4(r->left, r->val);
    int rn = dfs4(r->right, r->val);
    maxl = max(maxl, rn + ln);
    if (r->val == val) {
        return max(ln, rn) + 1;
    }
    return 0;
}

int longestUnivaluePath(TreeNode *root) {
    dfs4(root, root->val);
    return maxl;
}

unordered_map<string, TreeNode *> seen;
unordered_set<TreeNode *> repeat;


string dfs5(TreeNode *root) {
    if (!root) return "";
    string s = to_string(root->val) + "(" + dfs5(root->left) + ")(" + dfs5(root->right) + ")";
    if (auto it = seen.find(s);it != seen.end()) {
        repeat.insert(it->second);
    } else {
        seen[s] = root;
    }
    return s;
}

vector<TreeNode *> findDuplicateSubtrees(TreeNode *root) {
    dfs5(root);
    return {repeat.begin(), repeat.end()};
}

int uniqueLetterString(string s) {
    unordered_map<char, vector<int >> mp;
    for (int i = 0; i < s.size(); ++i) {
        mp[s[i]].push_back(i);
    }
    int res = 0;
    for (auto [_, ve]: mp) {
        ve.insert(ve.begin(), -1);
        ve.push_back(s.size());
        for (int i = 1; i < ve.size() - 1; ++i) {
            res += (ve[i] - ve[i - 1]) * (ve[i + 1] - ve[i]);
        }
    }
    return res;
}


int findf(vector<int> &ve, int x) {
    return x == ve[x] ? x : ve[x] = findf(ve, ve[x]);
}

vector<int> findRedundantConnection(vector<vector<int>> &edges) {
    int n = edges.size();
    vector<int> f(n + 10);
    for (int i = 1; i <= edges.size(); ++i) {
        f[i] = i;
    }
    for (auto e: edges) {
        int v = e[0], u = e[1];
        if (findf(f, v) != findf(f, u)) {
//            to do union
            f[findf(f, v)] = findf(f, u);
        } else return e;
    }
    return {0, 0};
}


TreeNode *sortedListToBST(ListNode *head) {
    if (!head) return nullptr;
    else if (!head->next) return new TreeNode(head->val);
    ListNode *p = head;
    ListNode *p1 = head->next;
    ListNode *p2 = p1->next;
    while (p2 && p2->next) {
        p = p->next;
        p1 = p1->next;
        p2 = p2->next->next;
    }
    p->next = nullptr;
    TreeNode *t = new TreeNode(p1->val);
    t->left = sortedListToBST(head);
    t->right = sortedListToBST(p1->next);
    return t;
}

void dfs6(TreeNode *t, vector<string> &ve, string s) {
    if (!t) ve.emplace_back();
    if (t->left) dfs6(t->left, ve, s + to_string(t->val) + "->");
    if (t->right) dfs6(t->right, ve, s + to_string(t->val) + "->");

    if (!t->right && !t->left) {
        ve.push_back(s + to_string(t->val));
    }
}

vector<string> binaryTreePaths(TreeNode *root) {
    vector<string> ve;
    dfs6(root, ve, "");
    return ve;
}

vector<int> relativeSortArray(vector<int> &arr1, vector<int> &arr2) {
    map<int, int> mp;
    for (auto x: arr1) {
        mp[x]++;
    }
    int ind = 0;
    for (auto x: arr2) {
        while (mp[x]--)
            arr1[ind++] = x;
    }
    for (auto [f, s]: mp) {
        while (s--) {
            arr1[ind++] = f;
        }
    }
    return arr1;
}

vector<int> topKFrequent(vector<int> &nums, int k) {
    map<int, int> mp;
    for_each(nums.begin(), nums.end(), [&](const auto &item) {
        mp[item]++;
    });
    vector<pair<int, int>> ve(mp.begin(), mp.end());
    sort(ve.begin(), ve.end(), [](pair<int, int> &a, pair<int, int> &b) {
        return a.second > b.second;
    });
    vector<int> v;
    std::for_each_n(ve.begin(), k, [&](pair<int, int> item) {
        v.push_back(item.first);
    });
    return v;
}

vector<int> countBits(int n) {
    vector<int> dp(n + 1, 0);
    dp[0] = 0;
    for (int i = 1; i < n; ++i) {
        dp[i] = dp[i >> 1] + (i & 1);
    }
    return dp;
}

int trap(vector<int> &height) {
    vector<int> l(height.size());
    vector<int> r(height.size());
    l[0] = height[0];
    for (int i = 1; i < height.size(); ++i) {
        l[i] = max(height[i], l[i - 1]);
    }
    r[height.size() - 1] = height[height.size() - 1];
    for (int i = height.size() - 2; i >= 0; --i) {
        r[i] = max(height[i], r[i + 1]);
    }
    int sum = 0;
    for (int i = 0; i < height.size(); ++i) {
        int h = min(l[i], r[i]);
        sum += h - height[i];
    }
    return sum;
}

string reverseOnlyLetters(string s) {
    int l = 0, r = s.size() - 1;
    while (l <= r) {
        if (isalpha(s[l]) && isalpha(s[r])) {
            swap(s[l], s[r]);
            l++, r--;
        }
        if (!isalpha(s[l])) l++;
        if (!isalpha(s[r])) r--;
    }
    return s;
}


long long waysToBuyPensPencils(int total, int cost1, int cost2) {
    int sum = 1;
    for (int i = 0; i <= total / cost1; ++i) {
        sum += (total - i * cost1) / cost2 + 1;
    }
    return sum;
}

long long minimalKSum(vector<int> &nums, int k) {
    int res = 0;
    std::sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    std::for_each(nums.begin(), nums.end(), [&](int item) {
        if (item > 0 && item <= k) k++, res += item;
    });
    return -res + k * (k + 1) / 2;
}

int findTargetSumWays(vector<int> &nums, int target) {
    int sum = 0;
    for (const auto &item: nums) sum += item;
    if (sum < target || (sum - target) % 2) return 0;
    int res = (sum - target) >> 1;
    vector<int> dp(res + 1);
    dp[0] = 1;
    std::for_each(nums.begin(), nums.end(), [&](const auto &item) {
        for (int i = res; i >= item; --i) {
            dp[i] += dp[i - item];
        }
    });
    return dp[res];
}

int sumOfFlooredPairs(vector<int> &nums) {
    int maxx = *max_element(nums.begin(), nums.end());
    vector<int> cnt(maxx + 1);
    for (auto &item: nums) cnt[item]++;
    vector<int> pre(maxx + 1);
    for (int i = 1; i <= maxx; ++i) {
        pre[i] = pre[i - 1] + cnt[i];
    }
    long long ans = 0;
    for (int i = 1; i <= maxx; ++i) {
        if (cnt[i]) {
            for (int j = 1; j * i <= maxx; ++j) {
                ans += cnt[i] * j * (pre[min((j + 1) * i - 1, maxx)] - pre[j * i - 1]);
            }
        }
    }
    return ans;
}

int leastBricks(vector<vector<int>> &wall) {
    map<int, int> mp;
    for (auto &item: wall) {
        int sum = 0;
        for (int i = 0; i < item.size() - 1; ++i) {
            sum += item[i];
            mp[sum]++;
        }
    }
    int x = max_element(mp.begin(), mp.end(), [](pair<int, int> a, pair<int, int> b) {
        return a.second < b.second;
    })->second;
    return wall.size() - x;
}

int findLength(vector<int> &nums1, vector<int> &nums2) {
    vector<int> dp(nums2.size() + 1, 0);
    int res = 0;
    for (int i = 1; i <= nums1.size(); ++i) {
        for (int j = nums2.size(); j >= 1; ++j) {
            if (nums1[i - 1] == nums2[j - 1]) {
                dp[j] = dp[j - 1] + 1;
            }
            res = max(res, dp[j]);
        }
    }
    return res;
}


int numTilings(int n) {
    int mod = 1000000007;
    if (n < 3) return n;
    vector<int> dp(n + 1);
    dp[3] = 5;
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 4; i <= n; ++i) {
        dp[i] = (2 * dp[i - 1] + dp[i - 3]) % mod;
    }
    return dp[n];
}


bool canPartitionKSubsets(vector<int> &nums, int k) {
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if (sum % k) return false;
    int n = nums.size();
    int per = sum / k;
    sort(nums.begin(), nums.end());
    if (nums.back() > per) return false;
    vector<bool> dp(1 << n, true);
    function<bool(int, int)> dfs = [&dp, n, nums, per, &dfs](int s, int p) -> bool {
        if (s == 0) return true;
        if (!dp[s]) return false;
        dp[s] = false;
        for (int i = 0; i < n; ++i) {
            if (nums[i] + p > per) {
                break;
            }
            if ((s >> i) & 1) {
                if (dfs(s ^ (1 << i), (p + nums[i]) % per)) {
                    return true;
                }
            }
        }
        return false;
    };
    return dfs((1 << n) - 1, 0);
}

bool canPartitionKSubsets1(vector<int> &nums, int k) {
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if (sum % k) return false;
    int n = nums.size();
    int per = sum / k;
    sort(nums.begin(), nums.end());
    if (nums.back() > per) return false;

    vector<bool> dp(1 << n, false);
    vector<int> cursum(1 << n, 0);
    dp[0] = true;
    for (int i = 0; i < 1 << n; ++i) {
        if (!dp[i]) continue;
        for (int j = 0; j < n; ++j) {
            if (nums[j] + cursum[i] > per) break;
            if (i & (1 << j)) continue;
            else {
                int next = i | (1 << j);
                cursum[next] = (cursum[i] + nums[j]) % per;
                dp[next] = true;
            }
        }
    }
    return dp[(1 << n) - 1];
}

vector<int> frequencySort(vector<int> &nums) {
    map<int, int> mp;
    std::for_each(nums.begin(), nums.end(), [&](const auto &item) {
        mp[item]++;
    });
    std::sort(nums.begin(), nums.end(), [&](int a, int b) -> bool {
        return mp[a] == mp[b] ? a > b : mp[a] < mp[b];
    });
    return nums;
}

int maxLengthBetweenEqualCharacters(string s) {
    int ml = -1;
    for (int i = 0; i < s.size(); ++i) {
        int l = s.find_last_of(s[i]) - i - 1;
        ml = max(l, ml);
    }
    return ml;
}

array<array<int, 2>, 4> dir{1, 0, -1, 0, 0, 1, 0, -1};
array<int, 500 * 500 + 10> fa, areas;
int n;

int findf1(int x) {
    return x == fa[x] ? x : fa[x] = findf1(fa[x]);
}

void union1(int a, int b) {
    int af = findf1(a);
    int bf = findf1(b);
    if (af == bf) return;
    else {
        if (areas[af] > areas[bf]) {
            areas[af] += areas[bf];
            fa[bf] = af;
        } else {
            areas[bf] += areas[af];
            fa[af] = bf;
        }
    }
}

int largestIsland(const vector<vector<int>> &g) {
    n = g.size();
    int all = n * n;
    for (int i = 0; i < all; ++i) {
        fa[i] = i;
        areas[i] = 1;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (g[i][j] == 0)continue;
            for (const auto [xx, yy]: dir) {
                int x = i + xx, y = j + yy;
                if (x >= 0 && x < n && y >= 0 && y < n && g[x][y]) {
                    union1(x * n + y + 1, i * n + j + 1);
                }
            }
        }
    }
    int res = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (g[i][j]) {
                res = max(res, areas[findf1(i * n + j + 1)]);
            } else {
                int sum = 1;
                unordered_set<int> set;
                for (auto [xx, yy]: dir) {
                    int x = i + xx, y = j + yy;
                    if (x >= 0 && x < n && y >= 0 && y < n && g[x][y]) {
                        int xf = findf1(x * n + y + 1);
                        if (set.find(xf) != set.end()) continue;
                        set.insert(xf);
                        sum += areas[xf];
                    }
                }
                res = max(res, sum);
            }
        }
    }
    return res;
}

int rectangleArea(vector<vector<int>> &rectangles) {
    long long mod = 1e9 + 7;
    vector<int> lines;
    for (auto &item: rectangles) {
        lines.emplace_back(item[0]);
        lines.emplace_back(item[2]);
    }
    sort(lines.begin(), lines.end());
    int res = 0;
    for (int i = 1; i < lines.size(); ++i) {
        int l = lines[i - 1], r = lines[i];
        if (l == r) continue;
        vector<pair<int, int>> edges;
        for (auto &item: rectangles) {
            if (item[0] <= l && item[2] >= r)
                edges.emplace_back(item[1], item[3]);
        }
        sort(edges.begin(), edges.end());
        int up = -1, down = -1;
        long long len = 0;
        for (auto &item: edges) {
            if (item.first > up) {
                len += up - down;
                down = item.first;
                up = item.second;
            } else if (item.second > up) up = item.second;
        }
        len += up - down;
        len *= r - l;
        len %= mod;
        res = (res + len) % mod;
    }
    return res;
}

std::istream &func(std::istream &is) {
    std::string buf;
    while (is >> buf)
        std::cout << buf << std::endl;
    is.clear();
    return is;
}

int res = INT_MAX;

void dfs7(string &s1, string &s2, int start, int cur) {
    if (cur >= res) return;
    if (start == s1.size() - 1) {
        res = min(cur, res);
        return;
    }
    for (int i = start; i < s1.size(); ++i) {
        if (s1[i] != s2[i]) {
            for (int j = i + 1; j < s2.size(); ++j) {
                if (s2[j] == s1[i] && s2[j] != s1[j]) {
                    swap(s2[j], s2[i]);
                    dfs7(s1, s2, i + 1, cur + 1);
                    swap(s2[j], s2[i]);
                    if (s2[i] == s1[j])break;
                }
            }
            return;
        }
    }
    res = min(cur, res);
}

int kSimilarity(string s1, string s2) {
    dfs7(s1, s2, 0, 0);
    return res;
}

bool canFormArray(vector<int> &arr, vector<vector<int>> &pieces) {
    map<int, int> mp;
    for (int i = 0; i < pieces.size(); ++i) mp[pieces[i][0]] = i;
    for (int i = 0; i < arr.size();) {
        if (mp.find(arr[i]) == mp.end()) return false;
        for (auto &item: pieces[mp[arr[i]]]) {
            if (arr[i++] != item) return false;
        }
    }
    return true;
}

vector<int> decrypt(vector<int> &code, int k) {
    if (!k) return vector<int>(code.size(), 0);
    vector<int> v;
    int e = k > 0 ? 1 : k < 0 ? -1 : 0;
    for (int i = 0; i < code.size(); ++i) {
        int sum = 0;
        for (int j = e; j != k + e; j += e) {
            sum += code[(j + i + code.size()) % code.size()];
        }
        v.push_back(sum);
    }
}

vector<int> missingTwo(vector<int> &nums) {
    int xorr = 0;
    int n = nums.size() + 2;
    for (auto &item: nums) xorr ^= item;
    for (int i = 1; i <= n; ++i) {
        xorr ^= i;
    }
    int lone = xorr & (-xorr);
    int t1 = 0, t2 = 0;
    for (auto &item: nums) {
        if (lone & item)
            t1 ^= item;
        else
            t2 ^= item;
    }
    for (int i = 1; i <= n; ++i) {
        if (lone & i)
            t1 ^= i;
        else
            t2 ^= i;
    }
    return {t1, t2};
}

int getKthMagicNumber(int k) {
    vector<int> dp(k + 10, 0);
    int inx1 = 0;
    int inx2 = 0;
    int inx3 = 0;

    dp[0] = 1;
    for (int i = 1; i < k; ++i) {
        int a = dp[inx1] * 3, b = dp[inx2] * 5, c = dp[inx3] * 7;
        int minn = min(a, min(b, c));
        dp[i] = minn;
        if (minn == a) inx1++;
        if (minn == b) inx2++;
        if (minn == c) inx3++;
    }
    return dp[k - 1];
}

int minFlips(int a, int b, int c) {
    int ans = 0;
    while (c) {
        if (c & 1) {
            ans += (b | a) % 2 == 0;
        } else {
            ans += (b & 1) + (a & 1);
        }
        c >>= 1;
        a >>= 1;
        b >>= 1;
    }
    while (a | b) {
        ans += (b & 1) + (a & 1);
        a >>= 1;
        b >>= 1;
    }
    return ans;
}

void setZeroes(vector<vector<int>> &matrix) {
    vector<int> h(matrix.size(), 0), l(matrix[0].size());
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (!matrix[i][j]) h[i] = 1, l[j] = 1;
        }
    }
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (h[i] && l[j])matrix[i][j] = 0;
        }
    }
}


vector<int> smallestRange(vector<vector<int>> &nums) {
    int n = nums.size();
    map<int, vector<int>> mp;
    int l = INT_MAX, r = INT_MIN;
    for (int i = 0; i < n; ++i) {
        for (auto &item: nums[i]) {
            l = min(item, l);
            r = max(item, r);
            mp[item].push_back(i);
        }
    }
    int ansl = l, ansr = r;
    int nowl = l, nowr = l - 1;
    int nowsize = 0;
    vector<int> ve(n, 0);
    while (nowr < r) {
        nowr++;
        if (mp.count(nowr)) {
            for (auto &item: mp[nowr]) {
                ve[item]++;
                if (ve[item] == 1) nowsize++;
            }
        }
        while (nowsize == n) {
            if (nowr - nowl < ansr - ansl) ansl = nowl, ansr = nowr;
            if (mp.count(nowl)) {
                for (auto &item: mp[nowl]) {
                    ve[item]--;
                    if (ve[item] == 0) nowsize--;
                }
            }
            nowl++;
        }
    }
    return {ansl, ansr};
}

int lengthOfLongestSubstring(string s) {
    unordered_set<char> set;
    int n = s.size();
    int ans = 0;
    int last = 0;
    for (int i = 0; i < n; ++i) {
        if (i != 0) set.erase(s[i - 1]);
        while (last < n && !set.count(s[last])) {
            set.insert(s[last]);
            last++;
        }
        ans = max(ans, last - i);
    }
    return ans;
}

string convert(string s, int numRows) {
    if (numRows == 1) return s;
    vector<string> res(numRows, "");
    for (int i = 0; i < s.size(); ++i) {
        int ind = i % (numRows * 2 - 2);
        if (ind >= numRows) ind = (numRows - 1) - (ind - numRows + 1);
        res[ind] += s[i];
    }
    for (int i = 0; i < numRows; ++i) {
        res[0] += res[i];
    }
    return res[0];
}

string reformatNumber(string number) {
    string s;
    for (int i = 0; i < number.size(); ++i) {
        if (isalnum(number[i]))
            s += number[i];
    }
    int n = s.size();
    int f = n % 3;
    if (f == 1 && n > 1)f = 4;
    string s1;
    for (int i = 0; i < n - f; ++i) {
        if (i % 3 == 0 && i != 0) s1 += '-';
        s1 += s[i];
    }
    for (int i = n - f; i < n; ++i) {
        if ((i - n - f) % 2 == 0 && s1.size() != 0) s1 += '-';
        s1 += s[i];
    }
    return s1;
}

vector<string> subdomainVisits(vector<string> &cpdomains) {
    map<string, long> mp;
    for (auto cpdomain: cpdomains) {
        stringstream out(cpdomain);
        int times;
        string domain;
        out >> times >> domain;
        int len = domain.size();
        int pos = -1;
        mp[domain] += times;
        while ((pos = domain.find(".", pos + 1)) != -1) {
            string s = domain.substr(pos + 1);
            mp[s] += times;
        }
    }
    vector<string> res;
    for (auto mmp: mp) {
        res.push_back(to_string(mmp.second) + " " + mmp.first);
    }
    return res;
}

vector<int> advantageCount(vector<int> &nums1, vector<int> &nums2) {
    int n = nums1.size();
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j) { return nums2[i] < nums2[j]; });
    sort(nums1.begin(), nums1.end());
    vector<int> v(n);
    for (int i = 0, j = 0, k = n - 1; i < n; i++) {
        if (nums1[i] <= nums2[idx[j]])
            v[idx[k--]] = nums1[i];
        else
            v[idx[j++]] = nums1[i];
    }
    return v;
}

int scoreOfParentheses(string s) {
    int n = 0, sum = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '(') {
            if (n == 0) {
                n = 1;
            } else {
                n <<= 1;
            }
        } else {
            if (s[i - 1] == ')') {
                n >>= 1;
            } else {
                sum += n;
            }
        }
    }
    return sum;
}

bool areAlmostEqual(string s1, string s2) {
    int f = 0;
    for (int i = 0; i < s1.size(); ++i) {
        if (s1[i] != s2[i]) {
            if (f > 1) return false;
            f++;
        }
    }
    return true;
}

vector<int> threeEqualParts(vector<int> &arr) {
    int sum = accumulate(arr.begin(), arr.end(), 0);
    if (sum % 3) {
        return {-1, -1};
    }
    if (sum == 0) return {0, 2};
    int pa = sum / 3;
    int f = -1, s = -1, t = -1;
    int cur = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == 1) {
            if (cur == 0) f = i;
            else if (cur == pa) s = i;
            else if (cur == pa + pa) t = i;
            cur++;
        }
    }
    int len = arr.size() - t;
    if (f + len <= s && s + len <= t) {
        int pos = 0;
        while (t + pos < arr.size()) {
            if (arr[f + pos] == arr[s + pos] && arr[t + pos] == arr[s + pos]) {
                pos++;
            } else
                return {-1, -1};
        }
        return {f + pos, s + pos};
    }
    return {-1, -1};
}

int minSwap1(vector<int> &nums1, vector<int> &nums2) {
    int n = nums1.size();
    vector<vector<int>> dp(n, vector<int>(2, 0));
    dp[0][0] = 0, dp[0][1] = 1;
    for (int i = 1; i < nums1.size(); i++) {
        if (nums1[i] > nums1[i - 1] && nums2[i] > nums2[i - 1] && nums1[i] > nums2[i - 1] && nums2[i] > nums1[i - 1]) {
            dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]);
            dp[i][1] = min(dp[i - 1][1], dp[i - 1][0]) + 1;
        } else if (nums1[i] > nums2[i - 1] && nums2[i] > nums1[i - 1]) {
            dp[i][1] = dp[i - 1][0] + 1;
            dp[i][0] = dp[i - 1][1];
        } else {
            dp[i][0] = dp[i - 1][0];
            dp[i][1] = dp[i - 1][1] + 1;
        }
    }
    return min(dp[n - 1][0], dp[n - 1][1]);
}

int minSwap(vector<int> &nums1, vector<int> &nums2) {
    vector<vector<int>> dp(nums1.size(), vector<int>(2, 0));
    dp[0][1] = 1;
    for (int i = 1; i < nums1.size(); i++) {
        if (nums1[i] > nums1[i - 1] && nums2[i] > nums2[i - 1] && nums1[i] > nums2[i - 1] && nums2[i] > nums1[i - 1]) {
            dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]);
            dp[i][1] = min(dp[i - 1][1], dp[i - 1][0]) + 1;
        } else if (nums1[i] > nums2[i - 1] && nums2[i] > nums1[i - 1]) {
            dp[i][1] = dp[i - 1][0] + 1;
            dp[i][0] = dp[i - 1][1];
        } else {
            dp[i][0] = dp[i - 1][0];
            dp[i][1] = dp[i - 1][1] + 1;
        }
    }
    return min(dp[nums1.size() - 1][0], dp[nums2.size() - 1][1]);
}

int distinctSubseqII(string s) {
    int mod = 1000000007;
    vector<int> dp(26, 0);
    for (auto x: s) {
        dp[x - 'a'] = accumulate(dp.begin(), dp.end(), 1ll) % mod;
    }
    return accumulate(dp.begin(), dp.end(), 0) % mod;
}

vector<string> buildArray(vector<int> &target, int n) {
    vector<string> v;
    string s1 = "Push", s2 = "Pop";
    int inx = 0;
    for (int i = 1; i <= n; ++i) {
        if (i != target[inx]) {
            v.push_back(s1);
            v.push_back(s2);
        } else {
            v.push_back(s1);
            inx++;
            if (inx == target.size()) return v;
        }
    }
    return v;
}


bool possibleBipartition(int n, vector<vector<int>> &dislikes) {
    vector<int> fa1(n);
    iota(fa1.begin(), fa1.end(), 0);
    for (int i = 0; i < dislikes.size(); ++i) {
        int u = dislikes[i][0], v = dislikes[i][1];
        if (findf(fa1, u) == findf(fa1, v)) {
            return false;
        } else {
            fa[findf(fa1, u)] = findf(fa1, v);
        }
    }
    return true;
}


int fa1[4010];

int find(int x) { return x == fa1[x] ? x : fa1[x] = find(fa1[x]); }

bool possibleBipartition1(int n, vector<vector<int>> &dislikes) {
    for (int i = 0; i <= n * 2; i++)fa1[i] = i;
    for (auto &i: dislikes) {
        int a = find(i[0]), b = find(i[1]);
        if (a == b)return false;
        fa1[find(a + n)] = b;
        fa1[find(b + n)] = a;
    }
    return true;
}

int totalFruit(vector<int> &fruits) {
    int n = fruits.size();
    unordered_map<int, int> mp;
    int ans = 0;
    int left = 0;
    for (int i = 0; i < n; ++i) {
        mp[fruits[i]]++;
        while (mp.size() > 2) {
            auto it = mp.find(fruits[left]);
            if (--(it->second) == 0) {
                mp.erase(it);
            }
            ++left;
        }
        ans = max(ans, i - left + 1);
    }
    return ans;
}

int countStudents(vector<int> &students, vector<int> &sandwiches) {
    vector<int> res(2, 0);
    for (const auto &item: students) res[item]++;
    for (const auto &item: sandwiches)
        if (res[item]) res[item]--;
        else break;
    return res[0] + res[1];
}

int kthGrammar(int n, int k) {
    return __builtin_parity(k - 1);
}

int partitionDisjoint(vector<int> &nums) {
    int nowmax = nums[0];
    int leftMax = nums[0];
    int pos = 0;
    for (int i = 1; i < nums.size(); ++i) {
        nowmax = max(nums[i], nowmax);
        if (nums[i] < leftMax) {
            pos = i;
            leftMax = nowmax;
        }
    }
    return pos + 1;
}

int atMostNGivenDigitSet(vector<string> &digits, int n) {
    string s = to_string(n);
    int ans = 0;
    for (int i = 1; i < s.size(); ++i) {
        ans += pow(digits.size(), i);
    }
    for (int i = 0, j = 0; i < s.size(); ++i) {
        for (j = 0; j < digits.size() && stoi(digits[j]) < s[i] - '0'; ++j);
        ans += j * pow(digits.size(), (s.size() - 1 - i));
        if (i == s.size() - 1 && j < digits.size() && stoi(digits[j]) == s[i] - '0') ans++;
        if (j >= digits.size() || stoi(digits[j]) != s[i] - '0') break;
    }
    return ans;
}

void dfs8(int i, int j, vector <vector<int>> &vector, queue<pair<int, int>> queue1) {
    if (i < 0 || j < 0 || i >= vector.size() || j >= vector[0].size() || vector[i][j] != 1)return;
    queue1.emplace(i, j);
    vector[i][j] = -1;
    dfs8(i - 1, j, vector, queue1);
    dfs8(i + 1, j, vector, queue1);
    dfs8(i, j - 1, vector, queue1);
    dfs8(i, j + 1, vector, queue1);
}

int shortestBridge(vector<vector<int>> &grid) {
    int n = grid.size();
    vector<vector<int>> dirs = {{-1, 0},
                                {1,  0},
                                {0,  1},
                                {0,  -1}};
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.size(); j++) {
            if (grid[i][j] == 1) {
                queue<pair<int, int>> qu;
                dfs8(i, j, grid, qu);
                int step = 0;
                while (!qu.empty()) {
                    int m = qu.size();
                    for (int z = 0; z < m; z++) {
                        auto [x, y] = qu.front();
                        qu.pop();
                        for (int k = 0; k < 4; ++k) {
                            int dx = x + dirs[k][0];
                            int dy = y + dirs[k][1];
                            if (dx >= 0 && dy >= 0 && dx < n && dy < n) {
                                if (grid[dx][dy] == 0) {
                                    qu.emplace(dx, dy);
                                    grid[dx][dy] = -1;
                                } else if (grid[dx][dy] == 1) {
                                    return step;
                                }
                            }
                        }
                    }
                    step++;
                }
            }
        }
    }
    return 0;
}

class Solution {
public:
    int jobScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &profit) {
        int n = startTime.size();
        vector<vector<int>> jobs(n);
        for (int i = 0; i < n; i++) {
            jobs[i] = {startTime[i], endTime[i], profit[i]};
        }
        sort(jobs.begin(), jobs.end(), [](const vector<int> &job1, const vector<int> &job2) -> bool {
            return job1[1] < job2[1];
        });
        vector<int> dp(n + 1);
        for (int i = 1; i <= n; i++) {
            int k = upper_bound(jobs.begin(), jobs.begin() + i - 1, jobs[i - 1][0],
                                [&](int st, const vector<int> &job) -> bool {
                                    return st < job[1];
                                }) - jobs.begin();
            dp[i] = max(dp[i - 1], dp[k] + jobs[i - 1][2]);
        }
        return dp[n];
    }
};


int jobScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &profit) {
    struct job {
        int st;
        int et;
        int pf;
    };
    int n = startTime.size();
    vector<job> jobs(n);
    for (int i = 0; i < n; ++i) jobs[i] = {startTime[i], endTime[i], profit[i]};
    std::sort(jobs.begin(), jobs.end(), [&](job &a, job &b) {
        return a.et < b.et;
    });
    vector<int> dp(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int id = upper_bound(jobs.begin(), jobs.begin() + i - 1, jobs[i - 1].st, [&](int st, job b) {
            return st < b.et;
        }) - jobs.begin();
        dp[i] = max(dp[i - 1], dp[id] + jobs[i - 1].pf);
    }
    return dp[n];
}

long long minCost(vector<int> &nums, vector<int> &cost) {
    int n = nums.size();
    vector<pair<int, int >> vp(n);
    for (int i = 0; i < n; ++i) {
        vp[i] = {nums[i], cost[i]};
    }
    sort(vp.begin(), vp.end());
    long long total = 0;
    long long costSum = 0;
    for (int i = 0; i < nums.size(); ++i) {
        total += (long long) (vp[i].first - vp[0].first) * vp[i].second;
        costSum += vp[i].second;
    }
    long long ans = total;
    for (int i = 1; i < n; ++i) {
        costSum -= vp[i - 1].second * 2;
        total -= costSum * (vp[i].first - vp[i - 1].first);
        ans = min(total, ans);
    }
    return ans;
}

int shortestSubarray(vector<int> &nums, int k) {
    int n = nums.size();
    vector<int> pre(n + 1);
    for (int i = 0; i < n; ++i) {
        pre[i + 1] = pre[i] + nums[i];
    }
    int res = n + 1;
    deque<int> qu;
    for (int i = 0; i < n; ++i) {
        while (!qu.empty() && pre[i] - pre[qu.front()] >= k) {
            res = min(res, i - qu.front());
            qu.pop_front();
        }
        while (!qu.empty() && pre[qu.back()] >= pre[i]) {
            qu.pop_back();
        }
        qu.push_back(i);
    }
    return res < n + 1 ? res : -1;
}

int arraySign(vector<int> &nums) {
    int res = 1;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == 0) return 0;
        res *= nums[i] > 0 ? 1 : -1;
    }
    return res;
}

int sumSubarrayMins(vector<int> &arr) {
    long long mod = 1000000007;
    long long ans = 0;
    for (int i = 0; i < arr.size(); i++) {
        int l = i - 1;
        int r = i + 1;
        while (l >= 0 && arr[i] < arr[l])l--;
        while (r < arr.size() && arr[i] <= arr[r])r++;
        ans = (ans + (r - i) * (i - l) * arr[i]) % mod;
    }
    return (int) ans;
}

int sumSubarrayMins2(vector<int> &arr) {
    int n = arr.size();
    // ???? left[i] ?????????? arr[i] ???????????????????? -1??
    vector<int> left(n, -1);
    stack<int> st;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && arr[st.top()] >= arr[i])
            st.pop(); // ???????????
        if (!st.empty()) left[i] = st.top();
        st.push(i);
    }

    // ???? right[i] ?????????? arr[i] ???????????????????? n??
    vector<int> right(n, n);
    while (!st.empty()) st.pop();
    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && arr[st.top()] > arr[i])
            st.pop(); // ???????????
        if (!st.empty()) right[i] = st.top();
        st.push(i);
    }

    long ans = 0L;
    for (int i = 0; i < n; ++i)
        ans += (long) arr[i] * (i - left[i]) * (right[i] - i); // ??????
    return ans % mod;
}


int minimumDeletions(string s) {
    int res = 0, ans = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'b') {
            ans++;
        } else {
            res = min(ans, res + 1);
        }
    }
    return res;
}

void dfs9(vector<string> &r, string s, int i) {
    if (s.size() == i) {
        r.push_back(s);
        return;
    }
    if (isalnum(s[i])) dfs9(r, s, i + 1);
    else if (isalpha(s[i])) {
        s[i] = tolower(s[i]);
        dfs9(r, s, i + 1);
        s[i] = toupper(s[i]);
        dfs9(r, s, i + 1);
    }
}

vector<string> letterCasePermutation(string s) {
    vector<string> res;
    dfs9(res, s, 0);
    return res;
}

int magicalString(int n) {
    string s = "122";
    char c = '1';
    int sum = 1;
    for (int i = 2; s.size() < n; i++) {
        s += c;
        sum += c == '1';
        if (s.size() < n && s[i] == '2') {
            s += c;
            sum += c == '1';
        }
        c ^= 3;
    }
    return sum;
//    return count(s.begin(), s.begin()+n,'1');
}

void primer8_9() {
    vector<string> v;
    fstream ifs("../dayTask.txt");
    if (ifs.is_open()) {
        string s;
        while (ifs >> s) {
            cout << s << endl;
            if (s.find("30/") != -1)
                ///cout<<s<<" "<<s.size()<<" "<<s.find("30/")<<endl;
                s.replace(s.find("30"), 2, "99");
            v.push_back(s);
        }
        std::for_each(v.begin(), v.end(), [&](const auto &item) {
            ifs << item << endl;
//            ifs.seekp(sizeof(char ));
//            ifs.write(s.c_str(),sizeof(s.c_str()));
        });
    }
    ifs.close();
}

void write_txt() {
    fstream ifs("1.txt", ios::app);
    if (ifs.is_open()) {
        ifs << "22222222222222221122" << endl;
    }
    ifs.close();
}

bool arrayStringsAreEqual(vector<string> &word1, vector<string> &word2) {
    return reduce(word1.begin(), word1.end()) == reduce(word2.begin(), word2.end());
}

int reverse(int x) {
    long n = 0;
    while (x) {
        n = n * 10 + x % 10;
        x /= 10;
    }
    return n > INT_MAX || n < INT_MIN ? 0 : n;
}

int maxArea(vector<int> &height) {
    int ans = 0;
    int l = 0;
    int r = height.size() - 1;
    while (l < r) {
        ans = max(ans, (r - l) * min(height[l], height[r]));
        if (height[l] > height[r]) r--;
        else l++;
    }
    return ans;
}

int maxRepeating(string sequence, string word) {
    int res = 0;
    string tmp = word;
    while (sequence.find(word) != -1) {
        word += tmp;
        res++;
    }
    return res;
}

int myAtoi(string s) {
    int sum=0;
    stringstream liu(s);
    liu>>sum;
    return sum;
}

int reachNumber(int target) {
    int x= abs(target);
    int res=0;
    int i=1;
    while (res<target||(res-target)%2){
        res+=i;
        i++;
    }
    return i;
}

string interpret(string command) {
    while (command.find("()")!=string::npos){
        command.replace(command.find("()"), 2,"o");
    }

    while (command.find("(al)")!=string::npos){
        command.replace(command.find("(al)"), 4,"al");
    }
    return command;
}

void solve() {
    vector<int> i{1, 2};
    vector<int> p{1, 4, 25, 10, 35};
    vector<vector<int>> v{{2, 3},
                          {1, 3},
                          {1, 2}};
//    primer8_9();
//    write_txt();
//    cout << myAtoi("  +-422111dwqwd");
//    string s="T99.gds";
//    cout<<(s.find(".oas")==string::npos);
//    cout<<s.replace(max(s.find(".gds"),s.find(".oas")),4,".tiles");

//    int system1 = system("ls -a");
//    cout << system1<<endl;
    map<int,pair<int,int>>mp;
    mp[1].first=1;
    mp[1].second++;
    mp[1].second++;
    for (auto &item: mp){
        cout<<item.first<<item.second.first<<item.second.second<< endl;
    }
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
