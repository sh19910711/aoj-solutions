#include <bits/stdc++.h>
using namespace std;

const int SIZE = 30;
int h, w;
string m[SIZE];

bool input() {
  if (cin >> h >> w) {
    for (int i = 0; i < h; ++i) {
      cin >> m[i];
    }
    return true;
  }
  return false;
}

typedef tuple<int, int, int> node_t; // (steps, r, c)
typedef priority_queue<node_t, vector<node_t>, greater<node_t>> queue_t;

queue_t q;
const int dr[4] = {1, -1, 0, 0};
const int dc[4] = {0, 0, 1, -1};
const char START = 'S';
const char GOAL = 'G';
int mc[SIZE][SIZE];

bool outer(int r, int c) {
  return r < 0 || r >= h || c < 0 || c >= w;
}

bool invalid(int r, int c) {
  return m[r][c] == '#' || m[r][c] == 'x';
}

bool ok(int r, int c) {
  return m[r][c] == 'o';
}

bool goal(int r, int c) {
  return m[r][c] == GOAL;
}

void push(const node_t& node) {
  auto steps = get<0>(node);
  auto r = get<1>(node);
  auto c = get<2>(node);
  if (steps >= mc[r][c]) return;
  mc[r][c] = steps;
  q.push(node);
}

int solve() {
  int sr, sc;
  sr = sc = -1;
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (m[i][j] == START) {
        sr = i;
        sc = j;
      }
    }
  }
  assert(sr != -1);
  assert(sc != -1);
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      mc[i][j] = numeric_limits<int>::max();
    }
  }

  q = queue_t();
  q.emplace(0, sr, sc);

  while (!q.empty()) {
    node_t node = q.top();
    q.pop();

    auto steps = get<0>(node);
    auto r = get<1>(node);
    auto c = get<2>(node);

    if (goal(r, c)) return steps;

    // normal
    for (int k = 0; k < 4; ++k) {
      auto nr = r + dr[k];
      auto nc = c + dc[k];
      if (outer(nr, nc) || invalid(nr, nc)) continue;
      auto nsteps = steps + (ok(nr, nc) ? 1 : 2);
      push(node_t(nsteps, nr, nc));
    }

    // paint
    for (int k = 0; k < 4; ++k) {
      for (int i = 1; i <= 3; ++ i) {
        auto nr = r + dr[k] * i;
        auto nc = c + dc[k] * i;
        if (outer(nr, nc)) break;
        if (m[nr][nc] == '#') break;
        auto nsteps = steps + 2 + i;
        push(node_t(nsteps, nr, nc));
      }
    }
  }

  return -1;
}

int main() {
  while (input()) cout << solve() << endl;
  return 0;
}
