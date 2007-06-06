#ifndef PSTADE_OVEN_TUPLE_HPP
#define PSTADE_OVEN_TUPLE_HPP
#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_traits.hpp>
#include <boost/tuple/tuple.hpp>
#include "./extension.hpp"
#include "./detail/config.hpp"


namespace pstade_oven_extension {


    template< class Iter >
    struct Range< boost::tuples::tuple<Iter, Iter> >
    {
        template< class X >
        struct associate
        {
            typedef Iter mutable_iterator;
            typedef Iter constant_iterator;
        };

        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return boost::tuples::get<0>(x);
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return boost::tuples::get<1>(x);
        }
    };


} // namespace pstade_oven_extension


PSTADE_OVEN_EXTENSION_OF_TEMPLATE((boost)(tuples)(tuple), 2)


// tuples::cons<>, nightmare.
//

namespace boost {


#define PSTADE_t boost::tuples::cons< Iter, boost::tuples::cons<Iter, boost::tuples::null_type> >


    template< class Iter >
    struct PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR< PSTADE_t >
    {
        typedef Iter type;
    };

    template< class Iter >
    struct PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR< PSTADE_t const >
    {
        typedef Iter type;
    };

    template< class Iter >
    struct range_const_iterator< PSTADE_t >
    {
        typedef Iter type;
    };

    template< class Iter >
    struct range_const_iterator< PSTADE_t const >
    {
        typedef Iter type;
    };

    template< class Iter >
    struct range_size< PSTADE_t > :
        boost::iterator_difference<Iter>
    { };

    template< class Iter >
    struct range_size< PSTADE_t const > :
        boost::iterator_difference<Iter>
    { };


    namespace tuples {

        template< class Iter >
        Iter PSTADE_OVEN_BOOST_RANGE_BEGIN(PSTADE_t& x)
        {
            return boost::tuples::get<0>(x);
        }

        template< class Iter >
        Iter PSTADE_OVEN_BOOST_RANGE_BEGIN(PSTADE_t const& x)
        {
            return boost::tuples::get<0>(x);
        }

        template< class Iter >
        Iter PSTADE_OVEN_BOOST_RANGE_END(PSTADE_t& x)
        {
            return boost::tuples::get<1>(x);
        }

        template< class Iter >
        Iter PSTADE_OVEN_BOOST_RANGE_END(PSTADE_t const& x)
        {
            return boost::tuples::get<1>(x);
        }

        template< class Iter >
        typename boost::iterator_difference<Iter>::type boost_range_size(PSTADE_t const& x)
        {
            return 2;
        }

    } // namespace tuples


#undef  PSTADE_t


} // namespace boost


#endif
