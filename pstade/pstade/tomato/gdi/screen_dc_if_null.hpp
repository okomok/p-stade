#pragma once

#include <boost/noncopyable.hpp>
#include "../diagnostic/is_valid.hpp"

namespace pstade { namespace tomato {


struct screen_dc_if_null :
	private boost::noncopyable
{
// ctor/dtor
	explicit screen_dc_if_null(HDC hDC) : m_hDC(hDC), m_managed(false)
	{
		if (m_hDC == NULL) {
			m_hDC = ::GetDC(NULL);
			api_verify(m_hDC != NULL);
			m_managed = true;
		}

		ATLASSERT(is_valid(m_hDC));
	}

	~screen_dc_if_null()
	{
		ATLASSERT(tomato::is_valid(m_hDC));

		if (m_managed)
			::DeleteDC(m_hDC);
	}

// selector
	HDC get_handle() const { return m_hDC; }

private:
	HDC m_hDC;
	bool m_managed;
};


} } // namespace pstade::tomato
