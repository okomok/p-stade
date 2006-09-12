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
#include "./transform_range.hpp"


namespace pstade { namespace oven {


namespace index_range_detail {


    template< class Incrementable, class UnaryFun >
    struct super_
    {
        typedef transform_range<
            counting_range<Incrementable> const,
            UnaryFun
        > type;
    };


} // namespace index_range_detail


template< class Incrementable, class UnaryFun >
struct index_range :
    index_range_detail::super_<Incrementable, UnaryFun>::type,
    private as_lightweight_proxy< index_range<Incrementable, UnaryFun> >
{
private:
    typedef typename index_range_detail::super_<Incrementable, UnaryFun>::type super_t;

public:
    index_range(Incrementable const& i, Incrementable const& j, UnaryFun const& fun) :
        super_t(counting_range<Incrementable>(i, j), fun)
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
