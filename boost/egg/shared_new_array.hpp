#ifndef PSTADE_SHARED_NEW_ARRAY_HPP
#define PSTADE_SHARED_NEW_ARRAY_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <boost/shared_array.hpp>


namespace boost { namespace egg {


    template<class T>
    struct X_shared_new_array
    {
        typedef shared_array<T> result_type;

        result_type operator()(std::size_t n) const
        {
            return result_type(new T[n]);
        }
    };


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
