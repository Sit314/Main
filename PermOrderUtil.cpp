#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

template <typename S>
ostream& operator<<(ostream& os, const vector<S>& vector)
{
    for (auto element : vector)
        os << element << " ";
    return os;
}

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

int gcd(const vector<int>& v)
{
    int n = v[0];
    for (int i = 1; i < v.size(); ++i) {
        n = gcd(v[i], n);
        if (n == 1)
            return 1;
    }
    return n;
}

int lcm(int a, int b)
{
    return a * b / gcd(a, b);
}

int lcm(const vector<int>& v)
{
    int n = v[0];
    for (int i = 1; i < v.size(); ++i)
        n = lcm(v[i], n);
    return n;
}

bool isPrime(int n)
{
    if (n <= 1)
        return false;

    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return false;

    return true;
}
