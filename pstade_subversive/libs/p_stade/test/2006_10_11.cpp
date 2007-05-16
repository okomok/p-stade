#include <pstade/vodka/drink.hpp>


#include <string>
#include <vector>
#include <boost/assert.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/foreach.hpp>
#include <pstade/locale.hpp>
#include <boost/range/adaptors.hpp>


int main()
{
    namespace lambda = boost::lambda;
    namespace loc = pstade;
    namespace ranges = boost::ranges;
    using namespace ranges;

    std::vector<char> out;

    BOOST_FOREACH (char ch,
        new std::string("xOLxLExH")
            | shared
            | filtered(lambda::_1 != 'x') | regularized
            | reversed
            | transformed(loc::to_lower)  | const_refs
            | jointed(", range!\0secret"|as_c_str)
            | memoized
    ) {
        out.push_back(ch);
    }

    BOOST_ASSERT( ranges::equals(out, "hello, range!"|as_literal) );
}
