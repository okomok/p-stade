#ifndef PSTADE_NONASSIGNABLE_HPP
#define PSTADE_NONASSIGNABLE_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: 'boost::numeric::ublas::nonassignable'
//
// at <boost/numeric/ublas/detail/definitions.hpp>


#include <pstade/adl_barrier.hpp>


namespace pstade {

PSTADE_ADL_BARRIER(nonassignable) {


struct nonassignable
{
protected:
    nonassignable()
    { }

    ~nonassignable()
    { }

private:
    nonassignable const& operator=(nonassignable const&);
};


} // ADL barrier

} // namespace pstade


#endif
