#ifndef PSTADE_OVEN_DEREFERENCE_HPP
#define PSTADE_OVEN_DEREFERENCE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_traits.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <pstade/function.hpp>


namespace pstade { namespace oven {


namespace dereference_detail {


    template< class Iterator >
    struct baby
    {
        typedef typename
            boost::iterator_reference<
                typename boost::remove_const<Iterator>::type
            >::type
        result_type;

        // Pass by reference. "./reverse_iterator.hpp" tells why.
        result_type operator()(Iterator& it) const
        {
            return *it;
        }
    };


} // namespace dereference_detail


PSTADE_FUNCTION(dereference, (dereference_detail::baby<_>))


} } // namespace pstade::oven


#endif
