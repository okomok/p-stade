#ifndef PSTADE_LIME_DETAIL_LOAD_FILE_FWD_HPP
#define PSTADE_LIME_DETAIL_LOAD_FILE_FWD_HPP


// PStade.Lime
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include "./node_fwd.hpp"


namespace pstade { namespace lime {


template< class Interface >
void load_file(node<Interface>& root, std::string fileName);


} } // namespace pstade::lime


#endif
