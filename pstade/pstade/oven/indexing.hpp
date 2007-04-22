#ifndef PSTADE_OVEN_INDEXING_HPP
#define PSTADE_OVEN_INDEXING_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/result_of.hpp>
#include <pstade/constant.hpp>
#include <pstade/function.hpp>
#include "./counting.hpp"
#include "./transformed.hpp"


namespace pstade { namespace oven {


template<
    class Incrementable1, class Incrementable2, class UnaryFun,
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct indexing_base
{
    typedef typename
        boost::result_of<
            op_make_transformed<Reference, Value>(
                typename boost::result_of<op_counting<>(Incrementable1&, Incrementable2&)>::type,
                UnaryFun&
            )
        >::type
    result_type;

    result_type operator()(Incrementable1& i, Incrementable2& j, UnaryFun& fun) const
    {
        return
            op_make_transformed<Reference, Value>()(
                counting(i, j),
                fun
            );
    }
};


template<
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct op_indexing :
    function<
        indexing_base<
            boost::mpl::_1, boost::mpl::_2, boost::mpl::_3,
            Reference, Value
        >
    >
{ };


PSTADE_CONSTANT(indexing, (op_indexing<>))


} } // namespace pstade::oven


#endif
