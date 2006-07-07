#ifndef PSTADE_IS_SAME_HPP
#define PSTADE_IS_SAME_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/identity.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/egg/function.hpp>


namespace pstade {


namespace is_same_detail {


    struct baby
    {
        template< class T1, class T2 >
        struct result : boost::mpl::identity<
            bool
        >
        { };

        template< class Result, class T >
        Result call(T const& x, T const& y)
        {
            return boost::addressof(x) == boost::addressof(y);
        }
    };


} // namespace is_same_detail


PSTADE_EGG_FUNCTION(is_same, is_same_detail::baby)


} // namespace pstade


#endif
