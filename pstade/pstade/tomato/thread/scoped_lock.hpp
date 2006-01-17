#pragma once

#include <boost/noncopyable.hpp>
#include <pstade/workaround/warning_no_copy_constructor.hpp>
#include "../diagnostic/verify.hpp"

namespace pstade { namespace tomato {


// LockerT model:
//   WTL::CStaticDataInitCriticalSectionLock
//   WTL::CWindowCreateCriticalSectionLock

template< class LockerT >
struct scoped_lock :
	private boost::noncopyable
{
	scoped_lock()
	{
		HRESULT hr = m_locker.Lock();
		verify(SUCCEEDED(hr));
	}
	
	~scoped_lock()
	{
		m_locker.Unlock();
	}

	PSTADE_WORKAROUND_WARNING_NO_COPY_CONSTRUCTOR(scoped_lock)

private:
	LockerT m_locker;
};


} } // namespace pstade::tomato
