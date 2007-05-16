using namespace pstade;

napkin::ostream os1(std::cout);
os1 << "constructor style\n";

napkin::ostream os2;
os2.reset(std::cout);
os2 << "reset style\n";

napkin::ostream os3 = os2;
os3 << "copy\n";

napkin::ostream os4;
os4.reset(os3);
os4 << "os3 is StringOutputable.\n";