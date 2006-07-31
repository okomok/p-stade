template< class Range >
void modify(Range& rng)
{
    *boost::begin(rng) = 'y'; // error!
}

void test()
{
    std::string str1("hello, constant_range!");
    ::modify(str1|constants);
}