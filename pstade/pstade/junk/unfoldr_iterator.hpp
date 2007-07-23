#ifndef PSTADE_OVEN_DETAIL_UNFOLDR_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_UNFOLDR_ITERATOR_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// unfoldr :: (b->Maybe (a,b)) -> b -> [a]
// unfoldr fun b  = case fun b of Nothing    -> []
//                                Just (a,b) -> a : unfoldr fun b


#include <boost/assert.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/if.hpp>
#include <pstade/egg/dereference.hpp>
#include <pstade/egg/to_ref.hpp>
#include <pstade/egg/tuple_get.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/result_of.hpp>
#include "./has_is_pure.hpp"


namespace pstade { namespace oven { namespace detail {


template< class B, class UnaryFun >
struct unfoldr_iterator;


template< class B, class UnaryFun >
struct unfoldr_iterator_super
{
    typedef typename
        result_of<UnaryFun(B const&)>::type
    result_t;

    typedef typename
        result_of<
            egg::xp_tuple_get_c<0>(
                typename result_of<egg::op_dereference(result_t const&)>::type
            )
        >::type
    ref_t;

    typedef typename
        remove_cvr<ref_t>::type
    val_t;

    typedef
        boost::iterator_facade<
            unfoldr_iterator<B, UnaryFun>,
            val_t,
            typename boost::mpl::if_< has_is_pure<UnaryFun>,
                boost::forward_traversal_tag,
                boost::single_pass_traversal_tag
            >::type,
            ref_t
        >
    type;
};


template< class B, class UnaryFun >
struct unfoldr_iterator :
    unfoldr_iterator_super<B, UnaryFun>::type
{
private:
    typedef unfoldr_iterator self_t;
    typedef typename unfoldr_iterator_super<B, UnaryFun>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename result_of<UnaryFun(B const&)>::type result_t;

public:
    unfoldr_iterator()
    { }

    unfoldr_iterator(B const& b, UnaryFun fun) :
        m_fun(fun), m_result(fun(b))
    { }

    explicit unfoldr_iterator(UnaryFun fun) : // the end iterator
        m_fun(fun), m_result()
    { }

private:
    UnaryFun m_fun;
    result_t m_result;

    bool is_end() const
    {
        return !m_result;
    }

    bool equal_aux(self_t const& other, boost::forward_traversal_tag) const
    {
        if (is_end() ^ other.is_end())
            return false;
        else if (is_end() && other.is_end())
            return true;
        else {
            BOOST_ASSERT(!is_end() && !other.is_end());
            return egg::tuple_get_c<0>(*m_result) == egg::tuple_get_c<0>(*other.m_result);
        }
    }

    bool equal_aux(self_t const& other, boost::single_pass_traversal_tag) const
    {
        return is_end() == other.is_end();
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT(!is_end());
        return egg::tuple_get_c<0>(*m_result);
    }

    void increment()
    {
        BOOST_ASSERT(!is_end());
        m_result = m_fun(egg::to_cref(egg::tuple_get_c<1>(*m_result)));
    }

    bool equal(self_t const& other) const
    {
        return equal_aux(other,
            typename boost::iterator_category_to_traversal<typename super_t::iterator_category>::type() );
    }
};


} } } // namespace pstade::oven::detail


#endif
