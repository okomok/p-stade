
#include <boost/tuple/tuple.hpp>
#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/include/boost_tuple.hpp>
#include <boost/fusion/include/distance.hpp>


int main()
{
    namespace fusion = boost::fusion;

    boost::tuple<int, char> t(3, 'a');

    fusion::distance(fusion::begin(t), fusion::end(t)); // doesn't compile.
}
