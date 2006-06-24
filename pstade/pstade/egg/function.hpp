#ifndef PSTADE_EGG_FUNCTION_HPP
#define PSTADE_EGG_FUNCTION_HPP


// PStade.Egg
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/seq/cat.hpp>
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
{ };


} } // namespace pstade::egg


namespace boost {


    template< class BabyFunction >
    struct result_of<pstade::egg::function<BabyFunction>(void)> : // CWPro8 requires an argument 'void'
        pstade::egg::baby_result0<BabyFunction>
    { };


#if defined(PSTADE_EGG_DETAIL_NO_NESTED_RESULT_SPECIALIZATION)


/*
    template< class BabyFunction, class A0, class A1 >
    struct result_of<pstade::egg::function<BabyFunction>(A0, A1)> :
        pstade::egg::baby_result2<BabyFunction, A0, A1>
    { };
*/


    #define PSTADE_EGG_result_of(Z, N, _) \
        template< class BabyFunction, BOOST_PP_ENUM_PARAMS(N, class A) > \
        struct result_of<pstade::egg::function<BabyFunction>( BOOST_PP_ENUM_PARAMS(N, A) )> : \
            pstade::egg::BOOST_PP_CAT(baby_result, N)< BabyFunction, BOOST_PP_ENUM_PARAMS(N, A) > \
        { }; \
    /**/


    BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(PSTADE_EGG_MAX_ARITY), PSTADE_EGG_result_of, ~)


    #undef PSTADE_EGG_result_of


#endif


} // namespace boost


#define PSTADE_EGG_FUNCTION(Name, Baby) \
    typedef pstade::egg::function< \
        pstade::comma_protect<void(Baby)>::type \
    > BOOST_PP_SEQ_CAT((Name)(_)(fun)); \
    \
    PSTADE_INSTANCE( \
        const pstade::egg::function< pstade::comma_protect<void(Baby)>::type >, \
        Name, value \
    ) \
/**/


#endif
