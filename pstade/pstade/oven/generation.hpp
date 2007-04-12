#ifndef PSTADE_OVEN_GENERATION_HPP
#define PSTADE_OVEN_GENERATION_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/indirect_reference.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/optional.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/function.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/remove_cvr.hpp>
#include "./begin_end.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace generation_detail {


    template< class Generator >
    struct generator_iterator;


    // "Optional" becomes a new concept?

    template< class X >
    struct indirect_reference :
        boost::indirect_reference<X>
    { };

    template< class T >
    struct indirect_reference< boost::optional<T> > :
        boost::add_reference<T>
    { };


    template< class Generator >
    struct generator_iterator_super
    {
        typedef typename
            boost::result_of<Generator()>::type
        result_t;

        typedef typename
            indirect_reference<result_t>::type
        ref_t;

        typedef typename
            remove_cvr<ref_t>::type
        val_t;

        typedef
            boost::iterator_facade<
                generator_iterator<Generator>,
                val_t,
                boost::single_pass_traversal_tag,
                ref_t
            >
        type;
    };


    template< class Generator >
    struct generator_iterator :
        generator_iterator_super<Generator>::type
    {
    private:
        typedef typename generator_iterator_super<Generator>::type super_t;
        typedef typename super_t::reference ref_t;

    public:

        // If default-constructed one plays the end iterator role,
        // it would require 'Generator' to be DefaultConstructible.
        // But SinglePassIterator is not required to be.
        // So, specify it by using 'op_begin/op_end'.

        generator_iterator(Generator gen, op_begin) :
            m_gen(gen), m_result()
        {
            generate();
        }

        generator_iterator(Generator gen, op_end) :
            m_gen(gen), m_result()
        { }

        bool is_end() const
        {
            return !m_result;
        }

        Generator generator() const
        {
            return m_gen;
        }

    private:
        Generator m_gen;
        // 'mutable' needed; const-ness of 'optional' affects its element.
        mutable typename boost::result_of<Generator()>::type m_result;

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


    template< class Generator >
    struct baby
    {
        typedef
            generator_iterator<
                typename pass_by_value<Generator>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Generator& gen) const
        {
            return result_type(iter_t(gen, begin), iter_t(gen, end));
        }
    };


} // namespace generation_detail


PSTADE_FUNCTION(generation, (generation_detail::baby<_>))


namespace innumerable_detail {


    template< class Generator_ >
    struct return_op
    {
        typedef
            boost::optional<
                typename boost::result_of<Generator_()>::type
            >
        result_type;

        result_type operator()()
        {
            return result_type(m_gen());
        }

        explicit return_op(Generator_ gen) :
            m_gen(gen)
        { }

    private:
        Generator_ m_gen;        
    };


} // namespace innumerable_detail


PSTADE_OBJECT_GENERATOR(innumerable,
    (innumerable_detail::return_op< deduce<_1, to_value> >))


} } // namespace pstade::oven


#endif
