#ifndef PSTADE_OVEN_COUNT_RANGE_HPP
#define PSTADE_OVEN_COUNT_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <limits> // numeric_limits
#include <boost/assert.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/iterator_categories.hpp> // iterator_traversal
#include <boost/utility/result_of.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include <pstade/unused.hpp>
#include <pstade/tupled.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace count_range_detail {


    template< class Incrementable > inline
    bool is_valid(Incrementable const& i, Incrementable const& j, boost::single_pass_traversal_tag)
    {
        pstade::unused(i, j);
        return true;
    }

    template< class Incrementable > inline
    bool is_valid(Incrementable const& i, Incrementable const& j, boost::random_access_traversal_tag)
    {
        return i <= j;
    }


    template< class Super, class Incrementable > inline
    Super make(Incrementable const& i, Incrementable const& j)
    {
        typedef typename Super::iterator iter_t;
        typedef typename boost::iterator_traversal<iter_t>::type trv_t;
        BOOST_ASSERT( (is_valid)(i, j, trv_t()) );

        return Super(iter_t(i), iter_t(j));
    }


    template<
        class Incrementable,
        class CategoryOrTraversal,
        class Difference
    >
    struct super_ :
        iter_range<
            boost::counting_iterator<Incrementable, CategoryOrTraversal, Difference>
        >
    { };


} // namespace count_range_detail


template<
    class Incrementable,
    class CategoryOrTraversal = boost::use_default,
    class Difference          = boost::use_default
>
struct count_range :
    count_range_detail::super_<Incrementable, CategoryOrTraversal, Difference>::type,
    private as_lightweight_proxy< count_range<Incrementable, CategoryOrTraversal, Difference> >
{
private:
    typedef typename
        count_range_detail::super_<Incrementable, CategoryOrTraversal, Difference>::type
    super_t;

public:
    count_range(Incrementable const& i, Incrementable const& j) :
        super_t(count_range_detail::make<super_t>(i, j))
    { }
};


PSTADE_OBJECT_GENERATOR(make_count_range, const count_range, (by_value))
PSTADE_PIPABLE(counted, boost::result_of<op_tupled(op_make_count_range)>::type)


// Note:
// 'make_count_range(0, non_int_t(i))' doesn't compile.
// 'make_count_range(non_int_t(0), non_int_t(i))' compiles,
// but seems cumbersome, especially if 'non_int_t' is 
// not easy to know. Also note that something like 'int_range'
// would get stuck into a hell of cast. So we define...
//

template< class Incrementable_, class Incrementable > inline
count_range<Incrementable> const
count_from_to(Incrementable_ const& i, Incrementable const& j)
{
    // suppress warning using 'static_cast'.
    return count_range<Incrementable>(static_cast<Incrementable>(i), j);
}

template< class Incrementable > inline
count_range<Incrementable> const
count_from(Incrementable const& i)
{
    return count_range<Incrementable>(i, (std::numeric_limits<Incrementable>::max)());
}

template< class Incrementable > inline
count_range<Incrementable> const
count_to(Incrementable const& j)
{
    return count_range<Incrementable>(0, j);
}


} } // namespace pstade::oven


#endif
