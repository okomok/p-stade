#ifndef PSTADE_OVEN_GENERATE_RANGE_HPP
#define PSTADE_OVEN_GENERATE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>
#include <pstade/object_generator.hpp>
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
    typedef generate_range type;
    typedef Generator generator_type;

private:
    typedef typename generate_range_detail::super_<Generator, Traversal>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit generate_range(Generator gen, unused_argument = unused_argument()) :
        super_t(
            iter_t(gen, boost::mpl::true_()),
            iter_t(gen, boost::mpl::false_())
        )
    { }
};


PSTADE_OBJECT_GENERATOR(make_generate_range,
    const(generate_range< deduce_to_value<from_1>, deduce_to_value<from_2, boost::single_pass_traversal_tag> >))

// It is always SinglePass if Generator is reference.
PSTADE_OBJECT_GENERATOR(generation, const(generate_range< deduce_to_reference<from_1> >))


} } // namespace pstade::oven


#endif
