#ifndef PSTADE_CONST_HPP
#define PSTADE_CONST_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Same as: boost::lambda::make_const
//
// http://www.boost.org/doc/html/lambda/le_in_details.html#lambda.rvalues_as_actual_arguments


// See: oven::constants
//
// http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2004/n1674.pdf


// See: cbegin/cend proposal
//
// http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2004/n1674.pdf


namespace pstade {


template< class T > inline
T const& const_(T const& x)
{
    return x;
}


} // namespace pstade


#endif
