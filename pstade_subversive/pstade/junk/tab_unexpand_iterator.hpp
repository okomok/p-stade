#ifndef PSTADE_OVEN_TAB_UNEXPAND_ITERATOR_HPP
#define PSTADE_OVEN_TAB_UNEXPAND_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)




namespace pstade { namespace oven {




PSTADE_OBJECT_GENERATOR(make_tab_unexpand_iterator,
    (tab_unexpand_iterator< deduce<_1, to_value> >) const)


} } // namespace pstade::oven


#endif
