#ifndef PSTADE_OVEN_GENERATION_HPP
#define PSTADE_OVEN_GENERATION_HPP


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


#include "./detail/prelude.hpp"
#include <boost/assert.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/function.hpp>
#include <pstade/indirect.hpp>
#include <pstade/object_generator.hpp>
#include <boost/optional/optional.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/remove_cvr.hpp>
#include "./detail/begin_end_tag.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace generation_detail {


    template< class StoppableGenerator >
    struct generator_iterator;


    template< class StoppableGenerator >
    struct generator_iterator_super
    {
        typedef typename
            boost::result_of<StoppableGenerator()>::type
        result_t;

        typedef typename
            boost::result_of<op_indirect(result_t const&)>::type
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
        typedef typename boost::result_of<StoppableGenerator()>::type result_t;

    public:

        // If default-constructed one plays the end iterator role,
        // it would require 'StoppableGenerator' to be DefaultConstructible.
        // But SinglePassIterator is not required to be. So use tags.

        generator_iterator(StoppableGenerator gen, detail::begin_tag) :
            m_gen(gen), m_result()
        {
            generate();
        }

        generator_iterator(StoppableGenerator gen, detail::end_tag) :
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


    template< class StoppableGenerator >
    struct baby
    {
        typedef
            generator_iterator<
                typename pass_by_value<StoppableGenerator>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(StoppableGenerator& gen) const
        {
            return result_type(
                iter_t(gen, detail::begin_tag()),
                iter_t(gen, detail::end_tag())
            );
        }
    };


} // namespace generation_detail


PSTADE_FUNCTION(generation, (generation_detail::baby<_>))


namespace nonstop_detail {


    template< class Generator >
    struct return_op
    {
        typedef
            boost::optional<
                typename boost::result_of<Generator()>::type
            >
        result_type;

        result_type operator()()
        {
            return result_type(m_gen());
        }

        explicit return_op()
        { }

        explicit return_op(Generator gen) :
            m_gen(gen)
        { }

    private:
        Generator m_gen;        
    };


} // namespace nonstop_detail


PSTADE_OBJECT_GENERATOR(nonstop,
    (nonstop_detail::return_op< deduce<_1, as_value> >))


} } // namespace pstade::oven


#endif
