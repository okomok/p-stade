

#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/transform.hpp>
#include <boost/fusion/include/begin.hpp>


struct klass {};


klass rvalue(int)
{
    return klass();
}

klass const & lvalue(klass const &i)
{
    return i;
}


int main()
{
    boost::fusion::vector<int> seq;

    *boost::fusion::begin(
        boost::fusion::transform(
            boost::fusion::transform(seq, &rvalue), // rvalues
            &lvalue
        )
    );
}
