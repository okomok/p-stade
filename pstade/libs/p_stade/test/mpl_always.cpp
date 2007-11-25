

#include <boost/mpl/apply.hpp>
#include <boost/mpl/always.hpp>

typedef boost::mpl::apply< boost::mpl::always<int> >::type should_be_int;

int main() {}
