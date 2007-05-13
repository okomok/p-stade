#ifndef PSTADE_TOMATO_DIET_BUFFER_HPP
#define PSTADE_TOMATO_DIET_BUFFER_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/value_type.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/diet/access.hpp>
#include <pstade/integral_cast.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/oven/distance.hpp>


namespace pstade { namespace tomato {


namespace buffer_detail {


    template< class PointerRange > inline
    UINT_PTR bytes(PointerRange const& buf)
    {
        typedef typename boost::range_value<PointerRange>::type val_t;
        return pstade::integral( sizeof(val_t) * oven::distance(buf) );
    }


} // namespace buffer_detail


struct buffer
{
    typedef buffer pstade_diet_diagnostic;

    template< class PointerRange >
    explicit buffer(PointerRange const& rng, bool w = true) :
        m_ptr(boost::begin(rng)), m_bytes(buffer_detail::bytes(rng)),
        m_writable(w)
    { }

    explicit buffer(VOID const *ptr, UINT_PTR bytes, bool w = true) :
        m_ptr(ptr), m_bytes(bytes),
        m_writable(w)
    { }

private:
    VOID const *m_ptr;
    UINT_PTR m_bytes;
    bool m_writable;

friend class diet::access;
    bool pstade_diet_is_valid() const
    {
    #if !defined(_WIN32_WCE)

        return // See: ATL7::AtlIsValidAddress
            (m_ptr != PSTADE_NULLPTR) &&
            !::IsBadReadPtr(m_ptr, m_bytes) &&
            (!m_writable || !::IsBadWritePtr(const_cast<LPVOID>(m_ptr), m_bytes));

    #else

        return
            (m_ptr != PSTADE_NULLPTR);

    #endif
    }

    template< class OStream >
    void pstade_diet_dump(OStream& os) const
    {
        os <<
            "<buffer> "     <<
                "<address>" << reinterpret_cast<unsigned int>(m_ptr) << "</address>" <<
                "<bytes>"   << m_bytes << "</bytes>" <<
            "</buffer>";
    }
};


} } // namespace pstade::tomato


#endif
