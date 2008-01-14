
#include <pstade/minimal_test.hpp>
#include <boost/optional/optional.hpp>


struct klass
{
    klass(int &i) : m_i(i) {}
    int &m_i;
};

struct klass_c
{
    klass_c(int &i) : m_i(i) {}
    int const &m_i;
};

struct klass_cc
{
    klass_cc(int const &i) : m_i(i) {}
    int const &m_i;
};


template<class Klass, class Int>
bool fun_copy_test(Klass k, Int &i)
{
    return &i == &k.m_i;
}

template<class Optional, class Int>
bool fun_copy_optional_test(Optional o, Int &i)
{
    return &i == &*o;
}


void test()
{
    {// from mutable int

        int i = 0;

        // direct-initialization (works fine.)
        {
            klass k(i);
            BOOST_CHECK(&i == &k.m_i);
            klass const ck(i);
            BOOST_CHECK(&i == &ck.m_i);
        }
        {
            klass_c k(i);
            BOOST_CHECK(&i == &k.m_i);
            klass_c const ck(i);            
            BOOST_CHECK(&i == &ck.m_i);
        }
        {
            klass_cc k(i);
            BOOST_CHECK(&i == &k.m_i);
            klass_cc const ck(i);
            BOOST_CHECK(&i == &ck.m_i);
        }

        // copy-initialization (works fine.)
        {
            klass k = i;
            BOOST_CHECK(&i == &k.m_i);
            BOOST_CHECK(fun_copy_test<klass>(i, i));
            klass const ck = i;
            BOOST_CHECK(&i == &ck.m_i);
            BOOST_CHECK(fun_copy_test<klass const>(i, i));
        }
        {
            klass_c k = i;
            BOOST_CHECK(&i == &k.m_i);
            BOOST_CHECK(fun_copy_test<klass_c>(i, i));
            klass_c const ck = i;
            BOOST_CHECK(&i == &ck.m_i);
            BOOST_CHECK(fun_copy_test<klass_c const>(i, i));
        }
        {
            klass_cc k = i;
            BOOST_CHECK(&i == &k.m_i);
            BOOST_CHECK(fun_copy_test<klass_cc>(i, i));
            klass_cc const ck = i;
            BOOST_CHECK(&i == &ck.m_i);
            BOOST_CHECK(fun_copy_test<klass_cc const>(i, i));
        }
    }


    {// from const int

        int const ci = 0;

        // direct-initialization (works fine.)
        {
            klass_cc k(ci);
            BOOST_CHECK(&ci == &k.m_i);
            klass_cc const ck(ci);
            BOOST_CHECK(&ci == &ck.m_i);
        }

        // copy-initialization
        {
            klass_cc k = ci;
            BOOST_CHECK(&ci == &k.m_i); // fails.
            BOOST_CHECK(fun_copy_test<klass_cc>(ci, ci));
            klass_cc const ck = ci;
            BOOST_CHECK(&ci == &ck.m_i); // fails.
            BOOST_CHECK(fun_copy_test<klass_cc const>(ci, ci));
        }
    }

    {
        int const ci = 0;
        boost::optional<int const &> o = ci;

        BOOST_CHECK(&ci == &*o); // fails.
        BOOST_CHECK(fun_copy_optional_test< boost::optional<int const &> >(ci, ci));
    }
}


void pstade_minimal_test()
{
    ::test();
}
