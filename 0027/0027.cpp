
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

// @snippet<sh19910711/contest:misc/date.cpp>
namespace misc {
    class Date {
    public:
        int getYear() { return yy; }
        int getMonth() { return mm; }
        int getDate() { return dd; }
        int getDay() {
            int y = yy, m = mm;
            if ( mm <= 2 ) y -= 1, m += 12;
            int k = y % 100, j = y / 100;
            return ( dd + 13*(m+1)/5 + k + k/4 + j/4 + 5*j + 5 ) % 7;
        }
        static std::string getDayString( const int& day ) {
            const std::string T[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
            return T[day];
        }
        void init( const int& yy_, const int& mm_, const int& dd_ ) { yy = yy_, mm = mm_, dd = dd_; }
        static bool isLeapYear( int y ) { return y % 100 == 0 ? y % 400 == 0 : y % 4 == 0; }
        virtual std::string toString() {
            std::ostringstream oss;
            oss << std::setw(4) << std::setfill('0') << yy << "/";
            oss << std::setw(2) << std::setfill('0') << mm << "/";
            oss << std::setw(2) << std::setfill('0') << dd;
            return oss.str();
        }
        Date& operator ++() {
            dd ++;
            int ld = this->days[mm] + ( mm == 2 && Date::isLeapYear(yy) ? 1 : 0 );
            if ( dd > ld ) dd = 1, mm ++;
            if ( mm > 12 ) mm = 1, yy ++;
            return *this;
        }
        Date& operator --() {
            dd --;
            if ( dd == 0 ) mm --;
            if ( mm == 0 ) mm = 12, yy --;
            int ld = this->days[mm] + ( mm == 2 && Date::isLeapYear(yy) ? 1 : 0 );
            dd = ld;
            return *this;
        }
    protected:
        int yy, mm, dd;
        friend bool operator <( const Date& l, const Date& r ) {
            return l.yy == r.yy ? ( l.mm == r.mm ? ( l.dd == r.dd ? false : l.dd < r.dd ) : l.mm < r.mm ) : l.yy < r.yy;
        }
        friend bool operator ==( const Date& l, const Date& r ) {
            return l.yy == r.yy && l.mm == r.mm && l.dd == r.dd;
        }
        friend bool operator <=( const Date& l, const Date& r ) {
            return operator <(l, r) || operator ==(l, r);
        }
    private:
        static const int days[13];
    };
    const int Date::days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
}


// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
    using namespace std;
    
    int m, d;
    
    class Solution: public ISolution {
    public:
        bool input() {
            if ( ! ( cin >> m >> d ) )
                return false;
            if ( m == 0 && d == 0 )
                return false;
            return true;
        }
        string solve() {
            misc::Date date;
            date.init( 2004, m, d );
            return misc::Date::getDayString(date.getDay());
        }
        void output( string result ) {
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




