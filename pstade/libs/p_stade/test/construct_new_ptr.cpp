
#include <boost/shared_ptr.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/construct.hpp>
#include <cassert>

int main()
{
    namespace bl = boost::lambda;
    
    int i = 12;
    boost::shared_ptr<int> sp =
        bl::bind(
            bl::constructor< boost::shared_ptr<int> >(),
            bl::bind(bl::new_ptr<int>(), bl::_1)
        ) (i);

    assert(*sp == 12);
}
