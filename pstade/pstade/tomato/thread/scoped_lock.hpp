#ifndef PSTADE_TOMATO_THREAD_SCOPED_LOCK_HPP
#define PSTADE_TOMATO_THREAD_SCOPED_LOCK_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// LockerT:
//
// WTL::CStaticDataInitCriticalSectionLock
// WTL::CWindowCreateCriticalSectionLock


#include <boost/microsoft/sdk/windows.hpp>
#include <boost/noncopyable.hpp>
#include <pstade/require.hpp>


namespace pstade { namespace tomato {


template< class LockerT >
struct scoped_lock :
	private boost::noncopyable
{
	scoped_lock()
	{
		HRESULT hr = m_locker.Lock();
		PSTADE_REQUIRE(SUCCEEDED(hr));
	}

	~scoped_lock()
	{
		m_locker.Unlock();
	}

private:
	LockerT m_locker;
};


} } // namespace pstade::tomato


#endif
