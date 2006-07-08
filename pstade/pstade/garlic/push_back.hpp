#ifndef PSTADE_GARLIC_PUSH_BACK_HPP
#define PSTADE_GARLIC_PUSH_BACK_HPP


// PStade.Garlic
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/enable_if.hpp>
#include <pstade/apple/basic_ostream_fwd.hpp>
#include <pstade/apple/is_sequence.hpp>
#include <pstade/has_xxx.hpp>
#include <pstade/overload.hpp>
#include "./access.hpp"


namespace pstade { namespace garlic {


namespace push_back_detail {


    PSTADE_HAS_TYPE(pstade_garlic_back_insertable)


    // member function
    //
    template< class T, class ValueT > inline
    typename boost::enable_if< has_pstade_garlic_back_insertable<T>,
    void>::type aux(T& x, const ValueT& val)
    {
        return access::detail_push_back(x, val);
    }


    // ADL
    //
    template< class T, class ValueT > inline
    void pstade_garlic_push_back(T& x, const ValueT& val)
    {
        return pstade_garlic_push_back(x, val, overload<>());
    }

    template< class T, class ValueT > inline
    typename boost::disable_if< has_pstade_garlic_back_insertable<T>,
    void>::type aux(T& x, const ValueT& val)
    {
        return pstade_garlic_push_back(x, val);
    }


} // namespace push_back_detail


template< class BackInsertable, class ValueT > inline
void push_back(BackInsertable& bi, const ValueT& val)
{
    return push_back_detail::aux(bi, val);
}


} } // namespace pstade::garlic


// predefined customizations
//

template< class Sequence, class ValueT > inline
typename boost::enable_if< pstade::apple::is_sequence<Sequence>,
void>::type pstade_garlic_push_back(Sequence& seq, const ValueT& val, pstade::overload<>)
{
    seq.push_back(val);
}

template< class T, class Alloc, class ValueT > inline
void pstade_garlic_push_back(std::vector<T, Alloc>& seq, const ValueT& val, pstade::overload<>)
{
    seq.push_back(val);
}


template< class CharT, class Traits, class ValueT > inline
void pstade_garlic_push_back(std::basic_ostream<CharT, Traits>& os, const ValueT& val, pstade::overload<>)
{
    os << val;
}


#endif
