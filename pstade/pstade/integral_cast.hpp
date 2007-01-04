#ifndef PSTADE_INTEGRAL_CAST_HPP
#define PSTADE_INTEGRAL_CAST_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/assert.hpp>
#include <boost/numeric/conversion/cast.hpp> // numeric_cast
#include <boost/type_traits/is_integral.hpp>
#include <pstade/automatic.hpp>
#include <pstade/pipable.hpp>


namespace pstade {


    template<class To, class From> inline
    To integral_cast(From const& from)
    {
        BOOST_MPL_ASSERT((boost::is_integral<To>));
        BOOST_MPL_ASSERT((boost::is_integral<From>));
        return boost::numeric_cast<To>(from);
    }


    template<class To>
    struct op_integral_cast
    {
        typedef To result_type;
        
        template<class From>
        To operator()(From const& from) const
        {
            return pstade::integral_cast<To>(from);
        }
    };


    PSTADE_PIPABLE(to_integer, (automatic<op_integral_cast<boost::mpl::_1> >))


} // namespace pstade


#endif
