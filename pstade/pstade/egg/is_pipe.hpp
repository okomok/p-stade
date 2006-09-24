#ifndef PSTADE_EGG_IS_PIPE_HPP
#define PSTADE_EGG_IS_PIPE_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/metapredicate.hpp>
#include <pstade/remove_cvr.hpp>


namespace pstade_egg_extension {


    PSTADE_METAPREDICATE(pipe, pstade_egg)


} // namespace pstade_egg_extension


namespace pstade { namespace egg {


    template< class T >
    struct is_pipe :
        pstade_egg_extension::is_pipe<
            typename remove_cvr<T>::type
        >
    { };


    using pstade_egg_extension::as_pipe;


} } // namespace pstade::egg


#endif
