#ifndef PSTADE_EGG_UNFUSE_HPP
#define PSTADE_EGG_UNFUSE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/placeholders.hpp>
#include "./deduce.hpp"
#include "./detail/baby_unfuse_result.hpp"
#include "./function.hpp"
#include "./generator.hpp"
#include "./object.hpp"
#include "./use_brace_level1.hpp"


namespace pstade { namespace egg {


    template<
        class Base,
        class Pack          = boost::use_default,
        class NullaryResult = boost::use_default
    >
    struct result_of_unfuse
    {
        typedef
            function< detail::baby_unfuse_result<Base, Pack, NullaryResult> >
        type; // = { { Base, Pack } };
    };


    #define PSTADE_EGG_UNFUSE_RESULT_INITIALIZER(B, P) \
        { { B(), P() } } \
    /**/


    template<class NullaryResult = boost::use_default>
    struct tp_unfuse :
        generator<
            typename result_of_unfuse<
                deduce<boost::mpl::_1, as_value>,
                deduce<boost::mpl::_2, as_value, boost::use_default>,
                NullaryResult
            >::type,
            use_brace_level1
        >
    { };


    template<class NullaryResult = boost::use_default>
    struct xp_unfuse :
        tp_unfuse<NullaryResult>::type
    { };


    typedef tp_unfuse<>::type op_unfuse;
    PSTADE_EGG_OBJECT((op_unfuse), unfuse) = PSTADE_EGG_GENERATOR_INITIALIZER();


} } // namespace pstade::egg


#endif
