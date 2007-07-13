

#include <boost/fusion/functional/adapter/unfused_lvalue_args.hpp>


struct foo
{
    template<class FunCall>
    struct result;

    template<class Seq>
    struct result<Seq>
    {
        BOOST_STATIC_ASSERT((boost::fusion::size<Seq>::value != 0));
        typedef int type;
    };

    void operator()(Sequence const& seq) const
    {
    }
};

int main()
{
    int i = 0;
    boost::fusion::make_unfused_lvalue_args(foo());
}
