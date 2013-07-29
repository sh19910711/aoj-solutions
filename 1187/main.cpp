
// @snippet<sh19910711/contest:headers.cpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <limits>
#include <complex>
#include <functional>
#include <iterator>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

// @snippet<sh19910711/contest:solution/interface.cpp>
namespace solution {
  class SolutionInterface {
  public:
    virtual int run() = 0;
    
  protected:
    virtual void pre_calc() {}
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input() { return false; };
    virtual void output() {};
    
    SolutionInterface() {}
    
  private:
    
  };
}

// @snippet<sh19910711/contest:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
    virtual int run() {
      pre_calc();
      while ( action() );
      return 0;
    }
    
  };
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef std::vector<std::string> VS;
  typedef long long LL;
  typedef int INT;
  typedef std::vector<INT> VI;
  typedef std::vector<VI> VVI;
  typedef std::pair<INT,INT> II;
  typedef std::vector<II> VII;
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  typedef std::map<int, int> Map;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 2000 + 11;
  const int TEAMS = 50 + 11;
  // storages
  int M, T, P, R;
  int m[SIZE];
  int t[SIZE];
  int p[SIZE];
  int j[SIZE];

  class Team {
  public:
    int id;
    int ac;
    Map wa;
    int score;

    Team(): id(0), ac(0), wa(Map()), score(0) {}

    friend bool operator > ( const Team& l, const Team& r ) {
      if ( l.ac > r.ac )
        return true;
      if ( l.ac == r.ac ) {
        if ( l.score < r.score )
          return true;
        if ( l.score == r.score ) {
          if ( l.id > r.id )
            return true;
        }
      }
      return false;
    }

    friend bool operator == ( const Team& l, const Team& r ) {
      return l.ac == r.ac && l.score == r.score;
    }

    friend ostream& operator <<( ostream& os, const Team& team ) {
      return os << "{ id = " << team.id << ", ac = " << team.ac << ", score =" << team.score << "}" << endl;
    }
  };
  Team teams[TEAMS];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      normalize();
      proc_submissions();
      sort_teams();
    }

    void sort_teams() {
      std::sort(teams, teams + T, std::greater<Team>());
    }

    void proc_submissions() {
      for ( int i = 0; i < R; ++ i ) {
        int submission_team_id = t[i];
        int submission_judge = j[i];
        int submission_time = m[i];
        int submission_problem_id = p[i];
        Team& team = teams[submission_team_id];
        if ( submission_judge == 0 ) {
          team.score += submission_time + 20 * team.wa[submission_problem_id];
          team.ac ++;
        } else {
          team.wa[submission_problem_id] ++;
        }
      }
    }

    void normalize() {
      for ( int i = 0; i < R; ++ i ) {
        t[i] --;
      }
      for ( int i = 0; i < T; ++ i ) {
        teams[i].id = i;
      }
    }
    
  private:
    
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
  protected:
    virtual bool action() {
      init();
      if ( ! input() )
        return false;
      solver.solve();
      output();
      return true;
    }

    void init() {
      std::fill(teams, teams + TEAMS, Team());
    }

    bool input() {
      if ( ! ( cin >> M >> T >> P >> R ) )
        return false;
      if ( M == T && T == P && P == R && R == 0 )
        return false;
      for ( int i = 0; i < R; ++ i ) {
        cin >> m[i] >> t[i] >> p[i] >> j[i];
      }
      return true;
    }

    void output() {
      for ( int i = 0; i < T; ++ i ) {
        cout << teams[i].id + 1;
        if ( i + 1 < T ) {
          if ( teams[i] == teams[i + 1] ) {
            cout << "=";
          } else {
            cout << ",";
          }
        }
      }
      cout << endl;
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  return solution::Solution().run();
}
#endif

