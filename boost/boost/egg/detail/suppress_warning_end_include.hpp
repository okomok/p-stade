

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if defined(BOOST_MSVC)

    #pragma warning(pop)

    #if defined(BOOST_EGG_SCL_SECURE_NO_DEPRECATE)
        #undef BOOST_EGG_SCL_SECURE_NO_DEPRECATE
        #undef _SCL_SECURE_NO_DEPRECATE
    #endif

    #if defined(BOOST_EGG_CRT_SECURE_NO_DEPRECATE)
        #undef BOOST_EGG_CRT_SECURE_NO_DEPRECATE
        #undef _CRT_SECURE_NO_DEPRECATE
    #endif

#endif
