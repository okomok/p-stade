#ifndef PSTADE_GRAVY_SCREEN_DC_IF_NULL_HPP
#define PSTADE_GRAVY_SCREEN_DC_IF_NULL_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/require.hpp>
#include <pstade/verify.hpp>
#include "./detail/is_dc.hpp"
#include "./sdk/windows.hpp"


namespace pstade { namespace gravy {


    struct screen_dc_if_null
    {
        explicit screen_dc_if_null(HDC hDC) :
            m_hDC(hDC), m_managed(false)
        {
            if (m_hDC == NULL) {
                m_hDC = ::GetDC(NULL);
                PSTADE_REQUIRE(m_hDC != NULL);
                m_managed = true;
            }

            BOOST_ASSERT(detail::is_dc(m_hDC));
        }

        ~screen_dc_if_null()
        {
            BOOST_ASSERT(detail::is_dc(m_hDC));

            if (m_managed)
                ::DeleteDC(m_hDC)|verified;
        }

        HDC handle() const
        {
            return m_hDC;
        }

    private:
        HDC m_hDC;
        bool m_managed;

        screen_dc_if_null(screen_dc_if_null const&);
        screen_dc_if_null& operator=(screen_dc_if_null const&);
    };


} } // namespace pstade::gravy


#endif
