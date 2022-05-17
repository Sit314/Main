#include "PermOrderUtil.cpp"
#include <string>

using namespace std;

vector<int> primeCache;

vector<vector<int>> getAllSubdevisions(int n)
{
    if (n <= 1) {
        return vector<vector<int>> { {} };
    }

    vector<vector<int>> out;

    for (int i = 2; i <= n; i++) {
        vector<int> v;
        v.push_back(i);
        vector<vector<int>> rest = getAllSubdevisions(n - i);
        for (vector<int> possibleRest : rest) {
            vector<int> toPush(v);
            toPush.insert(toPush.end(), possibleRest.begin(), possibleRest.end());
            out.push_back(toPush);
        }
    }
    return out;
}

string brute(int n)
{
    vector<vector<int>> options = getAllSubdevisions(n);
    vector<int> best = options[0];
    for (vector<int> v : options)
        if (lcm(v) > lcm(best))
            best = v;

    string out = "[ ";
    for (int i : best)
        out += to_string(i) + " ";
    out += "] => " + to_string(lcm(best));
    return out;
}

int main()
{
    for (int n = 1; n <= 1000; n++)
        if (isPrime(n))
            primeCache.push_back(n);

    vector<int> v { 1, 2, 3, 4, 5 };

    cout << "v: " << v << "\n\n";

    cout << "cache: " << primeCache << "\n\n";

    cout << "gcd of (1,2) = " << gcd(1, 2) << "\n";
    cout << "gcd of (2,10) = " << gcd(2, 10) << "\n";
    cout << "gcd of (24,18) = " << gcd(24, 18) << "\n";
    cout << "gcd of (1220,516) = " << gcd(1220, 516) << "\n\n";

    cout << "gcd of (1,2,3,4,5) = " << gcd(v) << "\n";
    cout << "gcd of (2,4,6,8) = " << gcd(vector<int> { 2, 4, 6, 8 }) << "\n";
    cout << "gcd of (660,444,132,876) = " << gcd(vector<int> { 660, 444, 132, 876 }) << "\n\n";

    cout << "lcm of (1,2,3,4,5) = " << lcm(v) << "\n";
    cout << "lcm of (2,4,6,8) = " << lcm(vector<int> { 2, 4, 6, 8 }) << "\n";
    cout << "lcm of (660,444,132,876) = " << lcm(vector<int> { 660, 444, 132, 876 }) << "\n\n";

    cout << "lcm of (1,1,1,2,3) = " << lcm(vector<int> { 1, 1, 1, 2, 3 }) << "\n";
    cout << "lcm of (1,1,2,4) = " << lcm(vector<int> { 1, 1, 2, 4 }) << "\n";
    cout << "lcm of (3,5) = " << lcm(vector<int> { 3, 5 }) << "\n\n";

    // int N = 8;

    // for (vector<int> opt : getAllSubdevisions(N))
    //     cout << opt << "\n";

    for (int N = 2; N < 100; N++)
        cout << N << ": " << brute(N) << "\n";

    return 0;
}
