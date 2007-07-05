#ifndef PSTADE_EGG_PERFECT_HPP
#define PSTADE_EGG_PERFECT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Works around the forwarding problem.
// You can choose:
//     perfect(lambda::_1)(1); or
//     lambda::_1(1|to_ref);
//
// Also, this can add 'boost::result_of/lambda::sig' support
// by passing the extra argument, as 'lambda::ret' does.
// Thus, you can change/specify the result type of the function.
//     perfect<int>(f)(x);


#include <boost/mpl/placeholders.hpp>
#include <pstade/result_of.hpp>
#include "./deduce.hpp"
#include "./detail/baby_perfect_result.hpp"
#include "./function.hpp"
#include "./generator.hpp"
#include "./use_brace_level1.hpp"


namespace pstade { namespace egg {


    template<class Base, class ResultType = boost::use_default>
    struct result_of_perfect
    {
        typedef
            function< detail::baby_perfect_result<Base, ResultType> >
        type;
    };


    #define PSTADE_EGG_PERFECT_RESULT_INITIALIZER(B) \
        { { B() } } \
    /**/


    template<class ResultType = boost::use_default>
    struct tp_perfect :
        generator<
            typename result_of_perfect<deduce<boost::mpl::_1, as_value>, ResultType>::type,
            use_brace_level1
        >
    { };


    template<class ResultType = boost::use_default>
    struct xp_perfect :
        tp_perfect<ResultType>::type
    { };


    template<class Base> inline
    typename result_of<xp_perfect<>(Base&)>::type
    perfect(Base base)
    {
        return xp_perfect<>()(base);
    }

    template<class ResultType, class Base> inline
    typename result_of<xp_perfect<ResultType>(Base&)>::type
    perfect(Base base)
    {
        return xp_perfect<ResultType>()(base);
    }


} } // namespace pstade::egg


#endif
