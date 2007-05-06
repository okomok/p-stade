#ifndef PSTADE_OVEN_REFERENT_HPP
#define PSTADE_OVEN_REFERENT_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// A dereference of ReadableIterator returns a type "convertible" to
// associated 'value_type', but it is useless for writing generic code.


// Precondition:
//
// 'Iterator' is Readable or Lvalue.


#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <pstade/function.hpp>


namespace pstade { namespace oven {


namespace referent_detail {


    template< class Value, class Reference >
    struct result_
    {
        // doesn't need 'boost::is_lvalue_iterator'; by the precondition.
        typedef
            boost::mpl::or_<
                boost::is_same<Value&, Reference>,
                boost::is_same<Value const&, Reference>
            >
        is_lvalue;

        typedef typename
            boost::mpl::if_< is_lvalue,
                Reference,
                Value
            >::type
        type;
    };


    template< class Iterator >
    struct baby
    {
        typedef typename
            boost::remove_const<Iterator>::type
        iter_t;

        typedef typename
            boost::iterator_value<iter_t>::type
        val_t;

        typedef typename
            boost::iterator_reference<iter_t>::type
        ref_t;

        typedef typename
            result_<val_t, ref_t>::type
        result_type;

        // Pass by reference; see "./reverse_iterator.hpp"
        result_type operator()(Iterator& it) const
        {
            return *it;
        }
    };


} // namespace referent_detail


PSTADE_FUNCTION(referent, (referent_detail::baby<_>))


} } // namespace pstade::oven


#endif
