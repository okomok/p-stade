#define BOOST_AUTO_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/stream_read.hpp>
#include <pstade/oven/single.hpp>
#include <boost/range/iterator_range.hpp>
BOOST_AUTO_TEST_CASE(iterator_range_equals) {
  using namespace pstade::oven;
  using namespace boost;
  using namespace std;

  stringstream ss("1");
//  BOOST_CHECK(equals(make_iterator_range(istreambuf_iterator<char>(ss), istreambuf_iterator<char>()), single('1')));
  BOOST_CHECK(equals(streambuf_read(ss), single('1')));
} 
