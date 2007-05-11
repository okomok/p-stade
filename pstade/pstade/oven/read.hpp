#ifndef PSTADE_OVEN_READ_HPP
#define PSTADE_OVEN_READ_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// A readerence of ReadableIterator returns a type "convertible" to
// associated 'value_type', but it is useless for writing generic code.
//
// Once 'read' is applied to non-Lvalue one, the result is not Assignable,
// meaning that the iterator loses Writability.


#include <iterator> // istreambuf_iterator
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/function.hpp>


namespace pstade { namespace oven {


namespace read_detail {


    template< class T >
    struct is_istreambuf_iterator :
        boost::mpl::false_
    { };

    template< class CharT, class Traits >
    struct is_istreambuf_iterator< std::istreambuf_iterator<CharT, Traits> > :
        boost::mpl::true_
    { };


} // namespace read_detail


template< class ReadableOrLvalueIter >
struct iterator_read
{
    typedef typename
        boost::remove_cv<ReadableOrLvalueIter>::type
    iter_t;

    typedef typename
        boost::iterator_value<iter_t>::type
    val_t;

    typedef typename
        boost::iterator_reference<iter_t>::type
    ref_t;

    typedef
        boost::mpl::or_<
            boost::is_same<ref_t, val_t&>,
            boost::is_same<ref_t, val_t const&>,
            boost::is_same<ref_t, val_t const volatile&>
        >
    is_ref;

    // Works around a gcc and msvc STL bug that
    // 'istreambuf_iterator<>::reference' is wrongly a reference type.
    typedef
        boost::mpl::and_<
            boost::mpl::not_< read_detail::is_istreambuf_iterator<iter_t> >,
            is_ref
        >
    is_ref_;

    typedef typename
        boost::mpl::if_< is_ref_,
            ref_t,
            val_t
        >::type
    type;
};


namespace read_detail {


    template< class ReadableOrLvalueIter >
    struct baby
    {
        typedef typename
            iterator_read<ReadableOrLvalueIter>::type
        result_type;

        // Pass by reference; see "./reverse_iterator.hpp"
        result_type operator()(ReadableOrLvalueIter& it) const
        {
            return *it;
        }
    };


} // namespace read_detail


PSTADE_FUNCTION(read, (read_detail::baby<_>))


} } // namespace pstade::oven


#endif
