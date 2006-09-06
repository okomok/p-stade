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


    template< class UnaryFun, class Incrementable >
    struct super_
    {
        typedef transform_range<
            counting_range<Incrementable> const,
            UnaryFun
        > type;
    };


} // namespace index_range_detail


template<
    class UnaryFun,
    class Incrementable = std::size_t
>
struct index_range :
    index_range_detail::super_<UnaryFun, Incrementable>::type,
    private as_lightweight_proxy< index_range<UnaryFun, Incrementable> >
{
private:
    typedef typename index_range_detail::super_<UnaryFun, Incrementable>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    index_range(UnaryFun fun, Incrementable i, Incrementable j) :
        super_t(counting_range<Incrementable>(i, j), fun)
    { }
};


template< class Incrementable, class UnaryFun > inline
index_range<UnaryFun, Incrementable> const
make_index_range(UnaryFun fun, Incrementable i, Incrementable j)
{
    return index_range<UnaryFun, Incrementable>(fun, i, j);
}


} } // namespace pstade::oven


#endif
