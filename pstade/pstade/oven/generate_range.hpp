#ifndef PSTADE_OVEN_GENERATE_RANGE_HPP
#define PSTADE_OVEN_GENERATE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./as_lightweight_proxy.hpp"
#include "./generate_iterator.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace generate_range_detail {


    template< class Generator, class Traversal >
    struct super_ :
        iter_range<
            generate_iterator<Generator, Traversal>
        >
    { };


} // namespace generate_range_detail


template<
    class Generator,
    class Traversal = boost::single_pass_traversal_tag
>
struct generate_range :
    generate_range_detail::super_<Generator, Traversal>::type,
    private as_lightweight_proxy< generate_range<Generator, Traversal> >
{
    typedef Generator generator_type;

private:
    typedef typename generate_range_detail::super_<Generator, Traversal>::type super_t;
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

template< class Generator, class Traversal > inline
generate_range<Generator, Traversal> const
make_generate_range(Generator gen, Traversal)
{
    return generate_range<Generator, Traversal>(gen);
}


// 'make_generate_range<Gen&>(gen);' seems cumbersome?
template< class Generator > inline
generate_range<Generator&> const
generation(Generator& gen)
{
    return generate_range<Generator&>(gen);
}

template< class Generator, class Traversal > inline
generate_range<Generator&, Traversal> const
generation(Generator& gen, Traversal)
{
    return generate_range<Generator&, Traversal>(gen);
}


} } // namespace pstade::oven


#endif
