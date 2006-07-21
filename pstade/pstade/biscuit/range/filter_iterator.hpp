#ifndef PSTADE_BISCUIT_RANGE_FILTER_ITERATOR_HPP
#define PSTADE_BISCUIT_RANGE_FILTER_ITERATOR_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: <boost/iterator/filter_iterator.hpp>


#include <boost/config.hpp> // BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE
#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/utility/addressof.hpp>
#include "../algorithm/search.hpp"


namespace pstade { namespace biscuit {


template< class Parser, class ForwardIter, class UserState >
struct filter_iterator;


namespace filter_iterator_detail {


    template< class Parser, class ForwardIter, class UserState >
    struct super_
    {
        typedef boost::iterator_adaptor<
            filter_iterator<Parser, ForwardIter, UserState>,
            ForwardIter,
            boost::use_default,
            boost::forward_traversal_tag
        > type;
    };


} // namespace filter_iterator_detail


template< class Parser, class ForwardIter, class UserState >
struct filter_iterator :
    filter_iterator_detail::super_<Parser, ForwardIter, UserState>::type
{
private:
    typedef typename filter_iterator_detail::super_<Parser, ForwardIter, UserState>::type super_t;

public:
    filter_iterator()
    { }

    filter_iterator(ForwardIter const& x, ForwardIter const& last, UserState& us) :
        super_t(x), m_submatch_last(x), m_last(last),
        m_pus(boost::addressof(us))
    {
        search_submatch(); // trigger!
    }

    template< class ForwardIter_ >
    filter_iterator(
        filter_iterator<Parser, ForwardIter_, UserState> const& other,
        typename boost::enable_if_convertible<ForwardIter_, ForwardIter>::type * = 0
    ) :
        super_t(other.base()), m_submatch_last(other.submatch_end()), m_last(other.end()),
        m_pus( boost::addressof(other.user_state()) )
    { }

    ForwardIter submatch_end() const { return m_submatch_last; }
    ForwardIter end() const { return m_last; }
    UserState& user_state() const { return *m_pus; }

private:
    ForwardIter m_submatch_last;
    ForwardIter m_last;
    UserState *m_pus;

    void search_submatch()
    {
        if (this->base() != m_submatch_last) {
            // still on the submatch
            return;
        }

        // get a next submatch
        boost::iterator_range<ForwardIter> tr(this->base(), m_last);
        boost::iterator_range<ForwardIter> sr = biscuit::search<Parser>(tr, *m_pus);

        if (boost::begin(sr) == m_last) {
            // not found
            this->base_reference() = m_last;
            return;
        }

        this->base_reference() = boost::begin(sr);
        m_submatch_last = boost::end(sr);
    }

friend class boost::iterator_core_access;
    void increment()
    {
        BOOST_ASSERT(this->base() != m_last && "out of range");

        ++(this->base_reference());
        search_submatch();
    }
};


template< class Parser, class ForwardIter, class UserState > inline
filter_iterator<Parser, ForwardIter, UserState>
make_filter_iterator(ForwardIter const& x, ForwardIter const& last, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
    return filter_iterator<Parser, ForwardIter, UserState>(x, last, us);
}


} } // namespace pstade::biscuit


#endif
