

#include <boost/utility/result_of.hpp>
using boost::result_of;


struct an_incomplete;

struct foo
{
    typedef an_incomplete result_type;

    result_type operator()(an_incomplete) const;
};


typedef result_of<foo(an_incomplete)>::type incom_t;

int main() {}
