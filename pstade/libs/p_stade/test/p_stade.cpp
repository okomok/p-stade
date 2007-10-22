
#include <iostream>
#include <utility>
#include <map>
#include <iterator>


namespace std {

template<typename T, typename U>
inline
std::ostream & operator<< (std::ostream & s, std::pair<T,U> const & p)
{
     s << "<" << p.first << "," << p.second << ">";
     return s;

}

}

template<typename K, typename T>
inline
std::ostream & operator<< (std::ostream & s, std::map<K,T> const & m)
{
     s << "(";
     typedef typename std::map<K,T>::value_type t;
     std::copy(m.begin(), m.end(), std::ostream_iterator<t>(s, " "));
     s << ")";
     return s;

}

int main()
{
    std::map<int, int> m;
    std::cout << m;
}
