#include <bits/stdc++.h>
using namespace std;

string s;

bool input() {
  return cin >> s;
}

string convert(string s) {
  string res;
  for (int i = 0; i < 1000; ++i) {
    for (char c = '0'; c <= '9'; ++c) {
      for (auto& x : s) {
        if (x == c) {
          res += x;
          x = '@';
          break;
        }
      }
    }
    for (char c = 'a'; c <= 'z'; ++c) {
      for (auto& x : s) {
        if (x == c) {
          res += x;
          x = '@';
          break;
        }
      }
    }
  }
  return res;
}

int count(const string& s, int k) {
  int res = 1;
  for (int i = k; i + 1 < (int)s.size(); ++i) {
    if (s[i + 1] - s[i] == 1) {
      res ++;
    } else {
      break;
    }
  }
  return res;
}

int solve() {
  string t = convert(s);
  int res = 0;
  for (int i = 0; i < (int)t.size();) {
    int cnt = count(t, i);
    if (cnt >= 3) {
      res += 3;
    } else {
      res += cnt;
    }
    i += cnt;
  }
  return res;
}

int main() {
  while (input()) cout << solve() << endl;
  return 0;
}
