

// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(PSTADE_EGG_BY_PERFECT_NUMBER)
    #error Please define PSTADE_EGG_BY_PERFECT_NUMBER
#endif


    struct BOOST_PP_CAT(by_perfect, PSTADE_EGG_BY_PERFECT_NUMBER);


    template<class Baby>
    struct function<Baby, BOOST_PP_CAT(by_perfect, PSTADE_EGG_BY_PERFECT_NUMBER)>
    {
        typedef function function_type;
        typedef Baby baby_type;

        Baby m_baby;

        Baby baby() const
        {
            return m_baby;
        }

        template<class FunCall>
        struct result;

        #define  PSTADE_EGG_BY_PERFECT_TEMPLATE_ARITY PSTADE_EGG_BY_PERFECT_NUMBER
        #include PSTADE_EGG_BY_PERFECT_TEMPLATE()

        #include PSTADE_EGG_SIG_TEMPLATE()
    };


#undef  PSTADE_EGG_BY_PERFECT_NUMBER
