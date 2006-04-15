#ifndef PSTADE_NAPKIN_LOCK_OSTREAM_HPP
#define PSTADE_NAPKIN_LOCK_OSTREAM_HPP


// PStade.Napkin
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/noncopyable.hpp>
#include <boost/thread/mutex.hpp>
#include "./ostream.hpp"


namespace pstade { namespace napkin {


template< class CharT >
struct basic_lock_ostream :
	private boost::noncopyable
{
	basic_lock_ostream()
	{ }

	template< class StringOutputable >
	explicit basic_lock_ostream(StringOutputable& out) :
		m_os(out)
	{ }

	template< class OutputStreamable >
	basic_lock_ostream& operator<<(const OutputStreamable& x)
	{
		{
			boost::mutex::scoped_lock lock(m_mtx);
			m_os << x;
		}

		return *this;
	}

	template< class StringOutputable >
	void reset(StringOutputable& out)
	{
		m_os.reset(out);
	}

private:
	basic_ostream<CharT> m_os;
	boost::mutex m_mtx;
};


typedef basic_lock_ostream<char>
lock_ostream;


typedef basic_lock_ostream<wchar_t>
lock_wostream;


} } // namespace pstade::napkin


#endif
