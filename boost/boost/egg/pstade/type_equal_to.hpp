#ifndef PSTADE_TYPE_EQUAL_TO_HPP
#define PSTADE_TYPE_EQUAL_TO_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// See <boost/python/type_id.hpp>.


#include <typeinfo>
#include <boost/egg/pstade/make_bool.hpp>
#include <boost/egg/pstade/pod_constant.hpp>


# if (defined(__GNUC__) && __GNUC__ >= 3) \
 || defined(_AIX) \
 || (   defined(__sgi) && defined(__host_mips)) \
 || (defined(__hpux) && defined(__HP_aCC)) \
 || (defined(linux) && defined(__INTEL_COMPILER) && defined(__ICC))
#  define PSTADE_TYPE_EQUAL_TO_WORKAROUND
#  include <cstring> // strcmp
# endif 


namespace pstade {


    struct T_type_equal_to
    {
        typedef bool result_type;

        result_type operator()(std::type_info const &i, std::type_info const &j) const
        {
#if defined(PSTADE_TYPE_EQUAL_TO_WORKAROUND)
            return !std::strcmp(i.name(), j.name());
#else
            return make_bool(i == j);
#endif
        }
    };


    PSTADE_POD_CONSTANT((T_type_equal_to), type_equal_to) = {};


} // namespace pstade


#endif
