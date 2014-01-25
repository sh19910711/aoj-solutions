
// @snippet<sh19910711/contest-base:headers.cpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <list>
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

// @snippet<sh19910711/contest-base:solution/define_classes.cpp>
namespace solution {
  struct InputStorage;
  struct OutputStorage;
  struct Storages {
    InputStorage* in;
    OutputStorage* out;
  };
  class SolverInterface {
  public:
    virtual const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) = 0;
  };
}

// @snippet<sh19910711/contest-base:solution/interface.cpp>
namespace solution {
  class SolutionInterface {
  public:
    virtual ~SolutionInterface() {};
    virtual int run() = 0;
    SolverInterface* solver;
    Storages* storages;
  protected:
    virtual bool input( InputStorage* s ) = 0;
    virtual void output( const OutputStorage* s ) = 0; 
    virtual void before_all_actions() {}
    virtual void after_all_actions() {}
    virtual void before_action( const int& test_no ) {}
    virtual void after_action( const int& test_no ) {}
    virtual bool action() {
      if ( ! this->input(this->storages->in) ) {
        return false;
      }
      this->output(solver->solve(this->storages->in, this->storages->out));
      return true;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
    virtual ~SolutionBase() {};
    virtual int run() {
      this->before_all_actions();
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      this->after_all_actions();
      return 0;
    }
  };
}

// @snippet<sh19910711/contest:math/extgcd.cpp>
namespace math {
  // 拡張ユークリッド互除法: a*x+b*y=gcd(x,y)
  template <class T> T extgcd( T a, T b, T& x, T& y ) {
    for ( T u = y = 1, v = x = 0; a; ) {
      T q = b / a;
      std::swap( x -= q * u, u );
      std::swap( y -= q * v, v );
      std::swap( b -= q * a, a );
    }
    return b;
  }
}

// @snippet<sh19910711/contest:math/mod_inverse.cpp>
namespace math {
  // @desc mod mでaの逆元を求める
  template <class T> T mod_inverse( T a, T m ) {
    T x, y;
    extgcd( a, m, x, y );
    x %= m;
    while ( x < 0 )
      x += m;
    return x;
  }
}

// @snippet<sh19910711/contest-base:solution/typedef.cpp>
namespace solution {
  using namespace std;
  // typedef math::BigInteger Int;
  typedef long long Int;
  typedef long double Double;
}

// @snippet<sh19910711/contest-base:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const Int EXP_SIZE = 100000 + 11;
  const Int RESULT_NG = -1;
  enum EXCEPTION {
    ZERO_DIVIDED
  };
  
}

// @snippet<sh19910711/contest-base:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  
}

// @snippet<sh19910711/contest-base:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    Int p;
    string exp;
  };
  struct OutputStorage {
    string exp;
    Int result;
    Int p;
  };
}

// @snippet<sh19910711/contest-base:solution/solver-area.cpp>
namespace solution {
  typedef std::list<string> Tokens;
  
  class Eval {
  public:
    const InputStorage* in;
    Tokens tokens;
    Int mod;
    
    bool is_number( const char& c ) {
      return c >= '0' && c <= '9';
    }
    
    bool is_number( const string& s ) {
      return is_number(s[0]);
    }
    
    void generate_tokens( const string& s ) {
      if ( s.empty() ) {
        return;
      }
      tokens.clear();
      string tmp = "";
      tmp += *s.begin();
      for ( string::const_iterator it_i = s.begin() + 1; it_i != s.end(); ++ it_i ) {
        const char& c = *it_i;
        if ( is_number(c) && is_number(tmp[tmp.size() - 1]) ) {
          tmp += c;
        } else {
          tokens.push_back(tmp);
          tmp = "";
          tmp += c;
        }
      }
      if ( tmp != "" ) {
        tokens.push_back(tmp);
        tmp = "";
      }
    }
    
    void show_tokens( bool no_endl = false ) {
      for ( Tokens::iterator it_i = tokens.begin(); it_i != tokens.end(); ++ it_i ) {
        cout << *it_i;
        if ( ! no_endl ) {
          cout << endl;
        }
      }
      cout << endl;
    }
    
    bool is_open_bracket( Tokens::const_iterator cur ) {
      return (*cur)[0] == '(';
    }
    
    bool is_close_bracket( Tokens::const_iterator cur ) {
      return (*cur)[0] == ')';
    }
    
    bool is_multiple_operator( Tokens::const_iterator cur ) {
      return (*cur)[0] == '*';
    }
    
    bool is_divide_operator( Tokens::const_iterator cur ) {
      return (*cur)[0] == '/';
    }
    
    bool is_plus_operator( Tokens::const_iterator cur ) {
      return (*cur)[0] == '+';
    }
    
    bool is_minus_operator( Tokens::const_iterator cur ) {
      return (*cur)[0] == '-';
    }
    
    Int to_int( const string& s ) {
      std::istringstream iss(s);
      Int res;
      iss >> res;
      return res % mod;
    }
    
    string to_string( const Int& x ) {
      std::ostringstream oss;
      oss << x;
      return oss.str();
    }
    
