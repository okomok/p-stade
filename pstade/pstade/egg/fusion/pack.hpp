#ifndef PSTADE_EGG_FUSION_PACK_HPP
#define PSTADE_EGG_FUSION_PACK_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/fusion/include/vector.hpp>
#include "../detail/xxx_pack.hpp"


// vector0 is not template.
#define  PSTADE_EGG_FUSION_PACK_TEMPLATE(_) boost::fusion::vector
#define  PSTADE_EGG_XXX_PACK_PARAMS (fusion_pack, PSTADE_EGG_FUSION_PACK_TEMPLATE, FUSION_MAX_VECTOR_SIZE)
#include PSTADE_EGG_XXX_PACK()


#include "../detail/suffix.hpp"
#endif
