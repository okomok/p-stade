#include <vector>
#include <boost/range/sub_range.hpp>
#include <pstade/oven/sub_range.hpp>

using namespace boost;

int main(int argc, char* argv[])
{
    typedef std::vector< int > VectorType;
    VectorType v;
    sub_range< VectorType > range(v);
    sub_range< VectorType > range1(v);
    range = range1;
    return 0;
}
