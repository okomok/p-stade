struct S :
    or_<
        seq< chseq<'('>, S, chseq<')'> , S >,
        eps
    >
{ };
