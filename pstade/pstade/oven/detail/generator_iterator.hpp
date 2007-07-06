#ifndef PSTADE_OVEN_DETAIL_GENERATOR_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_GENERATOR_ITERATOR_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] Jens Maurer, generator_iterator, Boost.Utility, 2001.
//     http://www.boost.org/libs/utility/generator_iterator.htm


#include <boost/assert.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <pstade/egg/indirect.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/result_of.hpp>
#include "./begin_end_tag.hpp"


namespace pstade { namespace oven { namespace detail {


template< class StoppableGenerator >
struct generator_iterator;


template< class StoppableGenerator >
struct generator_iterator_super
{
    typedef typename
        result_of<StoppableGenerator()>::type
    result_t;

    typedef typename
        result_of<egg::op_indirect(result_t const&)>::type
    ref_t;

    typedef typename
        remove_cvr<ref_t>::type
    val_t;

    typedef
        boost::iterator_facade<
            generator_iterator<StoppableGenerator>,
            val_t,
            boost::single_pass_traversal_tag,
            ref_t
        >
    type;
};


template< class StoppableGenerator >
struct generator_iterator :
    generator_iterator_super<StoppableGenerator>::type
{
private:
    typedef typename generator_iterator_super<StoppableGenerator>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename result_of<StoppableGenerator()>::type result_t;

public:

    // If default-constructed one plays the end iterator role,
    // it would require 'StoppableGenerator' to be DefaultConstructible.
    // But SinglePassIterator is not required to be. So use tags.

    generator_iterator(StoppableGenerator gen, begin_tag) :
        m_gen(gen), m_result()
    {
        generate();
    }

    generator_iterator(StoppableGenerator gen, end_tag) :
        m_gen(gen), m_result()
    { }

    bool is_end() const
    {
        return !m_result;
    }

    StoppableGenerator generator() const
    {
        return m_gen;
    }

private:
    StoppableGenerator m_gen;
    result_t m_result;

    void generate()
    {
        m_result = m_gen();
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT(!is_end());
        return *m_result;
    }

    bool equal(generator_iterator const& other) const
    {
        return is_end() == other.is_end();
    }

    void increment()
    {
        BOOST_ASSERT(!is_end());
        generate();
    }
};


} } } // namespace pstade::oven::detail


#endif
