#ifndef PSTADE_NEW_SHARED_ARRAY_HPP
#define PSTADE_NEW_SHARED_ARRAY_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <boost/shared_array.hpp>
#include "./new_ptr.hpp"


namespace pstade { namespace egg {


    template<class X>
    struct pod_of_new_shared_array
    {
        struct type
        {
            typedef boost::shared_array<X> result_type;

            result_type operator()(std::size_t n) const
            {
                return result_type(new X[n]);
            }
        };
    };


    template<class X>
    struct X_new_shared_array :
        pod_of_new_shared_array<X>::type
    { };


} } // namespace pstade::egg


#endif
