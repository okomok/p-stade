#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OVEN_DETAIL_FUSIONAL_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_FUSIONAL_ITERATOR_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // ptrdiff_t
#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/egg/tuple/get.hpp>
#include <pstade/egg/tuple/size.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>


#if !defined(PSTADE_OVEN_FUSION_MAX_SIZE)
    #define PSTADE_OVEN_FUSION_MAX_SIZE 20
#endif


namespace pstade { namespace oven {


template< class Tuple, int sz = egg::tuple_size<Tuple>::value >
struct fusional_element;

// 0ary-
#define PSTADE_get(Z, N, _) \
    typename result_of<egg::xp_tuple_get_c<N>(Tuple&)>::type BOOST_PP_CAT(get, N)() const \
    { \
        BOOST_ASSERT(N == m_index); \
        return egg::xp_tuple_get_c<N>()(*m_ptuple); \
    } \
/**/
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_OVEN_FUSION_MAX_SIZE, <pstade/oven/detail/fusional_iterator.hpp>))
    #include BOOST_PP_ITERATE()
#undef  PSTADE_get


#define PSTADE_OVEN_FUSIONAL_DEREF(Elem)


namespace detail {


    typedef int fusional_iterator_base;


    template< class Tuple >
    struct fusional_iterator;


    template< class Tuple >
    struct fusional_iterator_super
    {
        typedef
            boost::iterator_adaptor<
                // Pass everything; fusional_iterator_base isn't an iterator.
                fusional_iterator<Reference, Value, Tuple>,
                fusional_iterator_base,
                fusional_element<Tuple>,
                boost::random_access_traversal_tag,
                fusional_element<Tuple> const&,
                std::ptrdiff_t
            >
        type;
    };


    template< class Tuple >
    struct fusional_iterator<Tuple> :
        fusional_iterator_super<Tuple>::type
    {
    private:
        typedef typename fusional_iterator_super<Tuple>::type super_t;
        typedef typename super_t::reference ref_t;

    public:
        typedef Tuple sequence_type;
        // BOOST_PP_REPEAT(n, PSTADE_element_typedef, ~)

        fusional_iterator()
        { }

        fusional_iterator(Tuple& tup, fusional_iterator_base it) :
            super_t(it), m_ptup(tup)
        { }

    private:
        mutable fusional_element<Tuple> m_elem;

    friend class boost::iterator_core_access;
        ref_t dereference() const
        {
            m_elem.detail_set_index(this->base());
            return m_elem;
        }
    };


} // namespace detail


} } // namespace pstade::oven


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Tuple>
    struct fusional_element<Tuple, n>
    {
        typedef Tuple sequence_type;

        explicit fusional_element()
        { }

        explicit fusional_element(Tuple& tup) :
            m_ptup(boost::addressof(tup))
        { }

        void detail_set_index(int index)
        {
            m_index = index;
        }

        int detail_get_index() const
        {
            return m_index;
        }

        template< int N >
        typename result_of<egg::xp_tuple_get_c<N>(Tuple&)>::type
        get() const
        {
            return egg::xp_tuple_get_c<N>()(*m_ptuple);
        }

        //BOOST_PP_REPEAT(n, PSTADE_get, ~)

    private:
        Tuple *m_ptup;
        int m_index;
    };


#undef n
#endif
