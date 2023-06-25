#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef long double ld;
#define f(i, x, n) for (ll i = x; i < n; i++)
#define rf(i, x, n) for (ll i = x; i >= n; i--)
#define all(v) v.begin(), v.end()
const ll N = 1e5 + 5;
ll const p = 1e9 + 7;

void solve()
{
    ll n, k;
    cout << "Enter the value of n: ";
    cin >> n;
    cout<< "\nEnter the value of k: ";
    cin >> k;
    cout<<endl;
    ll u = n - k;

    vector<int> c[u];
    string rc, temp;

    ll H[u][n];
    cout << "Enter the H matrix of size " << u << " x " << n << ":\n";
    f(i, 0, u)
    f(j, 0, n) cin >> H[i][j];

    cout << "\nEnter Received message:\n";
    cin >> rc;
    temp=rc;

    f(i, 0, u)
    f(j, 0, n) if (H[i][j] == 1) c[i].push_back(j);

    int cnte = 0;
    f(i, 0, n) if (rc[i] == 'e') cnte++;

    int iteration=0;

    while (1)
    {
        if (cnte == 0 || iteration>25 || (temp==rc && iteration!=0))
            break;

        f(i, 0, u)
        {
            for (auto vn : c[i])
            {
                if (rc[vn] == 'e')
                {
                    ll x = 0, flag = 1;
                    f(j, 0, c[i].size())
                    {
                        if (c[i][j] != vn)
                        {
                            if (rc[c[i][j]] != 'e')
                                x ^= (rc[c[i][j]] - '0');
                            else
                            {
                                flag = 0;
                                break;
                            }
                        }
                    }
                    temp=rc;
                    if (flag)
                    {
                        rc[vn]=x+'0';
                        cnte--;
                        if(cnte==0)
                        {
                            cout << "\nDecoded Codeword:\n";
                            f(i,0,n)
                            cout<<rc[i]<<" \n"[i==n-1];
                            return;
                        }
                    }
                }
            }
        }
        iteration++;
    }
    cout<<"Could not decode the codeword fully!!"<<endl;
    cout << "\nHere is the partially decoded codeword:\n";
    f(i,0,n)
    cout<<rc[i]<<" \n"[i==n-1];
}

int main()
{
    solve();
    return 0;
}