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
#include "./aggregate1.hpp"
#include "./deduce.hpp"
#include "./detail/baby_unfuse_result.hpp"
#include "./function.hpp"
#include "./generator.hpp"
#include "./object.hpp"


namespace pstade { namespace egg {


    template<
        class Base,
        class Pack          = boost::use_default,
        class NullaryResult = boost::use_default
    >
    struct unfuse_result
    {
        typedef
            function<
                detail::baby_unfuse_result<Base, Pack, NullaryResult>
            >
        type;
    };


    #define PSTADE_EGG_UNFUSE_RESULT_INITIALIZER(B, P) \
        { { B, P } } \
    /**/


    template<class NullaryResult = boost::use_default>
    struct xp_unfuse :
        generator<
            typename unfuse_result<
                deduce<boost::mpl::_1, as_value>,
                deduce<boost::mpl::_2, as_value, boost::use_default>,
                NullaryResult
            >::type,
            aggregate1
        >
    { };


    typedef xp_unfuse<>::type op_unfuse;
    PSTADE_EGG_OBJECT((op_unfuse), unfuse) = PSTADE_EGG_GENERATOR_INITIALIZER();


} } // namespace pstade::egg


#endif
