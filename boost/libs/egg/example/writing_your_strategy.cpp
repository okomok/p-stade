

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/function_extension.hpp>


#include <boost/egg/pipable.hpp>
#include <boost/egg/const.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>


#include "./egg_example.hpp"


//[code_example_writing_your_strategy_tag
struct your_strategy
{
    template<class _, class Arity, class Index>
    struct apply;

    typedef boost::mpl::vector<by_perfect, by_ref> arity2_bytags;

    template<class _, class Index>
    struct apply<_, boost::mpl::int_<2>, Index> :
        boost::mpl::at<arity2_bytags, Index>
    { };

    template<class _, class Index>
    struct apply<_, boost::mpl::int_<3>, Index>
    {
        typedef by_value type;
    };
};
//]

//[code_example_writing_your_strategy_specializing
namespace boost { namespace egg {

    template<class Lit>
    struct function<Lit, your_strategy>
    {
        BOOST_EGG_FUNCTION_PREAMBLE() /*< This must be placed first. >*/

        Lit m_lit;
        Lit const & little() const { return m_lit; }

    // 0ary
        typename apply_little<Lit const>::type /*< `apply_little` requires `_Lit` to be const-correct. >*/
        operator()() const
        {
            return call_little(m_lit);
        }

    // 2ary: by_perfect, by_ref
        BOOST_EGG_FUNCTION_CALL_OPERATOR((by_perfect)(by_ref), const)
    /*  is expanded to...
        template<class A0, class A1>
        typename apply_little<Lit const, A0, A1>::type
        operator()(A0 &a0, A1& a1) const
        {
            return call_little(m_lit, a0, a1);
        }

        template<class A0, class A1>
        typename apply_little<Lit const, BOOST_EGG_DEDUCED_CONST(A0), A1>::type
        operator()(A0 const &a0, A1 &a1) const
        {
            return call_little(m_lit, a0, a1);
        }
    */

    // 3ary: by_value
        template<class A0, class A1, class A2>
        typename apply_little<Lit const, A0, A1, A2>::type
        operator()(A0 a0, A1 a1, A2 a2) const
        {
            return call_little(m_lit, a0, a1, a2);
        }
    };

} }
//]

void egg_example()
{
}
