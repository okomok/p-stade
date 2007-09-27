#include <vector>
#include <pstade/oven/sub_range.hpp>

using namespace pstade::oven;

int main(int argc, char* argv[])
{
    typedef std::vector< int > VectorType;
    VectorType v;
    sub_range< VectorType > range;
    sub_range< VectorType > range1;
    range = range1;
        return 0;
}
