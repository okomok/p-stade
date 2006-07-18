#ifndef PSTADE_IS_SAME_HPP
#define PSTADE_IS_SAME_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/addressof.hpp>
#include <pstade/instance.hpp>


namespace pstade {


struct is_same_fun
{
    typedef bool result_type;

    template< class T >
    bool operator()(T const& x, T const& y) const
    {
        return boost::addressof(x) == boost::addressof(y);
    }
};


PSTADE_INSTANCE(is_same_fun const, is_same, value)


} // namespace pstade


#endif
