#include "A.h"

#include <exception>
#include <iostream>
using namespace std;

void A::f() {}

void convert(double d) {
    static int i = (int)d;
}

void inc(int i) {
    cout << "  (i: " << i << ")\n";

    static int count;
    cout << "  [old count: " << count << "]\n";
    count = i;
    count++;
    cout << "count: " << count << "\n\n";
}

int main() {
    for (int i = 0; i < 5; i++)
        inc(rand());
    return 0;
}
