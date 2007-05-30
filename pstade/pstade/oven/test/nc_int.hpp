#ifndef PSTADE_OVEN_TEST_NC_INT_HPP
#define PSTADE_OVEN_TEST_NC_INT_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../detail/prelude.hpp"
#include <boost/operators.hpp> // totally_ordered


namespace pstade { namespace oven { namespace test {


struct nc_int :
    private boost::totally_ordered<nc_int>
{
    explicit nc_int(int i) :
        m_int(i)
    { }

    int value() const
    {
        return m_int;
    }

// totally_ordered
    bool operator< (nc_int const& other) const
    {
        return m_int < other.m_int;
    }

    bool operator==(nc_int const& other) const
    {
        return m_int == other.m_int;
    }

    int& detail_value()
    {
        return m_int;
    }

private:
    int m_int;

    nc_int(nc_int const&);
    nc_int& operator=(nc_int const&);
};

inline
nc_int* new_clone(nc_int const& nci)
{
    return new nc_int(nci.value());
}


} } } // namespace pstade::oven::test


#endif
