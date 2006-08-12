#ifndef PSTADE_RADISH_BOOLEAN_HPP
#define PSTADE_RADISH_BOOLEAN_HPP


// PStade.Radish
//
// Copyright MB 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: 'unspecified_bool_type'
//
// at <boost/shared_ptr.hpp>


#include <boost/mpl/empty_base.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/derived_cast.hpp>
#include <pstade/nullptr.hpp>
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
private:
    typedef void (*pstade_radish_safe_bool_t)(boolean ***);
    static void pstade_radish_safe_bool(boolean ***) { }

public:
    operator pstade_radish_safe_bool_t() const
    {
        T const& d = pstade::derived(*this);
        return access::detail_bool(d) ?
            &boolean::pstade_radish_safe_bool : PSTADE_NULLPTR;
    }
};


} // ADL barrier

} } // namespace pstade::radish


#endif
