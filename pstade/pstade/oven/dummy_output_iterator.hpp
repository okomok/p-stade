#ifndef PSTADE_OVEN_DUMMY_OUTPUT_ITERATOR_HPP
#define PSTADE_OVEN_DUMMY_OUTPUT_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: 'boost::graph_detail::dummy_output_iterator'
//
// at <boost/graph/biconnected_components.hpp>


#include <iterator> // output_iterator_tag
#include <pstade/instance.hpp>


namespace pstade { namespace oven {


struct dummy_output_iterator
{
    typedef std::output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void pointer;
    typedef int  difference_type;

    struct reference
    {
        template< class T >
        reference& operator=(const T&) { return *this; }
    };

    reference operator *() const { return reference(); }
    dummy_output_iterator& operator++() { return *this; }
    dummy_output_iterator operator++(int) { return *this; }
};


PSTADE_INSTANCE(dummy_output_iterator const, dummy_outputter, value)


} } // namespace pstade::oven


#endif
