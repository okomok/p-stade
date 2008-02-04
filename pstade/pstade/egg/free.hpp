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
#include <pstade/affect.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/pod_constant.hpp>
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "./detail/free_call.hpp"
#include "./detail/get_pointer_preamble.hpp"
#include "./detail/pp_enum_fun_param_types.hpp"
#include "./detail/wrap.hpp"
#include "./use_deduced_form.hpp"


namespace pstade { namespace egg {


    template<class Base>
    struct result_of_free;

    #define PSTADE_EGG_FREE_L { {
    #define PSTADE_EGG_FREE_R } }
    #define PSTADE_EGG_FREE(F) PSTADE_EGG_FREE_L F PSTADE_EGG_FREE_R


    // member object pointers
    //

    template<class R, class T>
    struct result_of_free<R (T::*)>
    {
        typedef function<result_of_free, by_perfect> type;

        typedef R (T::*base_t);

        base_t m_base;

        base_t const& base() const
        {
            return m_base;
        }

        typedef result_of_free use_deduced_form;

        template<class Me, class U>
        struct apply :
            boost::mpl::eval_if< is_convertible<U, T const *>,
                affect<typename boost::remove_pointer<typename boost::remove_cv<U>::type>::type &, R>,
                boost::mpl::eval_if< is_convertible<U, T const&>,
                    affect<U&, R>,
                    boost::mpl::identity<R const&> // unknown
                >
            >
        { };

    // convertibles
        template<class Re>
        Re call(boost::type<Re>, T *p) const
        {
            return (p->*m_base);
        }

        template<class Re>
        Re call(boost::type<Re>, T const *p) const
        {
            return (p->*m_base);
        }

        template<class Re>
        Re call(boost::type<Re>, T &t) const
        {
            return (t.*m_base);
        }

        template<class Re>
        Re call(boost::type<Re>, T const &t) const
        {
            return (t.*m_base);
        }

    // unknown
        template<class Re, class U>
        Re call(boost::type<Re>, U const& u,
            typename disable_if< is_convertible<U const&, T const&> >::type = 0) const
        {
            PSTADE_EGG_GET_POINTER_PREAMBLE()
            return (get_pointer(u)->*m_base);
        }
    };


#define PSTADE_max_arity BOOST_PP_DEC(PSTADE_EGG_MAX_LINEAR_ARITY)
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_max_arity, <pstade/egg/free.hpp>))
    #include BOOST_PP_ITERATE()
#undef  PSTADE_max_arity


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
                Re r = PSTADE_EGG_FREE(base);
                return r;
            }
        };


    } // namespace free_detail


    typedef function<free_detail::little, by_value> T_free;
    PSTADE_POD_CONSTANT((T_free), free) = {{}};

    typedef T_free T_free_;
    PSTADE_POD_CONSTANT((T_free_), free_) = {{}};


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()

#define fparams PSTADE_EGG_PP_ENUM_FUN_PARAM_TYPES(n, A)


    // member function pointers
    //

    #define  cv_qualifier
    #include <pstade/egg/detail/free_mem_fun_include.hpp>

    #define  cv_qualifier const
    #include <pstade/egg/detail/free_mem_fun_include.hpp>

    #define  cv_qualifier volatile
    #include <pstade/egg/detail/free_mem_fun_include.hpp>

    #define  cv_qualifier const volatile
    #include <pstade/egg/detail/free_mem_fun_include.hpp>


#undef  fparams

#undef  n
#endif
