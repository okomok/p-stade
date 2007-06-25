#ifndef PSTADE_BASE_FROM_HPP
#define PSTADE_BASE_FROM_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// See './implicitly_defined.hpp"
// If your derived class is copyable, prefer this to
// 'boost::base_from_member'. Otherwise, VC7.1/8
// sometimes brings the derived class object
// to template constructor of 'base_from_member'.
// The workaorund is maybe to define copy-constructor
// and operator= of the derived class by your hand.
// Or, simply, shut away template constructors like below.
// Note that 'base_from' requires 'Member' to be CopyConstructible;
// Otherwise, you can of course use 'boost::base_from_member'.


namespace pstade {


template< class Member, int id = 0 >
struct base_from
{
    typedef base_from type;

protected:
    explicit base_from(Member const& m) :
        member(m)
    { }

    Member member;

    typedef Member member_type;

#if defined(__GNUC__)
    // 'typedef base_from type;' is bad for GCC3.4.
    // If you use this class as a metafunction, GCC complains
    // "with only non-default constructor in class without a constructor"
    // without this. (Boost1.34 seems to work around this.)
    base_from();
#endif
};


} // namespace pstade


#endif
