#include <bits/stdc++.h>
using namespace std;

const int SIZE = 100 + 11;
int n;
int a[SIZE];
int b[SIZE];

bool input() {
  if (cin >> n) {
    for (int i = 0; i < n; ++i) {
      cin >> a[i] >> b[i];
      --a[i];
      --b[i];
    }
    return true;
  }
  return false;
}

int rec(int d, int k) {
  if (d >= 31) {
    return 0;
  }
  int best = 0;
  if (a[k] <= d && d <= b[k]) {
    best = max(best, rec(d + 1, k + 1) + 100);
  }
  return max(best, rec(d + 1, k) + 50);
}

int solve() {
  for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
      if (a[i] > a[j]) {
        swap(a[i], a[j]);
        swap(b[i], b[j]);
      } else if (a[i] == a[j]) {
        if (b[i] < b[j]) {
          swap(a[i], a[j]);
          swap(b[i], b[j]);
        }
      }
    }
  }
  return rec(0, 0);
}

int main() {
  while (input()) cout << solve() << endl;
  return 0;
}
