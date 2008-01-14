struct factor : debugger<factor,
    or_<
        integer,
        seq< chseq<'('>, expression, chseq<')'> >,
        actor< seq< chseq<'-'>, factor >, do_negate >,
        seq< chseq<'+'>, factor >
    >
>
{ };
