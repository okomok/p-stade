#ifndef PSTADE_OVEN_ADJACENT_ITERATOR_HPP
#define PSTADE_OVEN_ADJACENT_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Should it be different name, 'adjacent_filtered' and 'adjacent_transformd'?
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2005/n1871.html
//
// Conforming to bidirectional iterator seems to need 'm_first'.
// Am I right?
//
// boost::filter_iterator takes predicate by explicit template argument.
// Such style is rejected for now.


#include <boost/assert.hpp>
#include <boost/iterator/zip_iterator.hpp> // detail::minimum_traversal_category_in_iterator_tuple
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_traits.hpp> // iterator_reference/value
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/core.hpp> // _1, _2
#include <boost/range/iterator_range.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/utility/result_of.hpp>
#include "./detail/an_iterator.hpp"
#include "./detail/equal_to.hpp"


namespace pstade { namespace oven {


template< class ForwardIter, class Functor, class BinaryPred >
struct adjacent_transform_iterator;


namespace adjacent_transform_iterator_detail {


    template< class ForwardIter >
    struct traversal
    {
        typedef boost::tuple<
            ForwardIter,
            detail::an_iterator<boost::bidirectional_traversal_tag>
        > iters_t;

        typedef typename boost::detail::
            minimum_traversal_category_in_iterator_tuple<iters_t>::type
        type;
    };


    template< class ForwardIter, class Functor, class BinaryPred >
    struct super_
    {
		typedef boost::transform_iterator<Functor, ForwardIter> helper_it;

        typedef boost::iterator_adaptor<
            adjacent_transform_iterator<ForwardIter, Functor, BinaryPred>,
            ForwardIter,
			typename boost::iterator_value<helper_it>::type,
            typename traversal<ForwardIter>::type,
			typename boost::iterator_reference<helper_it>::type
        > type;
    };


    template< class ForwardIter, class BinaryPred >
    ForwardIter next(ForwardIter first, ForwardIter last, BinaryPred pred)
    {
        // See: std::adjacent_find

        if (first == last)
            return last;

        ForwardIter next = first;
        while (++next != last) {
            if (!pred(*first, *next))
                return next;
            first = next;
        }

        return last;
    }


} // namespace adjacent_transform_iterator_detail


template<
	class ForwardIter,
	class Functor,
	class BinaryPred = detail::equal_to
>
struct adjacent_transform_iterator :
    adjacent_transform_iterator_detail::super_<ForwardIter, Functor, BinaryPred>::type
{
private:
    typedef adjacent_transform_iterator self_t;
    typedef typename adjacent_transform_iterator_detail::super_<ForwardIter, Functor, BinaryPred>::type super_t;
    typedef typename super_t::base_type base_t;
    typedef typename super_t::reference ref_t;

public:
    explicit adjacent_transform_iterator()
    { }

    explicit adjacent_transform_iterator(
        ForwardIter it,
        ForwardIter first, ForwardIter last,
        Functor fun,
        BinaryPred pred = detail::equal_to()
    ) :
        super_t(it), m_next(it),
        m_first(first), m_last(last),
        m_fun(fun), m_pred(pred)
    {
        find_next();
	}

    template< class ForwardIter_ >
    adjacent_transform_iterator(
        adjacent_transform_iterator<ForwardIter_, Functor, BinaryPred> other,
        typename boost::enable_if_convertible<ForwardIter_, ForwardIter>::type * = 0
    ) :
        super_t(other.base()), m_next(other.next()),
        m_first(other.begin()), m_last(other.end()),
        m_fun(other.functor()), m_pred(other.predicate())
    {
        find_next();
	}

    base_t next() const
    {
        return m_next;
    }

    base_t begin() const
    {
        return m_first;
    }

    base_t end() const
    {
        return m_last;
    }

    Functor functor() const
    {
        return m_fun;
    }

    BinaryPred predicate() const
    {
        return m_pred;
    }

private:
    base_t m_next;
    base_t m_first, m_last;
    Functor m_fun;
    BinaryPred m_pred;

	void find_next()
	{
        m_next = adjacent_transform_iterator_detail::next(
            m_next, m_last, m_pred
        );
	}

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT(this->base() != m_last && "out of range access");
        BOOST_ASSERT(this->base() != m_next);

		boost::iterator_range<base_t> rng(this->base(), m_next);
        return m_fun(rng);
    }

    void increment()
    {
        BOOST_ASSERT(this->base() != m_last && "out of range");

        this->base_reference() = m_next;
		find_next();
    }

    void decrement()
    {
        BOOST_ASSERT(this->base() != m_first && "out of range");

		namespace bll = boost::lambda;

        m_next = this->base();

        boost::reverse_iterator<base_t> rit(this->base());
        boost::reverse_iterator<base_t> rlast(m_first);

        // if you pass 'rit' instead of 'rlast', overflow(1-step) comes.
        this->base_reference() = adjacent_transform_iterator_detail::next(
			rit, rlast, bll::bind<bool>(m_pred, bll::_2, bll::_1)
        ).base();
    }

    bool equal(adjacent_transform_iterator other) const
    {
        BOOST_ASSERT(
        	m_first == other.m_first &&
        	m_last == other.m_last &&
        	"incompatible iterators"
        );

        return this->base() == other.base() && m_next == other.m_next;
    }
};


template< class ForwardIter, class Functor, class BinaryPred > inline const
adjacent_transform_iterator<ForwardIter, Functor, BinaryPred>
make_adjacent_transform_iterator(ForwardIter it, ForwardIter first, ForwardIter last, Functor fun, BinaryPred pred)
{
    return adjacent_transform_iterator<ForwardIter, Functor, BinaryPred>(it, first, last, fun, pred);
}


template< class ForwardIter, class Functor > inline const
adjacent_transform_iterator<ForwardIter, Functor>
make_adjacent_transform_iterator(ForwardIter it, ForwardIter first, ForwardIter last, Functor fun)
{
    return adjacent_transform_iterator<ForwardIter, Functor>(it, first, last, fun);
}


} } // namespace pstade::oven


#endif
