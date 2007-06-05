#ifndef PSTADE_OVEN_LIGHTWEIGHT_COPYABLE_HPP
#define PSTADE_OVEN_LIGHTWEIGHT_COPYABLE_HPP
#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/foreach.hpp> // foreach::tag
#include <boost/mpl/bool.hpp>
#include <pstade/radish/null_injector.hpp>


namespace pstade { namespace oven {


template<
    class Range,
    class Injector = radish::null_injector<Range>
>
struct lightweight_copyable :
    Injector
{
    friend
    boost::mpl::true_ *
    boost_foreach_is_lightweight_proxy(Range *&, boost::foreach::tag)
    {
        return 0;
    }
};


} } // namespace pstade::oven


#endif
