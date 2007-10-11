#ifndef PSTADE_OVEN_DETAIL_ZIP_ITERATOR_HACK_HPP
#define PSTADE_OVEN_DETAIL_ZIP_ITERATOR_HACK_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Makes Forward*Input*Range zippable.


#include <boost/iterator/zip_iterator.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include "./pure_traversal.hpp"


namespace pstade { namespace oven { namespace detail {


    template< class IteratorTuple >
    struct minimum_traversal_category_in_iterator_tuple
    {
        typedef typename
            boost::detail::tuple_impl_specific::tuple_meta_transform<
                IteratorTuple,
                pure_traversal<boost::mpl::_1> // modified from boost::iterator_traversal<>
            >::type
        tuple_of_traversal_tags;

        typedef typename
            boost::detail::tuple_impl_specific::tuple_meta_accumulate<
                tuple_of_traversal_tags,
                boost::detail::minimum_category<>,
                boost::random_access_traversal_tag
            >::type
        type;
    };


} } } // namespace pstade::oven::detail


namespace boost { namespace detail {


    template< BOOST_PP_ENUM_PARAMS(10, class T) >
    struct minimum_traversal_category_in_iterator_tuple< tuples::tuple<BOOST_PP_ENUM_PARAMS(10, T)> > :
        pstade::oven::detail::minimum_traversal_category_in_iterator_tuple< tuples::tuple<BOOST_PP_ENUM_PARAMS(10, T)> >
    { };

    template< class Head, class Tail >
    struct minimum_traversal_category_in_iterator_tuple< tuples::cons<Head, Tail> > :
        pstade::oven::detail::minimum_traversal_category_in_iterator_tuple< tuples::cons<Head, Tail> >
    { };


} } // namespace boost::detail


#endif
