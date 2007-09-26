#ifndef PSTADE_OVEN_INSERTER_HPP
#define PSTADE_OVEN_INSERTER_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iterator>
#include <pstade/adl_barrier.hpp>
#include "./detail/base_to_adaptor.hpp"


namespace pstade { namespace oven {


namespace inserter_detail {


    template< class Container >
    struct base_back
    {
        typedef
            std::back_insert_iterator<Container>
        result_type;

        result_type operator()(Container& x) const
        {
            return result_type(x);
        }
    };


    template< class Container >
    struct base_front
    {
        typedef
            std::front_insert_iterator<Container>
        result_type;

        result_type operator()(Container& x) const
        {
            return result_type(x);
        }
    };


    template< class Container >
    struct base
    {
        typedef
            std::insert_iterator<Container>
        result_type;

        result_type operator()(Container& x, typename Container::iterator i) const
        {
            return result_type(x, i);
        }
    };


} // namespace inserter_detail


PSTADE_ADL_BARRIER(inserter) { // for 'std'
    PSTADE_OVEN_BASE_TO_ADAPTOR(back_inserter, (inserter_detail::base_back<_>))
    PSTADE_OVEN_BASE_TO_ADAPTOR(front_inserter, (inserter_detail::base_front<_>))
    PSTADE_OVEN_BASE_TO_ADAPTOR(inserter, (inserter_detail::base<_>))
}


} } // namespace pstade::oven


#endif
