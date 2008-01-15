#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_VC7_1_APPLY_LITTLE_HPP
#define PSTADE_EGG_DETAIL_VC7_1_APPLY_LITTLE_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/boost_workaround.hpp>
#include "../config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "./apply_little_n.hpp"

#include "./vc7_1_array_resurrect.hpp"
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/mpl/assert.hpp>


#if !BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    #error This header is used only with msvc-7.1.
#endif


namespace pstade { namespace egg {


    namespace detail_vc7_1 {


#if 0
        template<class X>
        struct is_broken_array :
            boost::mpl::and_<
                boost::mpl::not_< boost::is_array<X> >,
                boost::is_array<typename detail_vc7_1::array_resurrect<X>::type>
            >
        { };
#else

        template<class X, class Sig = void(X)>
        struct is_broken_array_impl
        {
            BOOST_STATIC_CONSTANT(bool, value = false);
        };

        template<class X, class T>
        struct is_broken_array_impl< X, void(T[]) >
        {
            BOOST_STATIC_CONSTANT(bool, value = true);
        };


        template<class X>
        struct is_broken_array
        {
            BOOST_STATIC_CONSTANT(bool, value = is_broken_array_impl<X>::value);
        };

        template<class T, std::size_t N>
        struct is_broken_array< T[N] >
        {
            BOOST_STATIC_CONSTANT(bool, value = false);
        };
#endif


#define PSTADE_or(Z, N, _) BOOST_PP_IF(N, BOOST_PP_IDENTITY(||), BOOST_PP_EMPTY)() BOOST_PP_CAT(B, N)
        template<PSTADE_PP_ENUM_PARAMS_WITH(PSTADE_EGG_MAX_LINEAR_ARITY, bool B, = false)>
        struct or_ :
            boost::mpl::bool_<BOOST_PP_REPEAT(PSTADE_EGG_MAX_LINEAR_ARITY, PSTADE_or, B)>
        { };
#undef  PSTADE_or


        struct dummy_result
        {
            typedef dummy_result type; // overriden in non-broken context, after all.

            template<class T>
            operator T() const;
        };


    } // namespace detail_vc7_1


    template<class Little, PSTADE_PP_ENUM_PARAMS_WITH(BOOST_PP_INC(PSTADE_EGG_MAX_LINEAR_ARITY), class A, = void)>
    struct apply_little;


    // 1ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/detail/vc7_1_apply_little.hpp>))
    #include BOOST_PP_ITERATE()


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Little, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply_little<Little, BOOST_PP_ENUM_PARAMS(n, A)> :
        boost::mpl::eval_if< detail_vc7_1::or_<PSTADE_PP_ENUM_PARAMS_WITH(n, detail_vc7_1::is_broken_array<A, >::value)>,
            detail_vc7_1::dummy_result,
            BOOST_PP_CAT(apply_little, n)<
                Little,
                BOOST_PP_ENUM_PARAMS(n, A)
            >
        >
    { };


#undef n
#endif
