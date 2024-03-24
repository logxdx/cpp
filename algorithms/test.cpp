#include <bits/stdc++.h>
using namespace std;

/* TYPES  */
#define int long long
#define ll long long
#define ull unsigned long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vll vector<long long>
#define mii map<int, int>
#define si set<int>
#define sc set<char>

/* FUNCTIONS */
#define f(i,s,e) for(long long int i=s;i<e;i++)
#define cf(i,s,e) for(long long int i=s;i<=e;i++)
#define rf(i,e,s) for(long long int i=e-1;i>=s;i--)
#define pb push_back
#define eb emplace_back

/* INPUTS */
#define mp make_pair
#define showp(x) for(auto y:x) cout<<y.first sp y.second<<endl;
#define take(x) for(auto &y:x) cin>>y
#define show(x) for(auto y:x) cout<<y<<" "; cout<<endl
#define yes cout<<"YES"<<endl
#define no cout<<"NO"<<endl

/* UTILS */
#define max4(a,b,c,d) max(max((a),(b)),max((c),(d)))
#define max3(a,b,c) max(max((a),(b)),(c))
#define min4(a,b,c,d) min(min((a),(b)),min((c),(d)))
#define min3(a,b,c) min(min((a),(b)),(c))

#define sp <<" "<<
#define endl '\n'

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sorta(arr, sz) sort(arr, arr+ sz)
#define sortd(arr, sz) sort(arr, arr+sz, greater<ll>())
#define ff first
#define ss second
#define sz(x) (int)x.size()

#define N 1000000
#define MOD 1000000007
#define PI 3.1415926535897932384626433832795
#define INF 1e18

#define read(type) readInt<type>()
ll min(ll a,int b) { if (a<b) return a; return b; }
ll min(int a,ll b) { if (a<b) return a; return b; }
ll max(ll a,int b) { if (a>b) return a; return b; }
ll max(int a,ll b) { if (a>b) return a; return b; }
ll gcd(ll a,ll b) { if (b==0) return a; return gcd(b, a%b); }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
ll power(ll a,ll b) { ll res=1; while (b>0) { if (b&1) res=res*a; a=a*a; b>>=1; } return res; }
ll power(ll a,ll b,ll m) { ll res=1; while (b>0) { if (b&1) res=(res*a)%m; a=(a*a)%m; b>>=1; } return res; }
ll modinv(ll a,ll m) { return power(a,m-2,m); }
ll mod_add(ll a,ll b,ll m) { return (a%m+b%m)%m; }
ll mod_sub(ll a,ll b,ll m) { return (a%m-b%m+m)%m; }
ll mod_mul(ll a,ll b,ll m) { return ((a%m)*(b%m))%m; }
ll mod_div(ll a,ll b,ll m) { return mod_mul(a,modinv(b,m),m); }
ll fact(ll n) { ll res=1; for (int i=2;i<=n;++i) res=(res*i)%MOD; return res; }

string to_upper(string a) { for (int i=0;i<(int)a.size();++i) if (a[i]>='a' && a[i]<='z') a[i]-='a'-'A'; return a; }
string to_lower(string a) { for (int i=0;i<(int)a.size();++i) if (a[i]>='A' && a[i]<='Z') a[i]+='a'-'A'; return a; }
bool prime(ll a) { if (a==1) return 0; for (int i=2;i<=round(sqrt(a));++i) if (a%i==0) return 0; return 1; }
bool is_palindrome(string s) { for (int i=0;i<(int)s.size()/2;++i) if (s[i]!=s[(int)s.size()-i-1]) return 0; return 1; }
bool is_vowel(char c) { return (c=='a' || c=='e' || c=='i' || c=='o' || c=='u'); }
bool is_consonant(char c) { return !is_vowel(c); }

#define fastio() ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

void solve() {

    

}

signed main() {
    fastio();

    int t;
    cin>>t;
    while(t--) {
        solve();       
    }
    
    return 0;
}