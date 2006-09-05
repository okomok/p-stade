#ifndef PSTADE_SAUSAGE_DETAIL_ROUTINE_RESULT_HPP
#define PSTADE_SAUSAGE_DETAIL_ROUTINE_RESULT_HPP


// PStade.Sausage
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)



namespace pstade { namespace sausage { namespace detail {


template< class Routine >
struct routine_result
{
    typedef typename Routine::routine_result_type type;
};


} } } // namespace pstade::sausage::detail


#endif
