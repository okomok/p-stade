#ifndef PSTADE_VALUE_HPP
#define PSTADE_VALUE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/noncopyable.hpp>
#include <pstade/instance.hpp>
#include <pstade/remove_cvr.hpp>


namespace pstade {


    // Define from scratch.
    // Egg would turn the argument into reference;
    // that's the dark-side of the language in the
    // case of function reference.
    //


    namespace value_detail {


        struct fun
        {
            template< class Signature >
            struct result;

            template< class Self, class A >
            struct result<Self(A)> :
                remove_cvr<A>
            { };

            template< class A >
            A operator()(A a) const
            {
                return a;
            }
        };


    } // namespace value_detail


    typedef value_detail::fun const value_fun;
    PSTADE_INSTANCE(value_fun, value, value)


    namespace value_detail {


        struct pipe :
            private boost::noncopyable
        { };


        template< class A > inline
        A operator|(A a, pipe const&)
        {
            return a;
        }

        
    } // namespace value_detail


    PSTADE_INSTANCE(value_detail::pipe const, to_value, value)


} // namespace pstade


#endif
