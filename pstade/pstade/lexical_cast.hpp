#ifndef PSTADE_LEXICAL_CAST_HPP
#define PSTADE_LEXICAL_CAST_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://d.hatena.ne.jp/Cryolite/20061101


#include <boost/lexical_cast.hpp>
#include <pstade/auto_castable.hpp>
#include <pstade/pipable.hpp>
#include <pstade/singleton.hpp>
#include <pstade/to_type.hpp>


namespace pstade {


    struct lexical_cast_fun :
        to_type_cast_result
    {
        template< class From, class Type_To >
        typename to_type<Type_To>::type operator()(From from, Type_To) const
        {
            return boost::lexical_cast<typename to_type<Type_To>::type>(from);
        }
    };

    PSTADE_SINGLETON_CONST(lexical_cast_fun, lexical_cast)


    PSTADE_AUTO_CASTABLE(lexical, lexical_cast_fun) // will be removed.
    PSTADE_PIPABLE(lexicalized, lexical_fun)


} // namespace pstade


#endif
