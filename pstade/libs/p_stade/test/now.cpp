#include <pstade/../libs/wine/test/contract.cpp>


#if 0

#include <boost/optional.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/mpl/if.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <cassert>
#include <pstade/nonassignable.hpp>
#include <pstade/assignable.hpp>




namespace postcondition_detail {


    struct assertion
    {
        template< class Functor >
        explicit scoped_postcondition(Functor fun) :
            m_fun(fun)
        { }

        ~scoped_postcondition()
        {
            if (std::uncaught_exception())
                return;

            try {
                m_fun();
            }
            catch (...) {
                BOOST_ASSERT("postcondition is broken." && false);
            }
        }

    private:
        boost::function<bool()> m_fun
    };


} // namespace postcondition_detail



struct xxx :
    private pstade::nonassignable
{
    explicit xxx(int ) { }
};


namespace contract_detail {

    template< class T >
    struct result_box :
        boost::mpl::if_< boost::is_reference<T>,
            boost::optional<T>
            boost::optional< pstade::assignable<T> >
        >
    { };

}



#define PSTADE_POSTCONDITION(T, As) \
    std::auto_ptr< T > pstade_contract_detail_result_ptr;
pstade_contract_detail_postcondition_label: \
    if (pstade_contract_detail_result_ptr) { \
        T result = *pstade_contract_detail_result_ptr; \
        As; \
        return result; \
    } \
/**/


namespace postcondition_detail {


    template< class T >
    struct ref_to_ptr :
        boost::add_pointer<
            typename boost::remove_reference<T>::type
        >
    { };


    template< class T >
    struct result_ptr :
        boost::mpl::eval_if< boost::is_reference<T>,
            ref_to_ptr<T>,
            boost::mpl::identity< std::auto_ptr<T> >
        >
    { };


    template< class T > inline
    void reset(T *& ptr, T& src)
    {
        ptr = src;
    }


    template< class T > inline
    void reset(std::auto_ptr<T>& ptr, T const& src)
    {
        ptr.reset(new T(src));
    }


} // namespace postcondition_detail


#define PSTADE_POSTCONDITION(T) \
        pstade::postcondition_detail::result_ptr< T >::type pstade_contract_detail_result_ptr; \
    pstade_contract_detail_postcondition_label: \
        if (pstade_contract_detail_result_ptr) { \
            T result = *pstade_contract_detail_result_ptr; \
            PSTADE_POSTCONDITION_assert_and_return
/**/

    #define PSTADE_POSTCONDITION_assert_and_return(As)
            PSTADE_CONTRACT_expand(As) \
            return result; \
        } \
    /**/


#define PSTADE_POSTCONDITION(T, As) \
    pstade::postcondition_detail::result_ptr< T >::type pstade_contract_detail_result_ptr; \
pstade_contract_detail_postcondition_label: \
    if (pstade_contract_detail_result_ptr) { \
        T result = *pstade_contract_detail_result_ptr; \
        As; \
        return result; \
    } \
/**/

#define PSTADE_POSTCONDITION_D(T, As) \
    PSTADE_POSTCONDITION_impl(T, As, typename) \
/**/


#define PSTADE_POSTCONDITION_impl(T, As, Typename) \
    boost::optional< Typename pstade::contract_dtail::optional_param< T >::type > pstade_contract_detail_result; \
pstade_contract_detail_postcondition_label: \
    if (pstade_contract_detail_result) { \
        T result = **pstade_contract_detail_result; \
        As; \
        return result; \
    } \
/**/


#define PSTADE_RETURN(Result) \
    { \
        pstade_contract_detail_result_scoped_ptr.reset(new pstade_contract_detail_result_t(Result));
        goto pstade_contract_detail_postcondition_label; \
    } \
/**/



#define PSTADE_RETURN(Result) \
    { \
        pstade::contract_detail::reset(pstade_contract_detail_result_ptr, Result);
        goto pstade_contract_detail_postcondition_label; \
    } \
/**/


xxx ob(3);


xxx const& test()
{
    PSTADE_POSTCONDITION (xxx const&,
        (result == 3)
    )

    xxx i(112);
    for (;;)
        PSTADE_RETURN(i);

    PSTADE_RETURN(ob);
}


#include <pstade/contract.hpp>

int g_x;

int& bar()
{
    PSTADE_POSTCONDITION(int&)
    (
        (result == 4)
    )

    g_x = 4;
    PSTADE_RETURN(g_x);
}


int foo(int i)
{
    PSTADE_POSTCONDITION(int)
    (
        (i == 4)
        (result == 4)
    )

    if (i == 3) {
        ++i;
        PSTADE_RETURN(i);
    }
    else
        PSTADE_RETURN(4);
}

void hoge()
{
    PSTADE_POSTCONDITION_VOID
    (
        (g_x == 5)
    )

    ++g_x;
    PSTADE_RETURN_VOID;
}


int const g_cx(3);

int const& hogehoge()
{
    PSTADE_POSTCONDITION(int const&)
    (
        (g_cx == 3)
    )

    PSTADE_RETURN(g_cx);
}


void test()
{
    ::foo(3);
    ::bar();
    ::hoge();
    ::hogehoge();
}


int main()
{
    ::test();
    return 0;
}

#endif
