#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <iostream> 
#include <map> 

template<class Map>
struct key_holder
{
    typedef typename Map::key_type key_t;
    key_t m_key;
    key_t operator *() const { return m_key; }
    operator bool() const { return false; }

    template<class Iter>
    key_holder(Iter it) {
        m_key = it->first;
    }
};

template<class Map>
struct mapped_holder
{
    typedef typename Map::mapped_type mapped_t;
    mapped_t m_mapped;
    mapped_t operator *() const { return m_mapped; }
    operator bool() const { return false; }

    template<class Iter>
    mapped_holder(Iter it) {
        m_mapped = it->second;
    }
};


#define FOREACH(A, Key, Value, Hash) \
    for (Hash::iterator INAME = A.begin(); INAME != A.end(); ++INAME) \
        for (bool continue_ = true; continue_;) \
            for (Hash::key_type Key = INAME->first; continue_;) \
                for (Hash::mapped_type Value = INAME->second; continue_; continue_ = false) \
/**/


using namespace std; 
typedef map<int, double> hash; 

inline bool set_false(bool &b) { return b = false; }


int test_main(int, char *[])
{ 
  hash a; 

  a[0] = 1.71; 
  a[1] = 3.14;
  a[2] = 5.01;

  FOREACH(a, k, v, hash) 
    cout << k << "->" << v << "\n";

  return 0; 
} 
