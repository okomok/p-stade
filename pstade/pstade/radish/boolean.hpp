#ifndef PSTADE_RADISH_BOOLEAN_HPP
#define PSTADE_RADISH_BOOLEAN_HPP


// PStade.Radish
//
// Copyright MB 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/empty_base.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/derived_cast.hpp>
#include "./access.hpp"


namespace pstade { namespace radish {

PSTADE_ADL_BARRIER(boolean) {


template<
    class T,
    class Base = boost::mpl::empty_base
>
struct boolean :
    Base
{
    operator bool() const
    {
        T& d = pstade::derived(*this);
        return access::detail_bool(d);
    }

    bool operator !() const
    {
        return !(operator bool());
    }
};


} // ADL barrier

} } // namespace pstade::radish


#endif
