#if 0
#include <pstade/../libs/oven/test/function_output_iterator.cpp>
#else

#include <pstade/vodka/drink.hpp>

#include <iostream>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>

#include <pstade/oven/generate_range.hpp>
#include <pstade/oven/counting_range.hpp> // int_range


typedef boost::minstd_rand base_generator_type;

void experiment(base_generator_type& generator)
{
    using namespace pstade;
    using namespace oven;

    typedef boost::uniform_int<> distribution_type;
    typedef boost::variate_generator<base_generator_type&, distribution_type> gen_type;
    gen_type die_gen(generator, distribution_type(1, 6));

    BOOST_FOREACH (int i, int_range(0, 10)|generated(boost::ref(die_gen))) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}


int main()
{
    base_generator_type generator(42u);
    ::experiment(generator);
    ::experiment(generator);

    return 0;
}


#endif
