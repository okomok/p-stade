#include <pstade/vodka/drink.hpp>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <functional>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/iterator/counting_iterator.hpp>

//copied from boost
template<class InIt, class OutIt>
InIt copy_n(InIt first, typename std::iterator_traits<InIt>::difference_type length, OutIt dest) {
      for (; length--; ++dest, ++first)
            *dest = *first;
   return first;
}
//Newton square root "improve" method modeling forward traversal iterator.
class improve_increment
: public boost::iterator_facade<improve_increment, float, boost::forward_traversal_tag> {
      const float x_;
      float y_;
      friend class boost::iterator_core_access;
      void increment() { y_ = (y_ + x_/y_)/2; }
      bool equal(improve_increment const& other) const { return y_ == other.y_; };
      const float& dereference() const { return y_; } //why won't this convert?
public:
      improve_increment(const float& x=0) : x_(x), y_(1) { }
      operator float() const { return y_; } //hack?
};
//Counting iterator adaptor to "count" over improvements.
typedef boost::counting_iterator<improve_increment> improve_iterate;
//Newton square root predicate to filter incremental "improve" outputs.
class satisfactory_test : public std::unary_function<const float&, bool> {
      const float x_;
      const float d_;
public:
      satisfactory_test(const float& x=0, const float& d=0.01) : x_(x), d_(d) { }
      bool operator()(const float& y) const {
            return abs ((y * y) - x_) < d_;
      }
};
//Top level iterator to filter improvements from test.
typedef boost::filter_iterator<satisfactory_test, improve_iterate> satisfactory_filter;
//Dump out the first 10 increments of the two iterators.
void main(void) {
      std::cout.precision(10);
      copy_n(
boost::make_counting_iterator(improve_increment(27.3F)),
10,
std::ostream_iterator<float>(std::cout, " ")
);
      copy_n(
boost::make_filter_iterator(satisfactory_test(27.3F, 0.001F), improve_iterate(27.3F)),
10,
std::ostream_iterator<float>(std::cout, " ")
);
}
