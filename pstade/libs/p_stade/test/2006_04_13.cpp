#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


#include <iostream>
#include <string>
#include <boost/test/utils/trivial_singleton.hpp>
#include <boost/pool/detail/singleton.hpp>

// <abc.hpp>
//
struct abc_t : // xxx_t‚Æ‚¢‚¤–¼‘O‚Å‚È‚¢‚Æ‚¢‚¯‚È‚¢
    boost::unit_test::singleton<abc_t>
{
public:
    void hello()
    {
        std::cout << "hello" << std::endl;
    }

    std::string str() const
    {
        return "hello";
    }

private:
    BOOST_TEST_SINGLETON_CONS(abc_t);
};

BOOST_TEST_SINGLETON_INST(abc)
//
// </abc.hpp>


// <X.cpp>
//
// #include <abc.hpp>
//
struct X
{
    X()
    {
        // abc.hello(); // ‚±‚ê‚Í‚Ü‚¸‚¢!
        m_hello = abc.str(); // OK
    };

    void hello()
    {
        std::cout << m_hello << std::endl;
    }

private:
    std::string m_hello;
};


X global_x;
//
// </X.cpp>


void foo()
{
    int i = boost::details::pool::singleton_default<int>::instance();
    (void)i;
};


void test()
{
    abc.hello();
    global_x.hello();

    // abc_t a; // error!
    
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
