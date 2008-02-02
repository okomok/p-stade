#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if 0
#include <boost/mpl/has_xxx.hpp>
#undef BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF
#include <pstade/has_xxx.hpp>
#define BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(H, T, D) \
     PSTADE_HAS_TYPE_NAMED(H, T)
#endif


#if 0
#define BOOST_MPL_PLACEHOLDERS_HPP_INCLUDED
#include <boost/mpl/arg.hpp>

namespace boost { namespace mpl {

    struct _1 : arg<1> {};
    struct _2 : arg<2> {};
    struct _3 : arg<3> {};
    struct _4 : arg<4> {};
    struct _5 : arg<5> {};
    struct _ : arg<-1> {};

} }
#endif


#include <boost/mpl/placeholders.hpp>

#if 0 // !defined(__GNUC__)
#include <boost/mpl/lambda.hpp>

struct dummy {};

struct my_mpl_1 : boost::mpl::_1
{
    template<
        typename A1 = void, typename A2 = void,
        typename A3 = void, typename A4 = void, typename A5 = void >
    struct apply : dummy
    {
        typedef A1 type;
    };
};

namespace boost { namespace mpl {

template<  typename Tag >
struct lambda< my_mpl_1, Tag >
{
    typedef true_ is_le;
    typedef my_mpl_1 result_;  // qualified for the sake of MIPSpro 7.41
    typedef mpl::protect<result_> type;
};

namespace aux {


    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
        >
    struct resolve_bind_arg< my_mpl_1, U1, U2, U3, U4, U5 >
    {
        typedef typename apply_wrap5<my_mpl_1, U1, U2, U3, U4, U5>::type type;
    };

}

}}

#else
typedef boost::mpl::_1 my_mpl_1;
#endif




#if 0
namespace boost { namespace mpl {

    template<>
    struct is_placeholder<my_mpl_1> :
        boost::mpl::true_
    { };

}}
#endif



#include <pstade/has_xxx.hpp>
        PSTADE_HAS_TYPE(anything)

        template<class F>
        struct msvc_identity
        {
            // For some reason, template pod functors need this.
            static bool const b = has_anything<F>::value;
            typedef F type;
        };


#include <pstade/egg/detail/as_mpl_lambda.hpp>
#include <boost/test/minimal.hpp>


#include <pstade/test.hpp>
#include <pstade/egg/ambi.hpp>
#include <pstade/egg/polymorphic.hpp>
#include <pstade/egg/function_facade.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/oven.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>

#if 0
    namespace pstade { namespace oven {


        template<int I>
        struct range_value< boost::mpl::arg<I> >
        {
            template<class Range>
            struct apply :
                range_value<Range>
            { };
        };

    } }
#endif


namespace pstade { namespace oven {
namespace counting_from_detail {


    template< class Incrementable >
    struct base
    {
        typedef typename
            pass_by_value<Incrementable>::type
        inc_t;

        typedef typename
            boost::result_of<
                T_counting(Incrementable&, inc_t)
            >::type
        result_type;

        result_type operator()(Incrementable& i) const
        {
            return counting(i, (std::numeric_limits<inc_t>::max)());
        }
    };


} // namespace counting_from_detail

typedef PSTADE_EGG_DEFER((counting_from_detail::base<boost::mpl::_>)) T_counting_from;
T_counting_from counting_from;
} } // namespace pstade::oven


template< class Lambda >
struct base_op_front :
    pstade::egg::function_facade< base_op_front<Lambda> >
{
//    typedef typename boost::mpl::lambda<Lamdba>::type mf_t;

    template< class Me, class Range >
    struct apply
    {
        typedef typename boost::mpl::apply1<typename boost::mpl::lambda<Lambda>::type, Range>::type type;
    };

    template< class Re, class Range >
    Re call(Range& rng) const
    {
        return *boost::begin(rng);
    }
};


typedef pstade::egg::result_of_ambi0<
    ::base_op_front<PSTADE_EGG_AS_MPL_LAMBDA((pstade::oven::range_value<boost::mpl::_>))>
>::type T_my_value_front;
T_my_value_front my_value_front;


namespace lambda = boost::lambda;
namespace oven = pstade::oven;
using namespace oven;


typedef
    any_range<int, boost::single_pass_traversal_tag>
range;

range sieve(range rng)
{
    return rng|dropped(1)|filtered(regular(lambda::_1 % ::my_value_front(rng) != 0));
}

range primes( iteration(range(counting_from(2)), &::sieve)|transformed(::my_value_front) );


void test()
{
    (primes|taken(200));
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
