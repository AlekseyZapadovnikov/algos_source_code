#include <iostream>

using namespace std;

int soltion(int a, int b, int c, int d, long long k) {
  int cur = a;

  for (long long day = 0; day < k; day++) {
    int rost = cur * b;

    if (rost < c) {
      return 0;
    }

    int next = rost - c;
    if (next > d) {
      next = d;
    }

    if (next == cur) {
      return cur;
    }

    cur = next;
  }

  return cur;
}

int main() {
  int a, b, c, d;
  long long k;

  cin >> a >> b >> c >> d >> k;
  cout << soltion(a, b, c, d, k) << '\n';

  return 0;
}