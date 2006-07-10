#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_FUNCTION_HPP
#define PSTADE_EGG_FUNCTION_HPP


// PStade.Egg
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/comma_protect.hpp>
#include <pstade/instance.hpp>
#include "./baby_result_type.hpp"
#include "./detail/config.hpp"
#include "./detail/operators.hpp"
#include "./detail/results.hpp"
#include "./function_fwd.hpp"


namespace pstade { namespace egg {


    template< class BabyFunction >
    struct function :
        detail::operators<BabyFunction>,
        detail::results<BabyFunction>
    {
    private:
        typedef detail::operators<BabyFunction> super_t;

    public:
        explicit function(BabyFunction fun) :
            super_t(fun)
        { }
    };


} } // namespace pstade::egg


namespace boost {


    // 0ary
    //
    template< class BabyFunction >
    struct result_of<pstade::egg::function<BabyFunction>(void)> : // CWPro8 requires an argument 'void'
        pstade::egg::baby_result0<BabyFunction>
    { };


#if defined(PSTADE_EGG_DETAIL_NO_NESTED_RESULT_SPECIALIZATION)


    // 1ary
    //
    template< class BabyFunction, class A0 >
    struct result_of<pstade::egg::function<BabyFunction>(A0)> :
        pstade::egg::baby_result1<BabyFunction, A0>
    { };


    // 2ary
    //
    template< class BabyFunction, class A0, class A1 >
    struct result_of<pstade::egg::function<BabyFunction>(A0, A1)> :
        pstade::egg::baby_result2<BabyFunction, A0, A1>
    { };


    // 3ary -
    //
    #define BOOST_PP_ITERATION_PARAMS_1 (3, (3, PSTADE_EGG_MAX_ARITY, <pstade/egg/function.hpp>))
    #include BOOST_PP_ITERATE()


#endif


} // namespace boost


// See:
// Effective STL Item.6
//
#define PSTADE_EGG_FUNCTION(Name, Baby) \
    typedef pstade::egg::function< \
        pstade::comma_protect<void(Baby)>::type \
    > BOOST_PP_CAT(Name, _fun); \
    \
    PSTADE_INSTANCE( \
        pstade::egg::function< pstade::comma_protect<void(Baby)>::type > const, \
        Name, ((pstade::comma_protect<void(Baby)>::type())) \
    ) \
/**/


#endif
#else
#define n BOOST_PP_ITERATION()


template< class BabyFunction, BOOST_PP_ENUM_PARAMS(n, class A) >
struct result_of<pstade::egg::function<BabyFunction>( BOOST_PP_ENUM_PARAMS(n, A) )> :
    pstade::egg::BOOST_PP_CAT(baby_result, n)< BabyFunction, BOOST_PP_ENUM_PARAMS(n, A) >
{ };


#undef n
#endif
