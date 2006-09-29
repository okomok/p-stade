#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_NEW_HPP
#define PSTADE_NEW_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
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
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <pstade/const_overloaded.hpp>


#if !defined(PSTADE_NEW_MAX_ARITY)
    #define PSTADE_NEW_MAX_ARITY 5
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
    std::auto_ptr<T>
    new_(A0& a0, typename const_overloaded<A0>::type = 0)
    {
        return std::auto_ptr<T>( new T(a0) );
    } 

    template< class T, class A0 > inline
    std::auto_ptr<T>
    new_(A0 const& a0, typename const_overloaded<A0>::type = 0/*no effect, don't care.*/)
    {
        return std::auto_ptr<T>( new T(a0) );
    }


    // 2ary -
    //
#define PSTADE_NEW_new(R, BitSeq) \
    template< class T, BOOST_PP_ENUM_PARAMS(n, class A) > inline \
    std::auto_ptr<T> \
    new_( BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_NEW_param, ~, BitSeq), typename const_overloaded< BOOST_PP_ENUM_PARAMS(n, A) >::type = 0 ) \
    { \
        return std::auto_ptr<T>( new T( BOOST_PP_ENUM_PARAMS(n, a) ) ); \
    } \
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
