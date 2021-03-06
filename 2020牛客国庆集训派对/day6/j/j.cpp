#include <bits/stdc++.h>
using namespace std;
#define endl "\n" 
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
using db = double;
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y, int Mod = mod) { x += y; while (x >= Mod) x -= Mod; while (x < 0) x += Mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int nextInt() { int x; cin >> x; return x; }
void rd() {}
template <class T, class... Ts> void rd(T& arg, Ts&... args) { cin >> arg; rd(args...); }
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
template <template<typename...> class T, typename t, typename... A> 
void err(const T <t> &arg, const A&... args) { for (auto &v : arg) cout << v << ' '; err(args...); }
void ptt() { cout << endl; }
template <class T, class... Ts> void ptt(const T& arg, const Ts&... args) { cout << ' ' << arg; ptt(args...); }
template <class T, class... Ts> void pt(const T& arg, const Ts&... args) { cout << arg; ptt(args...); }
void pt() {}
template <template<typename...> class T, typename t, typename... A>
void pt(const T <t> &arg, const A&... args) { for (int i = 0, sze = arg.size(); i < sze; ++i) cout << arg[i] << " \n"[i == sze - 1]; pt(args...); }
inline ll qpow(ll base, ll n) { assert(n >= 0); ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr int N = 1e5 + 10; 
int n, m, deep[N], fa[N], f[N], d[N], in[N], out[N];
pII e[N];

vector <vector<pII>> G;

void dfs(int u) {
	in[u] = ++*in;
//	int cnt = 0;
	for (auto &it : G[u]) {
		int v = it.fi, id = it.se;
		if (!fa[v]) {
	//		++cnt; 
	//		if (cnt == SZ(G[u])) continue;
			f[id] = 1;
			fa[v] = u;
			deep[v] = deep[u] + 1;
			dfs(v);
		}
	}
	out[u] = *in;
}

void bfs(int u) {
	queue <int> que;
	que.push(u);
	while (!que.empty()) {
		int u = que.front(); que.pop();
		for (auto &it : G[u]) {
			int v = it.fi, id = it.se;
			if (!fa[v]) {
				f[id] = 1;
				fa[v] = u;
				deep[v] = deep[u] + 1;
				que.push(v);
			}
		}
	}
}

bool isSon(int u, int v) { return in[v] >= in[u] && in[v] <= out[u]; }

void dfs1(int u) {
//	if (u != 1) {
		int Min = n + 1, _id = -1, par = -1;
		for (auto &it : G[u]) {
			int v = it.fi, id = it.se;
			if (fa[v] != u) {
				if (_id == -1) {
					Min = deep[v];
					_id = id;
					par = v;
				} else {
					if (isSon(v, u) > isSon(par, u)) {
						Min = deep[v];
						_id = id;
						par = v;
					} else if (deep[v] < Min) {
						Min = deep[v];
						_id = id;
						par = v;
					}
				}
			}
		}
//		assert(_id != -1);
		if (_id != -1) f[_id] = 1;
//	}
	for (auto &it : G[u]) {
		int v = it.fi, id = it.se;
		if (fa[v] == u) dfs1(v);
	}
}

void run() {
	rd(n, m);
	G.clear(); G.resize(n + 1);
	memset(f, 0, sizeof (f[0]) * (m + 5));
	memset(fa, 0, sizeof (fa[0]) * (n + 5));
	memset(d, 0, sizeof (d[0]) * (n + 5));
	*in = 0;
	int p = 1;
	for (int i = 1, u, v; i <= m; ++i) {
		rd(u, v);
		++d[u];
		if (d[u] > d[p]) p = v;
		e[i] = pII(u, v);
		G[u].push_back(pII(v, i));
	}
	fa[p] = p;
	deep[p] = 0;
	dfs(p);
	dfs1(p);
	vector <int> res;
	int sum = 0;
	for (int i = 1; i <= m; ++i) sum += f[i] == 1;
   	for (int i = 1; i <= m; ++i) {
		if (f[i] == 0) {
			if (sum < n * 2) {
				++sum;
				f[i] = 1;
			} else {
				res.push_back(i);
			}
		} 
	}	
	for (auto &i : res)
		pt(e[i].fi, e[i].se);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = nextInt();
	while (_T--) run(); 
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ": ";
//        run();
//    }
//	while (cin >> n) run();
//	run();
	return 0;
}
