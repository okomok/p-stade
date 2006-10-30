#ifndef PSTADE_OVEN_GENERATE_ITERATOR_HPP
#define PSTADE_OVEN_GENERATE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/indirect_reference.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/optional.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/remove_cvr.hpp>


namespace pstade { namespace oven {


template< class Generator, class Traversal >
struct generate_iterator;


namespace generate_iterator_detail {


    template< class Generator >
    struct generator_result :
        boost::result_of<typename remove_cvr<Generator>::type()>
    { };


    // "Optional" seems to be a new concept?
    //

    template< class T >
    struct indirect_reference :
        boost::indirect_reference<T>
    { };

    template< class T >
    struct indirect_reference< boost::optional<T> > :
        boost::add_reference<T>
    { };


    // 'Generator' can be a reference.
    //

    template< class Generator >
    struct aux_gen
    {
        explicit aux_gen(Generator const& gen) :
            m_gen(gen)
        { }

        template< class Result >
        Result call()
        {
            return m_gen();
        }

    private:
        Generator m_gen;
    };

    template< class Generator >
    struct aux_gen< Generator& >
    {
        explicit aux_gen(Generator& gen) :
            m_pgen(boost::addressof(gen))
        { }

        template< class Result >
        Result call()
        {
            return (*m_pgen)();
        }

    private:
        Generator *m_pgen; // be a pointer for Assignable.
    };


    // A pointer copy/assignment can't tell Generator anything.
    // So it must be SinglePass.
    template< class Generator, class Traversal >
    struct traversal :
        boost::mpl::if_< boost::is_reference<Generator>,
            boost::single_pass_traversal_tag,
            Traversal
        >
    { };


    template< class Generator, class Traversal >
    struct super_
    {
        BOOST_MPL_ASSERT(( boost::mpl::or_<
            boost::is_same<Traversal, boost::single_pass_traversal_tag>,
            boost::is_same<Traversal, boost::forward_traversal_tag>
        > ));

        typedef typename generator_result<Generator>::type result_t;
        typedef typename indirect_reference<result_t>::type ref_t;
        typedef typename remove_cvr<ref_t>::type val_t;

        typedef boost::iterator_facade<
            generate_iterator<Generator, Traversal>,
            val_t,
            typename traversal<Generator, Traversal>::type,
            ref_t
        > type;
    };


} // namespace generate_iterator_detail


template<
    class Generator,
    class Traversal = boost::single_pass_traversal_tag
>
struct generate_iterator :
    generate_iterator_detail::super_<Generator, Traversal>::type
{
private:
    typedef generate_iterator self_t;
    typedef typename generate_iterator_detail::super_<Generator, Traversal>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef generate_iterator_detail::aux_gen<Generator> aux_gen_t;
    typedef typename generate_iterator_detail::generator_result<Generator>::type result_t;

public:
    // If default-constructed one plays the end iterator role,
    // it would require non-reference 'Generator' to be
    // DefaultConstructible. But SinglePassIterator is not
    // required to be. So, prefer the constructor with 'not_end'.
    generate_iterator()
    { }

    generate_iterator(Generator gen, bool not_end) :
        m_gen(gen), m_result()
    {
        if (not_end)
            generate();
    }

    bool is_end() const
    {
        return !m_result;
    }

private:
    aux_gen_t m_gen;
    mutable result_t m_result;

    void generate()
    {
        m_result = m_gen.template call<result_t>();
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


template< class Generator > inline
generate_iterator<Generator> const
make_generate_iterator(Generator gen, bool not_end)
{
    return generate_iterator<Generator>(gen, not_end);
}


} } // namespace pstade::oven


#endif
