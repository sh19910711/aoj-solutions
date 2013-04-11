
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
    class ISolution {
    public:
        virtual void init() {};
        virtual bool input() { return false; };
        virtual void output() {};
        virtual int run() = 0;
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

// @snippet<sh19910711/contest:io/config.cpp>
namespace io {
    const std::string OUTPUT_VECTOR_DELIMITER = ",";
}

// @snippet<sh19910711/contest:io/vector.cpp>
namespace io {
    template <typename T> std::ostream& operator <<( std::ostream& os, const std::vector<T>& v ) {
        typedef typename std::vector<T>::const_iterator Iterator;
        for ( Iterator it_i = v.begin(); it_i != v.end(); ++ it_i ) {
            os << *it_i;
            if ( it_i + 1 != v.end() )
                os << OUTPUT_VECTOR_DELIMITER;
        }
        return os;
    }
    template <typename T> std::istream& operator >>( std::istream& is, std::vector<T>& v ) {
        int n = v.size();
        for ( int i = 0; i < n; ++ i ) {
            is >> v[i];
        }
        return is;
    }
}

// @snippet<sh19910711/contest:table/trie.cpp>
namespace table {
    // @desc トライ木の実装
    template <class ValueType> class Trie {
    public:
        typedef std::vector<int>::const_iterator Iterator;
        static const int SIZE = 5;
        ValueType value;
        Trie *next[SIZE];
        Trie() { clear(); }
        void clear() { value = false; std::fill( next, next+SIZE, (Trie*)NULL ); }
        Trie& find( const std::vector<int>& s ) {
            Trie* res = this;
            for ( Iterator it_i = s.begin(); it_i != s.end(); ++ it_i ) {
                const int& c = *it_i;
                if ( ! res->next[c] ) res->next[c] = new Trie;
                res = res->next[c];
            }
            return *res;
        }
        ValueType& operator []( const std::vector<int>& s ) { return find(s).value; }
    };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
    using namespace std;
    using namespace io;

    typedef table::Trie<bool> Trie;
    typedef pair<int,VI> Node;
    typedef queue<Node> Queue;
    
    const int SIZE = 4;
    const int NONE = -1;
    const int dr[4] = { 1, -1, 0, 0 };
    const int dc[4] = { 0, 0, 1, -1 };
    
    VI M;
    Trie V;
    VI goal(SIZE * SIZE, 0);

    void init_global() {
        M = VI(SIZE * SIZE, 0);
        goal = VI(SIZE * SIZE, 0);
    }
    
    inline int mapping( int r, int c ) {
        return r * SIZE + c;
    }

    void drop( int r, int c ) {
        M[mapping(r, c)] ++;
    }

    bool test( int r, int c ) {
        bool res = false;
        for ( int k = 0; k < 4; ++ k ) {
            for ( int d = 1; d <= SIZE; ++ d ) {
                int nr = r + d * dr[k];
                int nc = c + d * dc[k];
                if ( nr < 0 || nr >= SIZE || nc < 0 || nc >= SIZE )
                    continue;
                if ( M[mapping(nr, nc)] ) {
                    M[mapping(nr, nc)] ++;
                    res |= true;
                    break;
                }
            }
        }
        return res;
    }

    bool update() {
        bool res = false;
        for ( int r = 0; r < SIZE; ++ r ) {
            for ( int c = 0; c < SIZE; ++ c ) {
                if ( M[mapping(r, c)] >= 5 ) {
                    test(r, c);
                    M[mapping(r, c)] = 0;
                    res |= true;
                }
            }
        }
        return res;
    }

    int bfs( VI start_state ) {
        Queue Q;
        Node start(0, start_state);
        Q.push(start);

        V.clear();
        V[start_state] = true;
        
        while ( ! Q.empty() ) {
            Node node = Q.front();
            Q.pop();

            int C = node.first;
            VI T = node.second;

            if ( T == goal )
                return C;

            for ( int r = 0; r < SIZE; ++ r ) {
                for ( int c = 0; c < SIZE; ++ c ) {
                    if ( T[mapping(r, c)] ) {
                        M = T;
                        drop(r, c);
                        while( update() );

                        int NC = C + 1;
                        if ( NC > 5 )
                            continue;
                        VI NM = M;
                        if ( V[NM] )
                            continue;
                        V[NM] = true;
                        Q.push(Node(NC, NM));
                    }
                }
            }
        }

        return NONE;
    }

    class Solution: public ISolution {
    public:
        
        bool input() {
            if ( ! ( cin >> M[mapping(0, 0)] ) )
                return false;
            for ( int i = 0; i < SIZE; ++ i )
                for ( int j = 0; j < SIZE; ++ j )
                    if ( i != 0 || j != 0 )
                        cin >> M[mapping(i, j)];
            return true;
        }
        
        int solve() {
            return bfs(M);
        }

        void output( int result ) {
            cout << result << endl;
        }
        
        int run() {
            init_global();
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

