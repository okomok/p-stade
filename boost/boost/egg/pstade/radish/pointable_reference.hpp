#ifndef PSTADE_RADISH_POINTABLE_REFERENCE_HPP
#define PSTADE_RADISH_POINTABLE_REFERENCE_HPP


// PStade.Radish
//
// Copyright Shunsuke Sogame 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace radish {


template< class T >
struct pointable_reference
{
    typedef T& type;
};

template< >
struct pointable_reference<void>
{
    typedef void type;
};

template< >
struct pointable_reference<void const>
{
    typedef void type;
};

template< >
struct pointable_reference<void volatile>
{
    typedef void type;
};

template< >
struct pointable_reference<void const volatile>
{
    typedef void type;
};


} } // namespace pstade::radish


#endif
