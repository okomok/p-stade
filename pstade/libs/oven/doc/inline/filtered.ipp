int src[]    = { 2,5,2,6,1,3,2 };
int answer[] = { 0,5,0,6,1,3,0 };

BOOST_FOREACH (int& i, src|filtered(lambda::_1 == 2)) {
    i = 0;
}

BOOST_CHECK( oven::equals(answer, src) );