#ifndef PSTADE_ARG_HPP
#define PSTADE_ARG_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// "Forwarding Problem" workaround


// Usage:
//
// template< class T >
// void f(T& x);
//
// f(pstade::arg(1));


// Same as:
//
// help_rvalue_deduction
//   at <boost/spirit/phoenix/function/detail/function_eval.hpp>


namespace pstade {


template< class T >
T& arg(T& x)
{
	return x;
}


template< class T >
const T& arg(const T& x)
{
	return x;
}


} // namespace pstade


#endif
