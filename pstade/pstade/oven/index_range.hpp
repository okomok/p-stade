#ifndef PSTADE_OVEN_INDEX_RANGE_HPP
#define PSTADE_OVEN_INDEX_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)



#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./counting.hpp"
#include "./range_base.hpp"
#include "./transformed.hpp"


namespace pstade { namespace oven {


namespace index_range_detail {


    template<
        class Incrementable,
        class UnaryFun,
        class Reference,
        class Value
    >
    struct super_
    {
        typedef transform_range<
            count_range<Incrementable> const,
            UnaryFun,
            Reference, Value
        > type;
    };


} // namespace index_range_detail


template<
    class Incrementable,
    class UnaryFun,
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct index_range :
    index_range_detail::super_<Incrementable, UnaryFun, Reference, Value>::type,
    private as_lightweight_proxy< index_range<Incrementable, UnaryFun, Reference, Value> >
{
    typedef index_range type;

private:
    typedef typename index_range_detail::super_<Incrementable, UnaryFun, Reference, Value>::type super_t;
    typedef typename range_base<super_t>::type base_t;

public:
    index_range(Incrementable const& i, Incrementable const& j, UnaryFun const& fun) :
        super_t(base_t(i, j), fun)
    { }
};

PSTADE_OBJECT_GENERATOR(make_index_range,
    (index_range< deduce<_1, to_value>, deduce<_3, to_value> >) const)


} } // namespace pstade::oven


#endif
