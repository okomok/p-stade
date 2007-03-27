

// Work around the warning: "BOOST_ERROR" redefined

#if defined(BOOST_ERROR)
    #error 'BOOST_ERROR' name conflict between Boost.Test and <boost/detail/lightweight_test.hpp>
#endif
#include <boost/detail/lightweight_test.hpp>
#undef BOOST_ERROR // Prefer Boost.Test to <boost/detail/lightweight_test.hpp>.
