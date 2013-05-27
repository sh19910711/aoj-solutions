
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
    const int TYPES = 3;
    const int LIMIT = 2;
    const int MOD = 10000;
    const int NONE = -1;

    int n, k;
    int A[SIZE];
    int B[SIZE];
    int T[SIZE];
    int memo[SIZE][TYPES][LIMIT];

    int rec( int d, int t, int k ) {
        if ( memo[d][t][k] != NONE )
            return memo[d][t][k];
        if ( d >= n - 1 ) {
            return memo[d][t][k] = ( k == 0 ? 1 : 0 );
        }
        if ( T[d] != NONE )
            if ( T[d] != t )
                return memo[d][t][k] = 0;
        if ( k == 0 ) {
            int res = 0;
            for ( int i = 0; i < TYPES; ++ i ) {
                if ( i != t )
                    res = ( res + rec(d + 1, i, 0) + rec(d + 1, i, 1) ) % MOD;
            }
            return memo[d][t][k] = res;
        }
        return memo[d][t][k] = rec(d + 1, t, 0);
    }

    int solve() {
        for ( int i = 0; i < k; ++ i )
            T[A[i] - 1] = B[i];
        int res = 0;
        for ( int i = 0; i < TYPES; ++ i )
            for ( int j = 0; j < LIMIT; ++ j )
                res = ( res + rec(0, i, j) ) % MOD;
        return res % MOD;
    }
    
    class Solution: public ISolution {
    public:

        void init() {
            for ( int i = 0; i < SIZE; ++ i )
                for ( int j = 0; j < TYPES; ++ j )
                    for ( int k = 0; k < LIMIT; ++ k )
                        memo[i][j][k] = NONE;
            for ( int i = 0; i < SIZE; ++ i )
                T[i] = NONE;
        }
        
        bool input() {
            if ( ! ( cin >> n >> k ) )
                return false;
            for ( int i = 0; i < k; ++ i )
                cin >> A[i] >> B[i];
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

