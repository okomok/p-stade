#ifndef PSTADE_VALUE_HPP
#define PSTADE_VALUE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/identity.hpp>
#include <boost/noncopyable.hpp>
#include <pstade/constant.hpp>
#include <pstade/object_generator.hpp>


namespace pstade {


    // Define this without 'callable' nor 'pipable'.
    // They would turn the argument into reference;
    // that's the dark-side of the language in the
    // case of function reference.


    typedef object_generator< boost::mpl::identity<object_arg1> > op_value;
    PSTADE_CONSTANT(value, op_value)


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


    PSTADE_CONSTANT(to_value, value_detail::pipe)


} // namespace pstade


#endif
