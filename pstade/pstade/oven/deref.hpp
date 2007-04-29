#ifndef PSTADE_OVEN_DEREF_HPP
#define PSTADE_OVEN_DEREF_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/indirect_reference.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <pstade/function.hpp>


namespace pstade { namespace oven {


namespace deref_detail {


    template< class Iterator >
    struct baby
    {
        typedef typename
            boost::indirect_reference<
                typename boost::remove_const<Iterator>::type
            >::type
        result_type;

        // Pass by reference. "./reverse_iterator.hpp" tells why.
        result_type operator()(Iterator& it) const
        {
            return *it;
        }
    };


} // namespace deref_detail


PSTADE_FUNCTION(deref, (deref_detail::baby<_>))


} } // namespace pstade::oven


#endif
