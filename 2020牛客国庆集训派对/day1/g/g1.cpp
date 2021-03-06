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
constexpr int M = 110;
int n, m, g[N], q;
ll f[N]; 

struct Matrix {
	ll a[M][M];
	Matrix() { memset(a, 0, sizeof a); }
	Matrix operator * (const Matrix &other) const {
		Matrix res = Matrix();
		for (int i = 1; i <= m; ++i) {
			for (int j = 1; j <= m; ++j) {
				for (int k = 1; k <= m; ++k) {
					chadd(res.a[i][j], a[i][k] * other.a[k][j] % mod);
				}
			}
		}
		return res;
	}
}res, base;

void qpow(int n) {
	while (n) {
		if (n & 1) res = res * base;
		base = base * base;
		n >>= 1;
	}
}

void run() {
	rd(n, q);
	vector <string> vec(q);
	m = 100;
	for (auto &it : vec) {
		nextInt();
		rd(it);
	}
	sort(all(vec));
	vec.erase(unique(all(vec)), vec.end());
	sort(all(vec), [&](string a, string b) {
		return SZ(a) < SZ(b);			
	});
	vector <string> _vec;
	for (auto &s : vec) {
		int ok = 1;
		for (auto &t : _vec) {
			if (s.find(t) != string::npos) {
				ok = 0;
				break;
			}
		}
		if (ok) _vec.push_back(s);
	}
	memset(g, 0, sizeof g);
	for (auto &it : _vec) ++g[SZ(it)];	
	memset(f, 0, sizeof f);
	f[0] = 1;
	for (int i = 1; i <= m; ++i) {
		f[i] = f[i - 1] * 26;
		f[i] %= mod;
		for (int j = 1; j <= m; ++j) {
			if (j > i) break;
			chadd(f[i], mod - f[i - j] * g[j] % mod);
		}
	}
	if (n <= m) return pt(f[n]);
	res = Matrix();
	base = Matrix();
	base.a[1][1] = 26;
	for (int i = 1; i <= m; ++i) {
		res.a[1][i] = f[m - i + 1];
		base.a[i][1] -= g[i];	
		if (i > 1) base.a[i - 1][i] = 1;
	}
	qpow(n - m);
	pt(res.a[1][1]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = 1;
	//nextInt();
	while (_T--) run(); 
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ": ";
//        run();
//    }
//	while (cin >> n) run();
//	run();
	return 0;
}
