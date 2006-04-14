#ifndef PSTADE_OVEN_ARRAY_RANGE_HPP
#define PSTADE_OVEN_ARRAY_RANGE_HPP


// PStade.Oven
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <boost/noncopyable.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/scoped_array.hpp>
#include <boost/utility/base_from_member.hpp>


namespace pstade { namespace oven {


template< class T >
struct array_range :
	private boost::base_from_member< boost::scoped_array<T> >,
	boost::iterator_range<T *>,
	private boost::noncopyable
{
private:
	typedef boost::base_from_member< boost::scoped_array<T> > initializer_t;
	typedef boost::iterator_range<T *> super_t;

public:
	explicit array_range(std::size_t sz) :
		initializer_t(new T[sz]),
		super_t(initializer_t::member.get(), initializer_t::member.get() + sz)
	{ }
};


} } // namespace pstade::oven


#endif
