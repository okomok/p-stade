#ifndef PSTADE_EGG_DETAIL_NATIVE_TYPEOF_HPP
#define PSTADE_EGG_DETAIL_NATIVE_TYPEOF_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright (C) 2004 Arkadiy Vertleyb
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#if defined(__COMO__)
#   ifdef __GNUG__
#       ifndef(BOOST_pstade_typeof_EMULATION)
#           ifndef BOOST_pstade_typeof_NATIVE
#               define BOOST_pstade_typeof_NATIVE
#           endif
#           define BOOST_pstade_typeof_KEYWORD typeof
#       endif
#   else
#       ifndef BOOST_pstade_typeof_NATIVE
#           ifndef BOOST_pstade_typeof_EMULATION
#               define BOOST_pstade_typeof_EMULATION
#           endif
#       else
#           error native typeof is not supported
#       endif
#   endif

#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
#   ifdef __GNUC__
#       ifndef BOOST_pstade_typeof_EMULATION
#           ifndef BOOST_pstade_typeof_NATIVE
#               define BOOST_pstade_typeof_NATIVE
#           endif
#           define BOOST_pstade_typeof_KEYWORD __typeof__
#       endif
#   else
#       ifndef BOOST_pstade_typeof_NATIVE
#           ifndef BOOST_pstade_typeof_EMULATION
#               define BOOST_pstade_typeof_EMULATION
#           endif
#       else
#           error native typeof is not supported
#       endif
#   endif

#elif defined(__GNUC__)
#   ifndef BOOST_pstade_typeof_EMULATION
#       ifndef BOOST_pstade_typeof_NATIVE
#           define BOOST_pstade_typeof_NATIVE
#       endif
#       define BOOST_pstade_typeof_KEYWORD __typeof__
#   endif

#elif defined(__MWERKS__)
#   if(__MWERKS__ <= 0x3003)  // 8.x
#       ifndef BOOST_pstade_typeof_EMULATION
#           ifndef BOOST_pstade_typeof_NATIVE
#               define BOOST_pstade_typeof_NATIVE
#           endif
#           define BOOST_pstade_typeof_KEYWORD __typeof__
#       else
#           error typeof emulation is not supported
#       endif
#   else // 9.x
#       ifndef BOOST_pstade_typeof_EMULATION
#           ifndef BOOST_pstade_typeof_NATIVE
#               define BOOST_pstade_typeof_NATIVE
#           endif
#           define BOOST_pstade_typeof_KEYWORD __typeof__
#       endif
#   endif

#elif defined(_MSC_VER)
#   if (_MSC_VER <= 1300)  // 6.5, 7.0
#       ifndef BOOST_pstade_typeof_EMULATION
#           ifndef BOOST_pstade_typeof_NATIVE
#               define BOOST_pstade_typeof_NATIVE
#           endif
//#           include <boost/typeof/msvc/typeof_impl.hpp>
#           define MSVC_pstade_typeof_HACK
#       else
#           error typeof emulation is not supported
#       endif
#   elif (_MSC_VER == 1310)  // 7.1
#       ifndef BOOST_pstade_typeof_EMULATION
#           ifndef BOOST_pstade_typeof_NATIVE
#               define BOOST_pstade_typeof_NATIVE
#           endif
//#           include <boost/typeof/msvc/typeof_impl.hpp>
#           define MSVC_pstade_typeof_HACK
#       endif
#   else // 8.0
#       ifndef BOOST_pstade_typeof_NATIVE
#           ifndef BOOST_pstade_typeof_EMULATION
#               define BOOST_pstade_typeof_EMULATION
#           endif
#       else
#           error native typeof is not supported
#       endif
#   endif

#else //unknown compiler
#   ifndef BOOST_pstade_typeof_NATIVE
#       ifndef BOOST_pstade_typeof_EMULATION
#           define BOOST_pstade_typeof_EMULATION
#       endif
#   else
#       ifndef BOOST_pstade_typeof_KEYWORD
#           define BOOST_pstade_typeof_KEYWORD typeof
#       endif
#   endif

#endif


#if defined(BOOST_pstade_typeof_NATIVE)
    #define PSTADE_EGG_HAS_NATIVE_TYPEOF
    #include <boost/typeof/typeof.hpp>
    #define PSTADE_EGG_NATIVE_TYPEOF     BOOST_TYPEOF
    #define PSTADE_EGG_NATIVE_TYPEOF_TPL BOOST_TYPEOF_TPL
    #define PSTADE_EGG_NATIVE_TYPEOF_NESTED_TYPEDEF     BOOST_TYPEOF_NESTED_TYPEDEF
    #define PSTADE_EGG_NATIVE_TYPEOF_NESTED_TYPEDEF_TPL BOOST_TYPEOF_NESTED_TYPEDEF_TPL
#endif


#endif
