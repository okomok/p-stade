#ifndef PSTADE_EGG_FORWARD_HPP
#define PSTADE_EGG_FORWARD_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// We can't use this in function<>::operator().
// Otherwise, it introduces the forwarding problem into little functions.


#include <boost/type_traits/remove_cv.hpp>
#include <pstade/adl_barrier.hpp>
#include "./function_fwd.hpp"


namespace pstade { namespace egg {


    template<class A, class Strategy>
    struct result_of_forward
    {
        typedef A& type;
    };

    // must return non-const rvalue for movable types.
    template<class A>
    struct result_of_forward<A, by_value> :
        boost::remove_cv<A>
    { };


PSTADE_ADL_BARRIER(forward) { // for C++0x

    template<class Strategy, class A> inline
    typename result_of_forward<A, Strategy>::type
    forward(A& a)
    {
        return a;
    }

}


} } // namespace pstade::egg


#endif
