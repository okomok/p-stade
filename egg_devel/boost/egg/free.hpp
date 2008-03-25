#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_FREE_HPP
#define BOOST_EGG_FREE_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] boost::bind
// [2] boost::mem_fn


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_LINEAR_ARITY
#include <boost/egg/const.hpp>
#include <boost/egg/detail/affect.hpp>
#include <boost/egg/detail/enable_if.hpp>
#include <boost/egg/detail/free_call.hpp>
#include <boost/egg/detail/get_pointer_preamble.hpp>
#include <boost/egg/detail/in_fun_spec.hpp>
#include <boost/egg/detail/is_convertible.hpp>
#include <boost/egg/detail/wrap.hpp>
#include <boost/egg/overloaded.hpp>


namespace boost { namespace egg {


    template<class Base>
    struct result_of_free;

    #define BOOST_EGG_FREE_L { {
    #define BOOST_EGG_FREE_R } }
    #define BOOST_EGG_FREE(F) BOOST_EGG_FREE_L F BOOST_EGG_FREE_R


    // member object pointers
    //

    template<class R, class T>
    struct result_of_free<R (T::*)>
    {
        typedef function<result_of_free, by_perfect> type;

        typedef R (T::*base_t);

        base_t m_base;

        base_t const &base() const
        {
            return m_base;
        }

        BOOST_EGG_OVERLOADED_PREAMBLE()

        template<class Me, class U>
        struct apply :
            mpl::eval_if< is_convertible_<U, T const *>,
                details::affect<typename remove_pointer<typename remove_cv<U>::type>::type &, R>,
                mpl::eval_if< is_convertible_<U, T const &>,
                    details::affect<U &, R>,
                    mpl::identity<R const &> // unknown
                >
            >
        { };

    // convertibles
        template<class Re>
        Re call(BOOST_EGG_OVERLOADED(Re) T *p) const
        {
            return (p->*m_base);
        }

        template<class Re>
        Re call(BOOST_EGG_OVERLOADED(Re) T const *p) const
        {
            return (p->*m_base);
        }

        template<class Re>
        Re call(BOOST_EGG_OVERLOADED(Re) T &t) const
        {
            return (t.*m_base);
        }

        template<class Re>
        Re call(BOOST_EGG_OVERLOADED(Re) T const &t) const
        {
            return (t.*m_base);
        }

    // unknown
        template<class Re, class U>
        Re call(BOOST_EGG_OVERLOADED(Re) U const &u,
            typename disable_if_< is_convertible_<U const &, T const &> >::type = 0) const
        {
            BOOST_EGG_GET_POINTER_PREAMBLE()
            return (get_pointer(u)->*m_base);
        }
    };


#define BOOST_EGG_max_arity BOOST_PP_DEC(BOOST_EGG_MAX_LINEAR_ARITY)
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_EGG_max_arity, <boost/egg/free.hpp>))
    #include BOOST_PP_ITERATE()
#undef  BOOST_EGG_max_arity


    namespace free_detail {


        // `generator` isn't usable around template specializations.
        struct little
        {
            template<class Me, class Base>
            struct apply :
                result_of_free<Base>
            { };

            template<class Re, class Base>
            Re call(Base base) const
            {
                Re r = BOOST_EGG_FREE(base);
                return r;
            }
        };


    } // namespace free_detail


    typedef function<free_detail::little, by_value> T_free;
    BOOST_EGG_CONST((T_free), free) = {{}};

    typedef T_free T_free_;
    BOOST_EGG_CONST((T_free_), free_) = {{}};


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
#else
#define n BOOST_PP_ITERATION()

#define fparams BOOST_EGG_ENUM_PARAMS_IN_FUN_SPEC(n, A)


    // member function pointers
    //

    #define  cv_qualifier
    #include <boost/egg/detail/free_mem_fun_include.hpp>

    #define  cv_qualifier const
    #include <boost/egg/detail/free_mem_fun_include.hpp>

    #define  cv_qualifier volatile
    #include <boost/egg/detail/free_mem_fun_include.hpp>

    #define  cv_qualifier const volatile
    #include <boost/egg/detail/free_mem_fun_include.hpp>


#undef  fparams

#undef  n
#endif
