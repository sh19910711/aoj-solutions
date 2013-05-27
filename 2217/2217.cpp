
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

// @snippet<sh19910711/contest:solution/interface.cpp>
namespace solution {
    class ISolution {
    public:
        virtual void init() {};
        virtual bool input() { return false; };
        virtual void output() {};
        virtual int run() = 0;
    };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
    using namespace std;

    const int SIZE = 100 + 11;
    const int NONE = -1;

    int n;
    int X[SIZE][SIZE];
    int Y[SIZE][SIZE];
    bool V[SIZE][SIZE];
    bool filled[SIZE][SIZE];

    void check_init() {
        for ( int i = 0; i < SIZE; ++ i )
            for ( int j = 0; j < SIZE; ++ j )
                V[i][j] = false;
    }

    bool check( int x, int y, int sx, int sy ) {
        if ( V[x][y] )
            return x == sx && y == sy;
        V[x][y] = true;
        int nx = X[x][y];
        int ny = Y[x][y];
        return check(nx, ny, sx, sy);
    }

    void fill( int x, int y ) {
        if ( filled[x][y] )
            return;
        filled[x][y] = true;
        int nx = X[x][y];
        int ny = Y[x][y];
        fill(nx, ny);
    }

    int solve() {
        int res = 0;
        for ( int y = 0; y < n; ++ y ) {
            for ( int x = 0; x < n; ++ x ) {
                check_init();
                if ( ! filled[x][y] && check(x, y, x, y) ) {
                    res ++;
                    fill(x, y);
                }
            }
        }
        return res;
    }
    
    class Solution: public ISolution {
    public:

        void init() {
            for ( int i = 0; i < SIZE; ++ i )
                for ( int j = 0; j < SIZE; ++ j )
                    filled[i][j] = false;
        }
        
        bool input() {
            if ( ! ( cin >> n ) )
                return false;
            if ( n == 0 )
                return false;
            for ( int y = 0; y < n; ++ y ) {
                for ( int x = 0; x < n; ++ x ) {
                    cin >> X[x][y] >> Y[x][y];
                }
            }
            return true;
        }

        void output( int result ) {
            cout << result << endl;
        }
        
        int run() {
            while ( init(), input() ) {
                output(solve());
            }
            return 0;
        }
        
    };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
    return solution::Solution().run();
}

