#include <bits/stdc++.h>
using namespace std;

const int SIZE = 10 + 11;

typedef long long Int;
typedef map<Int, Int> IntMap;

Int n, a, d;
Int m;
Int x[SIZE];
Int y[SIZE];
Int z[SIZE];
Int k;

bool input() {
  if (cin >> n >> a >> d) {
    if (cin >> m) {
      for (Int i = 0; i < m; ++i) {
        cin >> x[i] >> y[i] >> z[i];
      }
      cin >> k;
      return true;
    }
  }
  return false;
}

Int solve() {
  IntMap arr;

  for (Int i = 0; i < m; ++i) {
    arr[y[i]] = a + (y[i] - 1) * d;
    arr[z[i]] = a + (z[i] - 1) * d;
  }
  arr[k] = a + (k - 1) * d;

  for (Int i = 0; i < m; ++i) {
    if (x[i]) { // update
      arr[y[i]] = arr[z[i]];
    } else { // swap
      Int c = arr[y[i]];
      arr[y[i]] = arr[z[i]];
      arr[z[i]] = c;
    }
  }

  return arr[k];
}

int main() {
  while (input()) cout << solve() << endl;
  return 0;
}
