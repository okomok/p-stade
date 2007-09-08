#ifndef PSTADE_EGG_DEFER_SIG_HPP
#define PSTADE_EGG_DEFER_SIG_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Converts a poor functor type holding 'sig'
// into the function which supports 'boost::result_of'.
//
// For "big" arity, this use 'by_ref', hence can't take non-const-rvalue.
//
// As we can't detect the arity without 'lambda::bind',
// a nullary-callable function must be identified by 'defer_nullary_sig'.


#include <boost/mpl/bool.hpp>
#include <pstade/pod_constant.hpp>
#include "./detail/baby_defer_sig_result.hpp"
#include "./by_ref.hpp"
#include "./generator.hpp"
#include "./use_brace_level1.hpp"


namespace pstade { namespace egg {


    template<class SigFun>
    struct result_of_defer_sig
    {
        typedef
            function<detail::baby_defer_sig_result<SigFun, boost::mpl::false_>, by_ref>
        type;
    };

    #define PSTADE_EGG_DEFER_SIG_L { {
    #define PSTADE_EGG_DEFER_SIG_R } }

    typedef
        generator<
            result_of_defer_sig< deduce<boost::mpl::_1, as_value> >::type,
            boost::use_default,
            use_brace_level1
        >::type
    op_defer_sig;

    PSTADE_POD_CONSTANT((op_defer_sig), defer_sig) = PSTADE_EGG_GENERATOR;


    template<class SigFun>
    struct result_of_defer_nullary_sig
    {
        typedef
            function<detail::baby_defer_sig_result<SigFun, boost::mpl::true_>, by_ref>
        type;
    };

    typedef
        generator<
            result_of_defer_nullary_sig< deduce<boost::mpl::_1, as_value> >::type,
            boost::use_default,
            use_brace_level1
        >::type
    op_defer_nullary_sig;

    PSTADE_POD_CONSTANT((op_defer_nullary_sig), defer_nullary_sig) = PSTADE_EGG_GENERATOR;


} } // namespace pstade::egg


#endif
