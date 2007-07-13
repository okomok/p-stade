
#include <boost/fusion/include/as_vector.hpp>
#include <boost/fusion/include/transform_view.hpp>
#include <boost/fusion/include/vector.hpp>


struct identity
{
    template<class FunCall>
    struct result;

    template<class Fun>
    struct result<Fun(int&)>
    {
        typedef int& type;
    };

    int& operator()(int& i) const
    {
        return i;
    }
};


int main()
{
    typedef boost::fusion::vector<int, int> from_t;
    from_t from;
    boost::fusion::transform_view<from_t, ::identity> v(from, ::identity());

    boost::fusion::as_vector(v);
}
