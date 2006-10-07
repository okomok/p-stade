#ifndef PSTADE_OVEN_INDEX_RANGE_HPP
#define PSTADE_OVEN_INDEX_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./as_lightweight_proxy.hpp"
#include "./counting_range.hpp"
#include "./range_base.hpp"
#include "./transform_range.hpp"


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
            counting_range<Incrementable> const,
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
private:
    typedef typename index_range_detail::super_<Incrementable, UnaryFun, Reference, Value>::type super_t;
    typedef typename range_base<super_t>::type base_t;

public:
    index_range(Incrementable const& i, Incrementable const& j, UnaryFun const& fun) :
        super_t(base_t(i, j), fun)
    { }
};


template< class Incrementable, class UnaryFun > inline
index_range<Incrementable, UnaryFun> const
make_index_range(Incrementable const& i, Incrementable const& j, UnaryFun fun)
{
    return index_range<Incrementable, UnaryFun>(i, j, fun);
}


} } // namespace pstade::oven


#endif
