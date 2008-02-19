#include <boost/tuple/tuple.hpp>
#include <boost/iterator/zip_iterator.hpp>
#include <map>
#include <boost/ptr_container/ptr_map.hpp>
#include <pstade/oven/detail/zip_iterator_hack.hpp>

using boost::zip_iterator;
using boost::tuple;
using boost::make_tuple;
using boost::ptr_map;
using std::map;

int main() {
  //typedef map<int, int> theMapType;
  typedef boost::ptr_map<int, int> theMapType;
  typedef zip_iterator
     <tuple<theMapType::iterator, theMapType::iterator> > zipIter;
  theMapType map1;
  theMapType map2;
  zipIter(make_tuple(map1.begin(), map2.begin()));
}
