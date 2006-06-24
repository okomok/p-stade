#ifndef PSTADE_OVEN_NULL_OUTPUTTER_HPP
#define PSTADE_OVEN_NULL_OUTPUTTER_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iterator> // iterator, output_iterator_tag
#include <pstade/unused.hpp>
#include <pstade/instance.hpp>


namespace pstade { namespace oven {


struct null_output_iterator :
    std::iterator<std::output_iterator_tag, void, void, void, void>
{
    null_output_iterator()
    { }

    template< class ValueT > // template is legal
    const null_output_iterator& operator=(const ValueT& val) const
    {
        pstade::unused(val);
        return *this;
    }

    const null_output_iterator& operator*() const { return *this; }
    const null_output_iterator& operator++() const { return *this; }
    const null_output_iterator operator++(int) const { return *this; }
};


PSTADE_INSTANCE(const null_output_iterator, null_outputter, value)


} } // namespace pstade::oven


#endif
