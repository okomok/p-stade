#include <pstade/vodka/drink.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/result_of_lambda.hpp>
#include <pstade/lambda_bind.hpp>
#include <pstade/oven/detail/deferred_sig.hpp>

using namespace boost;

struct functor {
    template<class Args>
    struct sig {
        typedef typename tuples::element<1, Args>::type type;
    };

    template<class Arg>
    typename sig<tuple<functor, Arg> >::type
    operator()(Arg const& a) const
    {
        return a;
    }
};

template<class F, class Arg>
void g(F const& f, Arg& x)
{
    typename result_of<
        F(Arg&)
    >::type y = f(x);

    (void)y;
}

int main()
{
    using namespace boost::lambda;
    using namespace pstade;
    using namespace pstade::oven::detail;

    typedef char value_type;
    value_type x;
    functor f;

    // using a converter (compiles faster maybe)
    result_of<
        result_of<op_deferred_sig(functor&)>::type(value_type&)
    >::type y = deferred_sig(f)(x);

    // using the bind
    result_of<
        result_of<op_lambda_bind(functor&, op_lambda_1)>::type(value_type&)
    >::type y_ = bind(f, _1)(x);

    // Delay call of f until later.
    g(bind(f, _1), x);

    (void)y; (void)y_;
}
