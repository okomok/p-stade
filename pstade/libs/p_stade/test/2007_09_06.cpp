
#include <pstade/egg/egg.hpp>

using namespace pstade::egg;

int fuse_f(boost::tuples::tuple<int, int>);

typedef
result_of_unfuse<int (*)(boost::tuples::tuple<int,int>), boost::use_default, use_nullary_result>::type
f_t;
   // const f_t = PSTADE_EGG_UNFUSE_L &fuse_f PSTADE_EGG_UNFUSE_R;

int main()
{
}
