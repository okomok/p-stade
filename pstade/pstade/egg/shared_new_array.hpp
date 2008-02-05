#ifndef PSTADE_SHARED_NEW_ARRAY_HPP
#define PSTADE_SHARED_NEW_ARRAY_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <boost/shared_array.hpp>


namespace pstade { namespace egg {


    template<class X>
    struct X_shared_new_array
    {
        typedef boost::shared_array<X> result_type;

        result_type operator()(std::size_t n) const
        {
            return result_type(new X[n]);
        }
    };


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif
