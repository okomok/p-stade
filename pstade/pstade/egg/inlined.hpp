#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_INLINED_HPP
#define PSTADE_EGG_INLINED_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] http://d.hatena.ne.jp/Cryolite/01000831
// [2] http://ubiety.uwaterloo.ca/~tveldhui/papers/techniques/techniques01.html#index00030


// Note:
//
// Function reference doesn't work with gcc-4.1.
// PSTADE_EGG_INLINE can't support dependent names.


#include <boost/mpl/if.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <pstade/boost_workaround.hpp>
#include <pstade/dont_care.hpp>
#include <pstade/plain.hpp>
#include <pstade/pod_constant.hpp>
#include "./by_value.hpp"
#include "./config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "./generator.hpp"


#if BOOST_WORKAROUND(BOOST_MSVC, < 1500)

    // Fortunately, typeof is native when BOOST_MSVC < 1500.
    #include <boost/typeof/typeof.hpp>

    #if defined(BOOST_TYPEOF_EMULATION)
        #include <boost/mpl/identity.hpp>
        #include <boost/type_traits/is_pointer.hpp>
        #include <pstade/enable_if.hpp>
        #include <pstade/result_of.hpp>
        #include "./free.hpp"
        #define PSTADE_EGG_INLINE_GIVEUP
    #else
        #define PSTADE_EGG_INLINE_TYPEOF
    #endif

#else

    #define PSTADE_EGG_INLINE_COMPLIANT

#endif


namespace pstade { namespace egg {


    template<class Ptr, Ptr ptr>
    struct inlined;

    #define PSTADE_EGG_INLINED() {}


    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/inlined.hpp>))
    #include BOOST_PP_ITERATE()


    namespace inline_detail {


        template<class Ptr>
        struct result_
        {
            template<Ptr ptr>
            typename inlined<Ptr, ptr>::type of() const
            {
                typename inlined<Ptr, ptr>::type r = PSTADE_EGG_INLINED();
                return r;
            }

            explicit result_(dont_care = 0)
            { }
        };


        template<class Ptr>
        Ptr decay(Ptr);


#if defined(PSTADE_EGG_INLINE_GIVEUP)

        // function pointers
        template<class Ptr> inline
        typename lazy_enable_if< boost::is_pointer<Ptr>, boost::mpl::identity<Ptr> >::type
        adapt(Ptr ptr)
        {
            return ptr;
        }

        // member function pointers
        template<class Ptr> inline
        typename lazy_disable_if<boost::is_pointer<Ptr>, result_of<T_free(Ptr&)> >::type
        adapt(Ptr ptr)
        {
            return free(ptr);
        }

#endif


    } // namespace inline_detail


    typedef
        generator<
            inline_detail::result_< deduce<mpl_1, as_value> >,
            by_value
        >::type
    T_inline;

    typedef T_inline T_inline_;
    PSTADE_POD_CONSTANT((T_inline_), inline_) = PSTADE_EGG_GENERATOR();


#if defined(PSTADE_EGG_INLINE_COMPLIANT)
    #define PSTADE_EGG_INLINE(Ptr) pstade::egg::inline_(Ptr).of< Ptr >()
#elif defined(PSTADE_EGG_INLINE_TYPEOF)
    #define PSTADE_EGG_INLINE(Ptr) pstade::egg::inlined<BOOST_TYPEOF(pstade::egg::inline_detail::decay(Ptr)), Ptr>::type()
#elif defined(PSTADE_EGG_INLINE_GIVEUP)
    #define PSTADE_EGG_INLINE(Ptr) pstade::egg::inline_detail::adapt(Ptr)
#endif


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()

#if n == 0
    #define args void
#else
    #define args BOOST_PP_ENUM_PARAMS(n, A)
#endif


    // function pointers
    //

    template<class R BOOST_PP_ENUM_TRAILING_PARAMS(n, class A), R (*ptr)(args)>
    struct inlined<R (*)(args), ptr>
    {
        typedef inlined type;

        typedef R result_type;

        result_type operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, a)) const
        {
            return ptr(BOOST_PP_ENUM_PARAMS(n, a));
        }

#if n == 1
        typedef typename plain<A0>::type argument_type;
#elif n == 2
        typedef typename plain<A0>::type first_argument_type;
        typedef typename plain<A1>::type second_argument_type;
#endif
    };


#if 0


    // member function pointers
    //

#if n != PSTADE_EGG_MAX_LINEAR_ARITY
    #define  cv_qualifier
    #include <pstade/egg/detail/inlined_mem_fun_include.hpp>

    #define  cv_qualifier const
    #include <pstade/egg/detail/inlined_mem_fun_include.hpp>

    #define  cv_qualifier volatile
    #include <pstade/egg/detail/inlined_mem_fun_include.hpp>

    #define  cv_qualifier const volatile
    #include <pstade/egg/detail/inlined_mem_fun_include.hpp>
#endif

#endif


#undef  args

#undef  n
#endif
