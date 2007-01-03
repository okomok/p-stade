#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_FUNCTION_HPP
#define PSTADE_FUNCTION_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: <boost/detail/function1.hpp>
//
// Copyright David Abrahams 2006. Distributed under the Boost 
// Software License, Version 1.0. (See accompanying 
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) 


// Note:
//
// This is virtually a short version of 'forward'.


#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/unparenthesize.hpp>


namespace pstade {


    template<class Baby>
    struct function :
        callable< function<Baby> >
    {
        template<class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A)>
        struct apply
        { }; // complete for SFINAE.

        // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/function.hpp>))
        #include BOOST_PP_ITERATE()
    };


    #define PSTADE_FUNCTION(Object, Baby) \
        namespace BOOST_PP_CAT(pstade_function_workarea_of_, Object) { \
            using ::boost::mpl::_1; \
            using ::boost::mpl::_2; \
            using ::boost::mpl::_3; \
            using ::boost::mpl::_4; \
            using ::boost::mpl::_5; \
            \
            typedef ::pstade::function<PSTADE_UNPARENTHESIZE(Baby)> op; \
        } \
        typedef BOOST_PP_CAT(pstade_function_workarea_of_, Object)::op BOOST_PP_CAT(op_, Object); \
        PSTADE_CONSTANT( Object, (BOOST_PP_CAT(op_, Object)) ) \
    /**/


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)>
{
    typedef typename boost::mpl::BOOST_PP_CAT(apply, n)<Baby, BOOST_PP_ENUM_PARAMS(n, A)>::type baby_t;
    typedef typename baby_t::result type;
};

template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
Result call(PSTADE_PP_ENUM_REF_PARAMS(n, A, a)) const
{
    typedef typename boost::mpl::BOOST_PP_CAT(apply, n)<Baby, BOOST_PP_ENUM_PARAMS(n, A)>::type baby_t;
    return baby_t::call(BOOST_PP_ENUM_PARAMS(n, a));
}


#undef n
#endif
