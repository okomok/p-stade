#ifndef PSTADE_OVEN_TEST_NCINT_HPP
#define PSTADE_OVEN_TEST_NCINT_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../detail/prelude.hpp"
#include <boost/operators.hpp> // totally_ordered


namespace pstade { namespace oven { namespace test {


struct ncint :
    private boost::totally_ordered<ncint>
{
    explicit ncint(int i) :
        m_int(i)
    { }

    int value() const
    {
        return m_int;
    }

// totally_ordered
    bool operator< (ncint const& other) const
    {
        return m_int < other.m_int;
    }

    bool operator==(ncint const& other) const
    {
        return m_int == other.m_int;
    }

    int& detail_value()
    {
        return m_int;
    }

private:
    int m_int;

    ncint(ncint const&);
    ncint& operator=(ncint const&);
};

inline
ncint* new_clone(ncint const& nci)
{
    return new ncint(nci.value());
}


} } } // namespace pstade::oven::test


#endif
