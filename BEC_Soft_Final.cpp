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
    vector<float> prob(n), zprob(n);
    vector<float> temp(n, 1), ztemp(n, 1), prob_updt(n);
    string rc;

    ll H[u][n];
    cout << "Enter the H matrix of size " << u << " x " << n << ":\n";
    f(i, 0, u)
    f(j, 0, n) cin >> H[i][j];

    cout << "\nEnter Received message:\n";
    cin >> rc;

    f(i, 0, n)
    {
        if (rc[i] == '0')
            prob[i] = 0;
        else if (rc[i] == '1')
            prob[i] = 1;
        else
        prob[i]=0.5;
        zprob[i] = 1 - prob[i];
        prob_updt[i] = prob[i];
    }

    f(i, 0, u)
        f(j, 0, n) if (H[i][j] == 1) c[i].push_back(j);

    int iteration = 0;

    while (1)
    {
        if (iteration > 25)
            break;
        if (iteration != 0)
        {
            int flg = 1;
            f(i, 0, u)
            {
                ll x = 0;
                f(j,0,c[i].size())
                    x ^= (rc[c[i][j]] - '0');
                if (x == 1)
                {
                    flg = 0;
                    break;
                }
            }
            if (flg)
            {
                cout << "\nDecoded Codeword:\n";
                f(i, 0, n)
                cout << rc[i] << " \n"[i == n - 1];
                return;
            }
        }

        f(i, 0, n)
            temp[i] = 1,
            ztemp[i] = 1;

        f(i, 0, u)
        {
            for (auto vn : c[i])
            {
                    float y = 1;
                    f(j, 0, c[i].size())
                    {
                        if (c[i][j] != vn)
                            y *= (1 - 2 * prob_updt[c[i][j]]);
                    }
                    float r1, r2 = 0.5 + (0.5 * y);
                    r1 = 1 - r2;
                    temp[vn] *= r1;
                    ztemp[vn] *= r2;
            }
        }
        f(i, 0, n)
            temp[i] *= prob[i], ztemp[i] *= zprob[i];
        f(i, 0, n)
        {
            float K = (1 / (temp[i] + ztemp[i]));
            temp[i] *= K;
            ztemp[i] *= K;
            prob_updt[i] = temp[i];
        }
        f(i, 0, n)
        {
            if (temp[i] > ztemp[i])
                rc[i] = '1';
            else
                rc[i] = '0';
        }
        iteration++;
    }
    cout << "\nDecoded Codeword:\n";
    f(i, 0, n)
    cout << rc[i] << " \n"[i == n - 1];
}

int main()
{
    solve();
    return 0;
}