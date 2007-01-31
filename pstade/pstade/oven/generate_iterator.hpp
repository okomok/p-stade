#ifndef PSTADE_OVEN_GENERATE_ITERATOR_HPP
#define PSTADE_OVEN_GENERATE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/config.hpp> // BOOST_NESTED_TEMPLATE
#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/optional.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/remove_cvr.hpp>


namespace pstade { namespace oven {


template< class Generator >
struct generate_iterator;


namespace generate_iterator_detail {


    // "Optional" seems to be a new concept?

    template< class T >
    struct indirect_reference;

    template< class T >
    struct indirect_reference< boost::optional<T> > :
        boost::add_reference<T>
    { };


    template< class Generator >
    struct super_
    {
        typedef typename
            boost::result_of<Generator()>::type
        result_t;

        typedef typename
            remove_cvr<
                typename indirect_reference<result_t>::type
            >::type
        val_t;

        typedef
            boost::iterator_facade<
                generate_iterator<Generator>,
                val_t,
                boost::single_pass_traversal_tag,
                val_t const&
            >
        type;
    };


} // namespace generate_iterator_detail


template< class Generator >
struct generate_iterator :
    generate_iterator_detail::super_<Generator>::type
{
private:
    typedef generate_iterator self_t;
    typedef typename generate_iterator_detail::super_<Generator>::type super_t;
    typedef typename super_t::reference ref_t;

public:
    // If default-constructed one plays the end iterator role,
    // it would require 'Generator' to be DefaultConstructible.
    // But SinglePassIterator is not required to be.
    // So, prefer the constructor with 'mpl::true_/false_'.
    generate_iterator()
    { }

    generate_iterator(Generator const& gen, boost::mpl::true_) :
        m_gen(gen), m_result()
    {
        generate();
    }

    generate_iterator(Generator const& gen, boost::mpl::false_) : // end iterator
        m_gen(gen), m_result()
    { }

    bool is_end() const
    {
        return !m_result;
    }

private:
    Generator m_gen;
    typename boost::result_of<Generator()>::type m_result;

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

    bool equal(self_t const& other) const
    {
        return is_end() && other.is_end();
    }

    void increment()
    {
        BOOST_ASSERT(!is_end());
        generate();
    }
};


} } // namespace pstade::oven


#endif
