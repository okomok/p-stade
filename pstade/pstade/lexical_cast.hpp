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
#include <boost/utility/result_of.hpp>
#include <pstade/auto_castable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include <pstade/to_type.hpp>


namespace pstade {


    struct op_lexical_cast :
        to_type_cast_result
    {
        template< class From, class Type_To >
        typename to_type<Type_To>::type operator()(From const& from, Type_To) const
        {
            return boost::lexical_cast<typename to_type<Type_To>::type>(from);
        }
    };


    PSTADE_CONSTANT(lexical_cast, (op_lexical_cast))
    PSTADE_PIPABLE(lexicalized, (boost::result_of<op_auto_castable(op_lexical_cast)>::type))


} // namespace pstade


#endif
