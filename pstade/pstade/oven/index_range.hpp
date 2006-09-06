#ifndef PSTADE_OVEN_INDEX_RANGE_HPP
#define PSTADE_OVEN_INDEX_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./index_iterator.hpp"


namespace pstade { namespace oven {


namespace index_range_detail {


    template<
        class UnaryFun,  class Index,
        class Reference, class Value, class Difference
    >
    struct super_
    {
        typedef boost::iterator_range<
            index_iterator<UnaryFun, Index, Reference, Value, Difference>
        > type;
    };


} // namespace index_range_detail


template<
    class UnaryFun,
    class Index      = std::size_t,
    class Reference  = boost::use_default,
    class Value      = boost::use_default,
    class Difference = std::ptrdiff_t
>
struct index_range :
    index_range_detail::super_<UnaryFun, Index, Reference, Value, Difference>::type,
    private as_lightweight_proxy< index_range<UnaryFun, Index, Reference, Value, Difference> >
{
private:
    typedef typename index_range_detail::super_<UnaryFun, Index, Reference, Value, Difference>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    index_range(UnaryFun fun, Index i, Index j) :
        super_t(iter_t(fun, i), iter_t(fun, j))
    { }
};


template< class Index, class UnaryFun > inline
index_range<UnaryFun, Index> const
make_index_range(UnaryFun fun, Index i, Index j)
{
    return index_range<UnaryFun, Index>(fun, i, j);
}


} } // namespace pstade::oven


#endif
