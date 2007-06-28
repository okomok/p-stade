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
#include "./baby/generator.hpp"
#include "./baby/unfuse_result.hpp"
#include "./deduce.hpp"
#include "./function.hpp"
#include "./object.hpp"


namespace pstade { namespace egg {


    template<class NullaryResult = boost::use_default>
    struct xp_unfuse
    {
        typedef
            function<
                baby::generator<
                    function<
                        baby::unfuse_result<
                            deduce<boost::mpl::_1, as_value>,
                            deduce<boost::mpl::_2, as_value, boost::use_default>,
                            NullaryResult
                        >
                    >,
                    aggregate1
                >
            >
        type;
    };


    typedef xp_unfuse<>::type op_unfuse;
    PSTADE_EGG_OBJECT((op_unfuse), unfuse) = { {} };


} } // namespace pstade::egg


#endif
