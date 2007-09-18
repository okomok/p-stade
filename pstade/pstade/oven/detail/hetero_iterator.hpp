#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OVEN_DETAIL_HETERO_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_HETERO_ITERATOR_HPP
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
#include <pstade/use_default.hpp>


#if !defined(PSTADE_OVEN_HETERO_MAX_SIZE)
    #define PSTADE_OVEN_HETERO_MAX_SIZE 20
#endif


namespace pstade { namespace oven { namespace detail {


template< class Reference, class Tuple, int sz = egg::tuple_size<Tuple>::value >
struct hetero_iterator_dereference;

#define PSTADE_return_at(Z, N, _) case N: return egg::tuple_get_c<N>(tup);
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_OVEN_HETERO_MAX_SIZE, <pstade/oven/detail/hetero_iterator.hpp>))
    #include BOOST_PP_ITERATE()
#undef  PSTADE_return_at


typedef int hetero_iterator_base;

template< class Reference, class Value, class Tuple >
struct hetero_iterator;

template< class Reference, class Value, class Tuple >
struct hetero_iterator_super
{
    typedef
        boost::iterator_adaptor<
            // Pass everything; hetero_iterator_base isn't an iterator.
            hetero_iterator<Reference, Value, Tuple>,
            hetero_iterator_base,
            Value,
            boost::random_access_traversal_tag,
            Reference,
            std::ptrdiff_t
        >
    type;
};

template< class Reference, class Value, class Tuple >
struct hetero_iterator :
    hetero_iterator_super<Reference, Value, Tuple>::type
{
private:
    typedef typename hetero_iterator_super<Reference, Value, Tuple>::type super_t;

public:
    typedef Tuple sequence_type;

    hetero_iterator()
    { }

    hetero_iterator(Tuple& tup, hetero_iterator_base it) :
        super_t(it), m_ptup(boost::addressof(tup))
    { }

    hetero_iterator_base& detail_base_reference()
    {
        return this->base_reference();
    }

private:
    Tuple *m_ptup;

friend class boost::iterator_core_access;
    Reference dereference() const
    {
        BOOST_ASSERT(m_ptup);
        return hetero_iterator_dereference<Reference, Tuple>::call(*m_ptup, this->base());
    }
};


} } } // namespace pstade::oven::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template< class Reference, class Tuple >
    struct hetero_iterator_dereference<Reference, Tuple, n>
    {
        static Reference call(Tuple& tup, int index)
        {
            switch (index) {
                BOOST_PP_REPEAT(n, PSTADE_return_at, ~)
            default:
                BOOST_ASSERT(false);
                throw "impossible"; // suppress warning.
            }
        }
    };


#undef n
#endif