    Tokens::iterator eval_no_bracket( Tokens::iterator it_begin, Tokens::iterator it_end ) {
      // *, /
      for ( Tokens::iterator it_i = it_begin; it_i != it_end; ++ it_i ) {
        Tokens::iterator cur = it_i;
        if ( is_multiple_operator(cur) ) {
          Tokens::iterator prev = cur;
          prev --;
          Tokens::iterator next = cur;
          next ++;
          Int n_prev = to_int(*prev) % mod;
          Int n_next = to_int(*next) % mod;
          Int result = ( n_prev * n_next ) % mod;
          *prev = to_string(result);
          it_i = tokens.erase(it_i);
          it_i = tokens.erase(it_i);
          it_i --;
          it_i --;
        } else if ( is_divide_operator(cur) ) {
          Tokens::iterator prev = cur;
          prev --;
          Tokens::iterator next = cur;
          next ++;
          Int n_prev = to_int(*prev) % mod;
          Int n_next = to_int(*next) % mod;
          if ( n_next == 0 ) {
            throw ZERO_DIVIDED;
          }
          Int n_next_inv = math::mod_inverse(n_next, mod) % mod;
          Int result = ( n_prev * n_next_inv ) % mod;
          *prev = to_string(result);
          it_i = tokens.erase(it_i);
          it_i = tokens.erase(it_i);
          it_i --;
          it_i --;
        }
      }
      
      
      // +, -
      for ( Tokens::iterator it_i = it_begin; it_i != it_end; ++ it_i ) {
        Tokens::iterator cur = it_i;
        if ( is_plus_operator(cur) ) {
          Tokens::iterator prev = cur;
          prev --;
          Tokens::iterator next = cur;
          next ++;
          Int n_prev = to_int(*prev) % mod;
          Int n_next = to_int(*next) % mod;
          Int result = ( n_prev + n_next ) % mod;
          *prev = to_string(result);
          it_i = tokens.erase(it_i);
          it_i = tokens.erase(it_i);
          it_i --;
          it_i --;
        } else if ( is_minus_operator(cur) ) {
          Tokens::iterator prev = cur;
          prev --;
          Tokens::iterator next = cur;
          next ++;
          Int n_prev = to_int(*prev) % mod;
          Int n_next = to_int(*next) % mod;
          Int result = ( mod + n_prev - n_next ) % mod;
          *prev = to_string(result);
          it_i = tokens.erase(it_i);
          it_i = tokens.erase(it_i);
          it_i --;
          it_i --;
        }
      }
      
      return it_begin;
    }
    
    Tokens::iterator remove_brackets( Tokens::iterator it_begin, Tokens::iterator it_end ) {
      Tokens::iterator it_i = it_begin;
      it_i ++;
      string token = *it_i;
      it_i --;
      it_end --;
      while ( it_i != it_end )
        it_i = tokens.erase(it_i);
      *it_i = token;
      return it_i;
    }
    
    Tokens::iterator eval( Tokens::iterator start ) {
      for ( Tokens::iterator it_i = start; it_i != tokens.end(); ++ it_i ) {
        if ( is_open_bracket(it_i) ) {
          Tokens::iterator it_next = it_i;
          it_next ++;
          Tokens::iterator it_ret = eval(it_next);

          // eval internal
          it_i = eval_no_bracket(it_i, it_ret);

          it_next = it_i;
          it_ret ++;
          it_i = remove_brackets(it_next, it_ret);
          it_i --;
        } else if ( is_close_bracket(it_i) ) {
          return it_i;
        }
      }
      return tokens.end();
    }
    
    Int run() {
      mod = in->p;
      generate_tokens(in->exp);
      eval(tokens.begin());
      eval_no_bracket(tokens.begin(), tokens.end());
      return to_int(*tokens.begin());
    }
  };
  
  class Solver: public SolverInterface {
  public:
    Eval eval;
    
    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      eval.in = in;
      out->p = in->p;
      out->exp = in->exp;
      try {
        out->result = eval.run();
      } catch ( EXCEPTION e ) {
        if ( e == ZERO_DIVIDED ) {
          out->result = RESULT_NG;
        }
      }
      return out;
    }
  protected:
  };
}

// @snippet<sh19910711/contest-base:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
    bool input( InputStorage* in ) {
      string line;
      std::getline(std::cin, line);
      line = remove_spaces(line);
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream iss(line);
      return iss >> in->p >> in->exp && in->p;
    }
    void output( const OutputStorage* out ) {
      if ( out->result == RESULT_NG ) {
        std::cout << "NG" << std::endl;
      } else {
        std::cout << out->exp << " = " << out->result << " (mod " << out->p << ")" << std::endl;
      }
    }
    
    string remove_spaces( const string s ) {
      string res;
      for ( string::const_iterator it_i = s.begin(); it_i != s.end(); ++ it_i ) {
        if ( *it_i != ' ' ) {
          res += *it_i;
        }
      }
      return res;
    }
  };
}

// @snippet<sh19910711/contest-base:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  std::cin.sync_with_stdio(false);
  static solution::InputStorage in;
  static solution::OutputStorage out;
  static solution::Storages storages;
  static solution::Solution solution;
  static solution::Solver solver;
  storages.in = &in;
  storages.out = &out;
  solution.storages = &storages;
  solution.solver = &solver;
  return solution.run();
}
#endif




