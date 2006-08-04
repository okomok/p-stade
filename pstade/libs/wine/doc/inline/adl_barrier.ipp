namespace xxx {

    PSTADE_ADL_BARRIER(aaa) {

        struct aaa { };

    }

    void begin(aaa)
    {
        BOOST_CHECK(false);
    }

}

void begin(xxx::aaa) { }

void test()
{
    xxx::aaa a;
    begin(a);
}
