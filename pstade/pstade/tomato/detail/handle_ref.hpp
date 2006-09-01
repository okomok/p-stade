#ifndef PSTADE_TOMATO_DETAIL_HANDLE_REF_HPP
#define PSTADE_TOMATO_DETAIL_HANDLE_REF_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/nonassignable.hpp>


namespace pstade { namespace tomato { namespace detail {


template< class Handle, class Assertion >
struct handle_ref :
    private nonassignable
{
    /*implicit*/ handle_ref(Handle handle) :
        m_handle(handle)
    {
        BOOST_ASSERT(invariant());
    }

    operator Handle() const
    {
        BOOST_ASSERT(invariant());
        return m_handle;
    }

    Handle get() const
    {
        BOOST_ASSERT(invariant());
        return m_handle;
    }

private:
    Handle m_handle;

    bool invariant() const
    {
        return Assertion()(m_handle);
    }
};


} } } // namespace pstade::tomato::detail


#endif
