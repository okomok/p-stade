#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

static unsigned int INDEX = 0;

class A {

public:
    A() : myIndex(boost::lexical_cast<std::string>(INDEX++)) {};

    std::string GetIndex() const { return myIndex; }

private:
    std::string myIndex;
};

int main()
{
    std::vector<A> aArray(10);
    std::vector<std::string> values;
    values.reserve(10);

    std::transform(aArray.begin(),aArray.end(), std::back_inserter(values),
                   boost::bind(&A::GetIndex, _1));

    std::copy(values.begin(), values.end(),
              std::ostream_iterator<std::string>(std::cout, ","));

    return 0;
}