#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_NEW_HPP
#define PSTADE_NEW_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://d.hatena.ne.jp/Cryolite/20060622
// http://www.boost.org/libs/smart_ptr/shared_ptr.htm#BestPractices
// http://thread.gmane.org/gmane.comp.lib.boost.devel/140159/
// http://archives.free.net.ph/message/20060328.234524.bf2bc428.en.html
// http://www.gotw.ca/gotw/056.htm


// See: <boost/detail/callable.hpp>
//
// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <memory> // auto_ptr
#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/or.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/enable_if.hpp> // disable_if


#if !defined(PSTADE_NEW_MAX_ARITY)
    #define PSTADE_NEW_MAX_ARITY 5
#endif


// Workaround:
// GCC cannot order overloads which needs explicit template parameter
// if the function argument is const-qualified. 
// Not that VC++7.1's 'is_const' to array was fixed with Boost v1.34,
// but it looks still broken under weird situation around 'disable_if'.
//
#if defined(__GNUC__)
    #define PSTADE_NEW_NO_PARTIAL_ORDERING_WITH_EXPLICIT_TEMPLATE_PARAMETER
#endif


namespace pstade {


    // 0ary
    //
    template< class T > inline
    std::auto_ptr<T>
    new_()
    {
        return std::auto_ptr<T>( new T() );
    } 


    // 1ary
    //
    template< class T, class A0 > inline
#if !defined(PSTADE_NEW_NO_PARTIAL_ORDERING_WITH_EXPLICIT_TEMPLATE_PARAMETER)
    std::auto_ptr<T>
#else
    typename boost::disable_if<
        boost::mpl::or_< boost::is_const<A0> >, // avoid ambiguity
        std::auto_ptr<T>
    >::type
#endif
    new_(A0& a0)
    {
        return std::auto_ptr<T>( new T(a0) );
    } 

    template< class T, class A0 > inline
#if !defined(PSTADE_NEW_NO_PARTIAL_ORDERING_WITH_EXPLICIT_TEMPLATE_PARAMETER)
    std::auto_ptr<T>
#else
    typename boost::disable_if<
        boost::mpl::or_< boost::is_const<A0> >, // always "false", don't care.
        std::auto_ptr<T>
    >::type
#endif
    new_(A0 const& a0)
    {
        return std::auto_ptr<T>( new T(a0) );
    }


    // 2ary -
    //
#define PSTADE_NEW_new(R, BitSeq) \
    template< class T, BOOST_PP_ENUM_PARAMS(n, class A) > inline \
    PSTADE_NEW_result() \
    new_( BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_NEW_param, ~, BitSeq) ) \
    { \
        return std::auto_ptr<T>( new T( BOOST_PP_ENUM_PARAMS(n, a) ) ); \
    } \
/**/

#if !defined(PSTADE_NEW_NO_PARTIAL_ORDERING_WITH_EXPLICIT_TEMPLATE_PARAMETER)
    #define PSTADE_NEW_result() \
        std::auto_ptr<T> \
    /**/
#else
    #define PSTADE_NEW_result() \
        typename boost::disable_if< \
            boost::mpl::or_< BOOST_PP_ENUM(n, PSTADE_NEW_or_arg, ~) >, \
            std::auto_ptr<T> \
        >::type \
    /**/
#endif

#define PSTADE_NEW_or_arg(Z, Index, _) \
    boost::is_const< BOOST_PP_CAT(A, Index) > \
/**/

#define PSTADE_NEW_param(R, _, Index, Bit) \
    BOOST_PP_COMMA_IF(Index) BOOST_PP_CAT(A, Index) BOOST_PP_CAT(PSTADE_NEW_c, Bit) & BOOST_PP_CAT(a, Index) \
/**/

#define PSTADE_NEW_c0
#define PSTADE_NEW_c1 const

#define PSTADE_NEW_bits(Z, N, _) ((0)(1))


#define BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_NEW_MAX_ARITY, <pstade/new.hpp>))
#include BOOST_PP_ITERATE()


#undef PSTADE_NEW_bits
#undef PSTADE_NEW_c1
#undef PSTADE_NEW_c0
#undef PSTADE_NEW_param
#undef PSTADE_NEW_or_arg
#undef PSTADE_NEW_result
#undef PSTADE_NEW_new


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


BOOST_PP_SEQ_FOR_EACH_PRODUCT(
    PSTADE_NEW_new,
    BOOST_PP_REPEAT(n, PSTADE_NEW_bits, ~)
)


#undef n
#endif
