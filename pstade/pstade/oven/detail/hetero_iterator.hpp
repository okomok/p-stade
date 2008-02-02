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
#include <pstade/egg/fusion/get.hpp>
#include <pstade/egg/fusion/length.hpp>


#if !defined(PSTADE_OVEN_HETERO_MAX_SIZE)
    #define PSTADE_OVEN_HETERO_MAX_SIZE 20
#endif


namespace pstade { namespace oven { namespace detail {


// hetero_iterator_dereference
//

template< class Tuple, class Reference, int Size = egg::fusion_length<Tuple>::value >
struct hetero_iterator_dereference;

#define PSTADE_return_at(Z, N, _) case N: return egg::fusion_get_c<N>(tup);
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_OVEN_HETERO_MAX_SIZE, <pstade/oven/detail/hetero_iterator.hpp>))
    #include BOOST_PP_ITERATE()
#undef  PSTADE_return_at


// hetero_iterator
//

typedef int hetero_iterator_base;

template< class Tuple, class Reference, class Value >
struct hetero_iterator;

template< class Tuple, class Reference, class Value >
struct hetero_iterator_super
{
    typedef
        boost::iterator_adaptor<
            // Pass everything; hetero_iterator_base isn't an iterator.
            hetero_iterator<Tuple, Reference, Value>,
            hetero_iterator_base,
            Value,
            boost::random_access_traversal_tag,
            Reference,
            std::ptrdiff_t
        >
    type;
};

template< class Tuple, class Reference, class Value >
struct hetero_iterator :
    hetero_iterator_super<Tuple, Reference, Value>::type
{
private:
    typedef typename hetero_iterator_super<Tuple, Reference, Value>::type super_t;

public:
    typedef Tuple sequence_type;

    hetero_iterator()
    { }

    hetero_iterator(Tuple& tup, hetero_iterator_base i) :
        super_t(i), m_ptup(boost::addressof(tup))
    { }

private:
    Tuple *m_ptup;

friend class boost::iterator_core_access;
    Reference dereference() const
    {
        BOOST_ASSERT(m_ptup);
        return hetero_iterator_dereference<Tuple, Reference>::call(*m_ptup, this->base());
    }
};


} } } // namespace pstade::oven::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template< class Tuple, class Reference >
    struct hetero_iterator_dereference<Tuple, Reference, n>
    {
        static Reference call(Tuple& tup, int index)
        {
            switch (index) {
                BOOST_PP_REPEAT(n, PSTADE_return_at, ~)
            default:
                BOOST_ASSERT("out of range" && false);
                throw "impossible"; // suppress warning.
            }
        }
    };


#undef n
#endif
