
#if !defined(BOOST_PP_IS_ITERATING)

        #include <boost/preprocessor/cat.hpp>
        #include <boost/preprocessor/iteration/iterate.hpp>
        #include <boost/preprocessor/iteration/local.hpp>
        #include <boost/preprocessor/repetition/enum_params.hpp>
        #include "../../config/limit_idset_size.hpp"

        // local macro
        #define PSTADE_KETCHUP_idsetn_statement(z, i, unused) \
        if (ID##i == id) \
        { \
            return true; \
        } \
        /**/

        // header

        namespace pstade { namespace ketchup {

// empty
template< UINT Dummy = 0 >
struct idset0;

template< >
struct idset0<0>
{
    static bool contains(UINT)
    {
        return false;
    }
};


        #define BOOST_PP_ITERATION_LIMITS (1, PSTADE_KETCHUP_LIMIT_IDSET_SIZE)
        #define BOOST_PP_FILENAME_1 "./idsetn.hpp"
        #include BOOST_PP_ITERATE()

        // clean up

        } } // namespace pstade::ketchup
        
        #undef PSTADE_KETCHUP_idsetn_statement


#else // BOOST_PP_IS_ITERATING

    #define n BOOST_PP_ITERATION()


template<
    BOOST_PP_ENUM_PARAMS(n, UINT ID)
>
struct BOOST_PP_CAT(idset, n)
{
    static bool contains(UINT id)
    {
        #define BOOST_PP_LOCAL_MACRO(n) PSTADE_KETCHUP_idsetn_statement(~, n, ~)
        #define BOOST_PP_LOCAL_LIMITS (0, n-1)
        #include BOOST_PP_LOCAL_ITERATE()
        #undef BOOST_PP_LOCAL_MACRO

        return false;
    }
};


    #undef n

#endif // BOOST_PP_IS_ITERATING
