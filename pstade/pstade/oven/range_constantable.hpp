#ifndef PSTADE_OVEN_RANGE_CONSTANTABLE_HPP
#define PSTADE_OVEN_RANGE_CONSTANTABLE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Resurrects the constant-ness of 'const_iterator'
// in the range whose 'const_iterator' is mutable.


#include <boost/mpl/empty_base.hpp>


namespace pstade { namespace oven {


template<
    class T,
    class ConstIterator,
    class Base = boost::mpl::empty_base
>
struct range_constantable :
    Base
{
    // In fact, you must usually define this in 'T'
    // in order to avoid ambiguity.
    // typedef ConstIterator const_iterator;

    // Eat const-qualified range
    // before member functions are looked up.
    friend
    ConstIterator boost_range_begin(T const& x)
    {
        return x.begin();
    }

    friend
    ConstIterator boost_range_end(T const& x)
    {
        return x.end();
    }
};


} } // namespace pstade::oven


#endif
