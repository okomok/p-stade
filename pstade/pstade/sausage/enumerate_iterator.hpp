#ifndef PSTADE_SAUSAGE_ENUMRATE_ITERATOR_HPP
#define PSTADE_SAUSAGE_ENUMRATE_ITERATOR_HPP


// PStade.Sausage
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://d.hatena.ne.jp/y-hamigaki/20060409#1144593955


#include <boost/iterator/iterator_facade.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include "./detail/enumerate_iterator_impl.hpp"
#include "./enumerate_argument_type.hpp"


namespace pstade { namespace sausage {


template< class Enumerable >
struct enumerate_iterator;


namespace enumerate_iterator_detail {


	template< class Enumerable >
	struct super_
	{
		typedef typename enumerate_argument<Enumerable>::type arg_t;
		typedef typename boost::remove_reference<arg_t>::type val_t;

		typedef boost::iterator_facade<
			enumerate_iterator<Enumerable>,
			val_t,
			boost::single_pass_traversal_tag,
			arg_t
		> type;
	};


} // namespace enumerate_iterator_detail


template< class Enumerable >
struct enumerate_iterator :
	enumerate_iterator_detail::super_<Enumerable>::type
{
private:
	typedef typename enumerate_iterator_detail::super_<Enumerable>::type super_t;
	typedef typename super_t::reference ref_t;
	typedef detail::enumerate_iterator_impl<Enumerable> impl_t;

public:
	enumerate_iterator() // end iter
	{ }

	explicit enumerate_iterator(Enumerable& enm) :
		m_pimpl(new impl_t(enm))
	{
		if (m_pimpl->done())
			m_pimpl.reset();
	}

private:
	boost::shared_ptr<impl_t> m_pimpl;

friend class boost::iterator_core_access;
	ref_t dereference() const
	{
		return m_pimpl->deref();
	}

	void increment()
	{
		m_pimpl->next();
		if (m_pimpl->done())
			m_pimpl.reset();
	}

	bool equal(const enumerate_iterator& other) const
	{
		return m_pimpl == other.m_pimpl;
	}
};


template< class Enumerable > inline const
enumerate_iterator<Enumerable>
make_enumerate_first_iterator(Enumerable& enm)
{
	return enumerate_iterator<Enumerable>(enm);
}


	template< class Enumerable > inline const
	enumerate_iterator<
		// Writing 'const Enumerable' breaks VC++ if Enumerable is array.
		typename boost::add_const<Enumerable>::type 
	>
	make_enumerate_first_iterator(const Enumerable& enm)
	{
		return enumerate_iterator<
			typename boost::add_const<Enumerable>::type
		>(enm);
	}


template< class Enumerable > inline const
enumerate_iterator<Enumerable> make_enumerate_last_iterator(Enumerable& )
{
	return enumerate_iterator<Enumerable>();
}


	template< class Enumerable > inline const
	enumerate_iterator<
		typename boost::add_const<Enumerable>::type
	>
	make_enumerate_last_iterator(const Enumerable& )
	{
		return enumerate_iterator<
			typename boost::add_const<Enumerable>::type
		>();
	}


} } // namespace pstade::sausage


#endif
