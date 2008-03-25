#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_INLINED_HPP
#define BOOST_EGG_INLINED_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
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
// BOOST_EGG_INLINE can't support dependent names.


#include <boost/mpl/if.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_LINEAR_ARITY
#include <boost/egg/const.hpp>
#include <boost/egg/detail/boost_workaround.hpp>
#include <boost/egg/detail/dont_care.hpp>
#include <boost/egg/detail/in_fun_spec.hpp>
#include <boost/egg/detail/free_call.hpp>
#include <boost/egg/detail/plain.hpp>
#include <boost/egg/generator.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, < 1500)

    // Fortunately, typeof is native when BOOST_MSVC < 1500.
    #include <boost/typeof/typeof.hpp>

    #if defined(BOOST_TYPEOF_EMULATION)
        #include <boost/mpl/identity.hpp>
        #include <boost/type_traits/is_pointer.hpp>
        #include <boost/egg/detail/enable_if.hpp>
        #include <boost/egg/free.hpp>
        #include <boost/egg/result_of.hpp>
        #define BOOST_EGG_INLINE_GIVEUP
    #else
        #define BOOST_EGG_INLINE_TYPEOF
    #endif

#else

    #define BOOST_EGG_INLINE_COMPLIANT

#endif


namespace boost { namespace egg {


    template<class Ptr, Ptr ptr>
    struct inlined;

    #define BOOST_EGG_INLINED() {}


    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_EGG_MAX_LINEAR_ARITY, <boost/egg/inlined.hpp>))
    #include BOOST_PP_ITERATE()


    namespace inline_detail {


        template<class Ptr>
        struct result_
        {
            template<Ptr ptr>
            typename inlined<Ptr, ptr>::type of() const
            {
                typename inlined<Ptr, ptr>::type r = BOOST_EGG_INLINED();
                return r;
            }

            explicit result_(details::dont_care = 0)
            { }
        };


        template<class T>
        T decay(T);


#if defined(BOOST_EGG_INLINE_GIVEUP)

        // function pointers
        template<class Ptr> inline
        typename lazy_enable_if_< is_pointer<Ptr>, mpl::identity<Ptr> >::type
        adapt(Ptr ptr)
        {
            return ptr;
        }

        // member function pointers
        template<class Ptr> inline
        typename lazy_disable_if_<is_pointer<Ptr>, result_of_<T_free_(Ptr &)> >::type
        adapt(Ptr ptr)
        {
            return free_(ptr);
        }

#endif


    } // namespace inline_detail


    typedef
        generator<
            inline_detail::result_< deduce<mpl::_1, as_value> >,
            by_value
        >::type
    T_inline;

    typedef T_inline T_inline_;
    BOOST_EGG_CONST((T_inline_), inline_) = BOOST_EGG_GENERATOR();


#if defined(BOOST_EGG_INLINE_COMPLIANT)
    #define BOOST_EGG_INLINE(Ptr) boost::egg::inline_(Ptr).of< Ptr >()
#elif defined(BOOST_EGG_INLINE_TYPEOF)
    #define BOOST_EGG_INLINE(Ptr) boost::egg::inlined<BOOST_TYPEOF(boost::egg::inline_detail::decay(Ptr)), Ptr>::type()
#elif defined(BOOST_EGG_INLINE_GIVEUP)
    #define BOOST_EGG_INLINE(Ptr) boost::egg::inline_detail::adapt(Ptr)
#endif


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
#else
#define n BOOST_PP_ITERATION()

#define fparams BOOST_EGG_ENUM_PARAMS_IN_FUN_SPEC(n, A)


    // function pointers
    //

    template<class R BOOST_PP_ENUM_TRAILING_PARAMS(n, class A), R (*ptr)(fparams)>
    struct inlined<R (*)(fparams), ptr>
    {
        typedef inlined type;

        typedef R result_type;

        result_type operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, a)) const
        {
            return ptr(BOOST_PP_ENUM_PARAMS(n, a));
        }

#if n == 1
        typedef typename details::plain<A0>::type argument_type;
#elif n == 2
        typedef typename details::plain<A0>::type first_argument_type;
        typedef typename details::plain<A1>::type second_argument_type;
#endif
    };


    // member function pointers
    //

#if n != BOOST_EGG_MAX_LINEAR_ARITY

    #define  cv_qualifier
    #include <boost/egg/detail/inlined_mem_fun_include.hpp>

    #define  cv_qualifier const
    #include <boost/egg/detail/inlined_mem_fun_include.hpp>

    #define  cv_qualifier volatile
    #include <boost/egg/detail/inlined_mem_fun_include.hpp>

    #define  cv_qualifier const volatile
    #include <boost/egg/detail/inlined_mem_fun_include.hpp>

#endif


#undef  fparams

#undef  n
#endif
