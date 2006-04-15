#ifndef PSTADE_OVEN_RANGE_HOLDER_HPP
#define PSTADE_OVEN_RANGE_HOLDER_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/any.hpp>
#include <boost/noncopyable.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>


namespace pstade { namespace oven {


struct range_placeholder
{
	virtual ~range_placeholder() { }

	boost::any begin() { return begin_impl(); }
	boost::any end() { return end_impl(); }
	boost::any size() { return size_impl(); }
	bool empty() { return empty_impl(); }

	boost::any ptr_begin() { return ptr_begin_impl(); }
	boost::any ptr_end() { return ptr_end_impl(); }

protected:
	virtual boost::any begin_impl() = 0;
	virtual boost::any end_impl() = 0;
	virtual boost::any size_impl() = 0;
	virtual bool empty_impl() = 0;

	virtual boost::any ptr_begin_impl() = 0;
	virtual boost::any ptr_end_impl() = 0;
};


template< class Range >
struct range_holder :
	range_placeholder,
	private boost::noncopyable
{
	explicit range_holder(Range& rng) :
		m_held(rng)
	{ }

	Range& held() { return m_held; }

protected:
	boost::any begin_impl() { return boost::begin(m_held); }
	boost::any end_impl() { return boost::end(m_held); }
	boost::any size_impl() { return boost::size(m_held); }
	bool empty_impl() { return boost::empty(m_held); }

	boost::any ptr_begin_impl() { return &*boost::begin(m_held); }
	boost::any ptr_end_impl() { return &*boost::end(m_held); }

private:
	Range& m_held;
};


} } // namespace pstade::oven


#endif
