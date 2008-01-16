
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/detail/lightweight_test.hpp>


int main()
{
    namespace bll = boost::lambda;
    {
        int *x = new int(0);

        *x = 1;
        BOOST_TEST(*x == 1);

        (*bll::_1)(x) = 2; // ok.
        BOOST_TEST(*x == 2);
    }
    {
        std::string s("0");
        std::string::iterator x = s.begin();

        *x = '1';
        BOOST_TEST(*x == '1');

        (*bll::_1)(x) = '2'; // ok.
        BOOST_TEST(*x == '2');
    }
    {
        std::string s("0");
        std::string::iterator const x = s.begin();

        *x = '1';
        BOOST_TEST(*x == '1');

        (*bll::_1)(x) = '2'; // doesn't compile.
        BOOST_TEST(*x == '2');
    }
    {
        boost::shared_ptr<int> const x(new int(0));

        *x = 1;
        BOOST_TEST(*x == 1);

        (*bll::_1)(x) = 2; // doens't compile.
        BOOST_TEST(*x == 2);
    }

    return boost::report_errors();
}
