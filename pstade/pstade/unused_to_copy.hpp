#ifndef PSTADE_UNUSED_TO_COPY_HPP
#define PSTADE_UNUSED_TO_COPY_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// A unary template constructor can win the overloading race
// against copy-constructor. So disable it.
// http://groups.google.com/group/comp.lang.c++.moderated/browse_frm/thread/eca7b43d751008cd/


// Usage:
//
// See "./oven/iter_range.hpp"


// Note:
//
// If your class can be a base, use this even if the parameter
// is const-qualified; in order to work around dark-side of the language.
// 12.8/8 says "the copy constructor for *the class* is used".
// But VC8's implicitly-defined copy-constructor/copy-assignment-operator
// passes derived object to base constructor without casting to base type.
// Then the template constructor of base might be chosen.
// Is it possible to copy from derived? It isn't very likely.
// That's why 'is_base_of' is checked.
// Also note that 'boost::base_from_member' seems broken by this VC++ behavior.


#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>


namespace pstade {


namespace unused_to_copy_detail {

    // 'void *' would accept any pointer.
    struct enabler;

}


template< class T, class A >
struct unused_to_copy :
    boost::disable_if<
        boost::mpl::or_<
            boost::is_same<T, A>,
            boost::is_base_of<T, A>
        >,
        unused_to_copy_detail::enabler *
    >
{ };


template< class T, class A >
struct unused_to_copy_assign :
    boost::disable_if<
        boost::mpl::or_<
            boost::is_same<T, A>,
            boost::is_base_of<T, A>
        >,
        T&
    >
{ };


} // namespace pstade


#endif
