#ifndef PSTADE_SAUSAGE_DETAIL_YIELDED_HPP
#define PSTADE_SAUSAGE_DETAIL_YIELDED_HPP


// PStade.Sausage
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)



namespace pstade { namespace sausage { namespace detail {


template< class Generator >
struct yielded
{
    typedef typename Generator::yielded_type type;
};


} } } // namespace pstade::sausage::detail


#endif
