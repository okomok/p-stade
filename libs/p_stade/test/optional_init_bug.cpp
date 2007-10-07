#include <boost/optional/optional.hpp>
#include <boost/detail/lightweight_test.hpp>


int main()
{
    int const i = 10;
    boost::optional<int const &> o = i; // copy-initialization
    BOOST_TEST(&*o == &i); // failed on gcc3.4 and 4.1.

    return boost::report_errors();
}
