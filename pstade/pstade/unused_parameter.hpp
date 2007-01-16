#ifndef PSTADE_UNUSED_PARAMETER_HPP
#define PSTADE_UNUSED_PARAMETER_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade {


    struct unused_parameter
    {
        template<class T>
        unused_parameter(T const&)
        { }
    };


} // namespace pstade


#endif
