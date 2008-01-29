#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_FREE_HPP
#define PSTADE_EGG_FREE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] boost::bind
// [2] boost::mem_fn


#include <boost/implicit_cast.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/or.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/affect.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/pod_constant.hpp>
#include "./bll_bindable.hpp"
#include "./by_value.hpp"
#include "./config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "./construct_braced1.hpp"
#include "./detail/free_call.hpp"
#include "./detail/unref.hpp"
#include "./generator.hpp"


namespace pstade { namespace egg {


    namespace free_detail {


        template<class Base>
        struct result_;


        // data member pointer
        template<class R, class T>
        struct result_<R (T::*)>
        {
            typedef R (T::*base_type);

            base_type m_base;

            base_type const& base() const
            {
                return m_base;
            }

            template<class U>
            struct apply_ :
                boost::mpl::eval_if< is_convertible<U, T const *>,
                    affect<typename boost::remove_pointer<typename boost::remove_cv<U>::type>::type&, R>,
                    boost::mpl::eval_if< is_convertible<U, T const &>,
                        affect<U&, R>,
                        boost::mpl::identity<R const&> // unknown
                    >
                >
            { };

        // convertibles
            typename apply_<T *>::type operator()(T *p) const
            {
                return (p->*m_base);
            }

            typename apply_<T const *>::type operator()(T const *p) const
            {
                return (p->*m_base);
            }

            typename apply_<T>::type operator()(T &t) const
            {
                return (t.*m_base);
            }

            typename apply_<T const>::type operator()(T const &t) const
            {
                return (t.*m_base);
            }

        // unknown
            template<class U>
            typename apply_<U const>::type operator()(U const& u,
                typename disable_if< is_convertible<U const&, T const&> >::type = 0) const
            {
                PSTADE_EGG_GET_POINTER_PREAMBLE()
                return (get_pointer(u)->*m_base);
            }

        // result_of support
            template<class Signature>
            struct result;
            
            template<class Self, class U>
            struct result<Self(U)> :
                apply_<typename detail::unref<by_perfect, U>::type>
            { };

            #include PSTADE_EGG_BLL_BINDABLE()
        };


        // member function pointers
    #define PSTADE_max_arity BOOST_PP_DEC(PSTADE_EGG_MAX_LINEAR_ARITY)
    #define PSTADE_forward(Z, N, _) boost::implicit_cast<BOOST_PP_CAT(A, N)>(BOOST_PP_CAT(a, N))
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_max_arity, <pstade/egg/free.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_forward
    #undef  PSTADE_max_arity


    } // namespace free_detail


    template<class Base>
    struct result_of_free
    {
        typedef free_detail::result_<Base> type;
    };

    #define PSTADE_EGG_FREE_L {
    #define PSTADE_EGG_FREE_R }
    #define PSTADE_EGG_FREE(F) PSTADE_EGG_FREE_L F PSTADE_EGG_FREE_R


    typedef
        generator<
            result_of_free< deduce<mpl_1, as_value> >::type,
            by_value,
            X_construct_braced1<>
        >::type
    T_free;

    PSTADE_POD_CONSTANT((T_free), free) = PSTADE_EGG_GENERATOR();

    typedef T_free T_free_;
    PSTADE_POD_CONSTANT((T_free_), free_) = PSTADE_EGG_GENERATOR();


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()

#if n == 0
    #define args void
#else
    #define args BOOST_PP_ENUM_PARAMS(n, A)
#endif


    #define  cv_qualifier
    #include <pstade/egg/detail/free_mem_fun_include.hpp>

    #define  cv_qualifier const
    #include <pstade/egg/detail/free_mem_fun_include.hpp>

    #define  cv_qualifier volatile
    #include <pstade/egg/detail/free_mem_fun_include.hpp>

    #define  cv_qualifier const volatile
    #include <pstade/egg/detail/free_mem_fun_include.hpp>


#undef  args

#undef  n
#endif
