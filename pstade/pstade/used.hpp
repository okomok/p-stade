#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_USED_HPP
#define PSTADE_USED_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/instance.hpp>


#if !defined(PSTADE_USED_MAX_ARITY)
    #define PSTADE_USED_MAX_ARITY 20
#endif


namespace pstade {


namespace used_detail {


    template< class T > inline
    void aux(T const& x)
    {
        void const * volatile p = boost::addressof(x);
        (void)p;
    }


} // namespace used_detail


struct used_fun
{
    typedef void result_type;

    // 0ary
    void operator()() const
    { }

    // 1ary
    template< class A0 >
    void operator()(A0 const& a0) const
    {
        used_detail::aux( a0 );
    }

    // 2ary
    template< class A0, class A1 >
    void operator()(A0 const& a0, A1 const& a1) const
    {
        used_detail::aux( a0 );
        used_detail::aux( a1 );
    }

    // 3ary -
    #define PSTADE_USED_arg(Z, N, _) \
        BOOST_PP_CAT(A, N) const& BOOST_PP_CAT(a, N) \
    /**/

    #define PSTADE_USED_body(Z, N, _) \
        used_detail::aux( BOOST_PP_CAT(a, N) ); \
    /**/

    #define BOOST_PP_ITERATION_PARAMS_1 (3, (3, PSTADE_USED_MAX_ARITY, <pstade/used.hpp>))
    #include BOOST_PP_ITERATE()

    #undef PSTADE_USED_arg
    #undef PSTADE_USED_body
};


PSTADE_INSTANCE(used_fun const, used, value)


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


template< BOOST_PP_ENUM_PARAMS(n, class A) >
void operator()( BOOST_PP_ENUM(n, PSTADE_USED_arg, ~) ) const
{
    BOOST_PP_REPEAT(n, PSTADE_USED_body, ~)
}


#undef n
#endif
