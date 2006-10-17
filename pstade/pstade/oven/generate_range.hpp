#ifndef PSTADE_OVEN_GENERATE_RANGE_HPP
#define PSTADE_OVEN_GENERATE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./generate_iterator.hpp"


namespace pstade { namespace oven {


namespace generate_range_detail {


    template< class Generator >
    struct super_
    {
        typedef boost::iterator_range<
            generate_iterator<Generator>
        > type;
    };


} // namespace generate_range_detail


template< class Generator >
struct generate_range :
    generate_range_detail::super_<Generator>::type,
    private as_lightweight_proxy< generate_range<Generator> >
{
    typedef Generator generator_type;

private:
    typedef typename generate_range_detail::super_<Generator>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit generate_range(Generator gen) :
        super_t(iter_t(gen, true), iter_t(gen, false))
    { }
};


template< class Generator > inline
generate_range<Generator> const
make_generate_range(Generator gen)
{
    return generate_range<Generator>(gen);
}


// 'make_generate_range<Gen&>(gen);' seems not a good thing.
template< class Generator > inline
generate_range<Generator&> const
generation(Generator& gen)
{
    return generate_range<Generator&>(gen);
}


} } // namespace pstade::oven


#endif
