#ifndef PSTADE_BASE_FROM_HPP
#define PSTADE_BASE_FROM_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// If your derived class is copyable, prefer this to
// 'boost::base_from_member'. Otherwise, VC7.1/8
// sometimes brings the derived class object
// to template constructor of 'base_from_member'.
// The workaorund is maybe to define copy-constructor 
// and operator= of the derived class by your hand.
// Or, simply, shut away template constructors like below.
// Note that 'base_from' requires 'Member' to be CopyConstructible.


namespace pstade {


template< class Member, int id = 0 >
struct base_from
{
protected:
    explicit base_from(Member const& m) :
        member(m)
    { }

    Member member;

    typedef Member member_type;
};


} // namespace pstade


#endif
