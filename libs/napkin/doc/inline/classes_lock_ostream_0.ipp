napkin::lock_ostream los;

void simple_thread()
{
    los << "lock1\n";
}

void test()
{
    los.reset(std::cout);
    boost::thread thrd(&simple_thread);
    los << "lock2\n";
}
