
#include <pstade/minimal_test.hpp>


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


void test()
{
    {// from mutable int

        int i = 0;

        // direct-initialization
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

        // copy-initialization
        {
            klass k = i;
            BOOST_CHECK(&i == &k.m_i);
            klass const ck = i;
            BOOST_CHECK(&i == &ck.m_i);
        }
        {
            klass_c k = i;
            BOOST_CHECK(&i == &k.m_i);
            klass_c const ck = i;
            BOOST_CHECK(&i == &ck.m_i);
        }
        {
            klass_cc k = i;
            BOOST_CHECK(&i == &k.m_i);
            klass_cc const ck = i;
            BOOST_CHECK(&i == &ck.m_i);
        }
    }


    {// from const int

        int const ci = 0;

        // direct-initialization
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
            klass_cc const ck = ci;
            BOOST_CHECK(&ci == &ck.m_i); // fails.
        }
    }
}


void pstade_minimal_test()
{
    ::test();
}
