#ifndef PSTADE_OVEN_ARRAY_RANGE_HPP
#define PSTADE_OVEN_ARRAY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <boost/noncopyable.hpp>
#include <boost/scoped_array.hpp>
#include <boost/utility/base_from_member.hpp>
#include "./iter_range.hpp"
#include "./range_constantable.hpp"


namespace pstade { namespace oven {


namespace array_range_detail {


    template< class Value >
    struct init
    {
        typedef boost::base_from_member<
            boost::scoped_array<Value>
        > type;
    };


} // namespace array_range_detail


template< class Value >
struct array_range :
    private array_range_detail::init<Value>::type,
    iter_range<Value *>::type,
    private range_constantable<array_range<Value>, Value const *>,
    private boost::noncopyable
{
    typedef Value const *const_iterator; // "override" it!

private:
    typedef typename array_range_detail::init<Value>::type init_t;
    typedef typename iter_range<Value *>::type super_t;

public:
    explicit array_range(std::size_t sz) :
        init_t(new Value[sz]),
        super_t(init_t::member.get(), init_t::member.get() + sz)
    { }
};


} } // namespace pstade::oven


#endif
