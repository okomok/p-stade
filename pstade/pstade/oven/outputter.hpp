#pragma once

#if !defined(PSTADE_CFG_NO_STD_IOSTREAM)


#include <iosfwd>
#include <iterator> // for ostream_iterator
#include <boost/type.hpp>

namespace pstade { namespace oven {


///////////////////////////////////////////////////////////////////////////////
// outputter, missing from std
//
//   Reason why: boost::type
//     1. 'Default Function Template Arguments' is missing from C++ Standard.
//     2. Function calls using 'Explicit Template Arguments' make difficulty and
//        inconsistency, especially if overloadings are required.
//     3. 'boost::mpl::identity' that is adopted by Boost.Fusion also is possible,
//        but I like its bold name for important workarounds.
//
//   Reason why not: make_ostream_iterator
//     Object-generators of iterators are named differently, like 'back_inserter'.
//
template< class T, class ElemT, class TraitsT > inline
std::ostream_iterator<T, ElemT, TraitsT>
outputter(boost::type<T>, std::basic_ostream<ElemT, TraitsT>& out, const ElemT *delim = 0)
{
	return std::ostream_iterator<T, ElemT, TraitsT>(out, delim);
}

// T == ElemT
template< class ElemT, class TraitsT > inline
std::ostream_iterator<ElemT, ElemT, TraitsT>
outputter(std::basic_ostream<ElemT, TraitsT>& out, const ElemT *delim = 0)
{
	return std::ostream_iterator<ElemT, ElemT, TraitsT>(out, delim);
}


} } // namespace pstade::oven


#endif // !defined(PSTADE_CFG_NO_STD_IOSTREAM)
