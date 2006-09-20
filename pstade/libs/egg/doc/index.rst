++++++++++++++++++++++++
The Egg Function Library
++++++++++++++++++++++++

.. include:: ../../doc/refs.rst

:Author: MB
:Contact: mb2act@yahoo.co.jp 
:License: Distributed under the `Boost Software License Version 1.0`_
:Version: 0.90.3



.. epigraph::

    "*I'm a little bird that has broken out of the egg.*"

    -- Peter Pan



.. contents:: **Table of Contents**
.. section-numbering::



Introduction
------------

Egg provides the simple way of making a `Functor`_ that supports `Boost.ResultOf`_ and works around
`the Forwarding Problem`__. All the types, functions and macros are defined in namespace ``pstade::egg``.

__ http://std.dkuug.dk/jtc1/sc22/wg21/docs/papers/2002/n1385.htm



Requirements
------------

- `Boost C++ Libraries Version 1.33.1`__ or later (no compilation required)
- `P-Stade C++ Libraries Version 1.00.8`__ or later (no compilation required, give a higher priority than Boost headers)

__ Boost_
__ http://sourceforge.net/project/showfiles.php?group_id=141222&package_id=173059



Tested Under
------------

- Microsoft Visual C++ 2005 Express Edition
- Microsoft Visual C++ .NET Version 7.1
- GCC 3.4.4



Quick Start
-----------

1. Define a type that is a model of `Baby Function`_::

	D:\p-stade.sourceforge.net\pstade\libs\egg\doc\inline\quick_start0.ipp


2. Make a functor by using ``PSTADE_EGG_FUNCTION``::

	D:\p-stade.sourceforge.net\pstade\libs\egg\doc\inline\quick_start1.ipp


3. Use as a normal function which supports `Boost.ResultOf`_::

	D:\p-stade.sourceforge.net\pstade\libs\egg\doc\inline\quick_start2.ipp

Note that ``X`` is deduced as ``int const`` and ``Y`` as ``int``.



Basic Concepts
--------------

Specification
^^^^^^^^^^^^^
- ``BabyFunction``: a model of `Baby Function`_
- ``baby``: an object of `Baby Function`_


Baby Function
^^^^^^^^^^^^^

A ``BabyFunction`` is any type that is copy-constructible and the following expression must be valid.

- Case of no arguments; ``BabyFunction::nullary_result_type`` and ``baby.call<R>();``, where ``R`` is the same as ``BabyFunction::nullary_result_type``
- Case of ``N >= 1`` arguments; ``BabyFunction::result<unspecified,A1,A2,...,AN>::type``  and ``baby.call<R>(a1,a2,...aN);``, where ``R`` is the same as ``BabyFunction::result<unspecified,A1,A2,...,AN>::type``
- Semantics: The nested ``nullary_result_type`` and ``result`` return the result type of the functor.

Note that the result type of nullary functors is always specified by using nested ``nullary_result_type`` typedef instead of nested ``result`` templates.



Reference
---------

``function``
^^^^^^^^^^^^
- Header: ``<pstade/egg/function.hpp>``
- Valid expression: ``function<BabyFunction> fun(baby);`` or ``function<BabyFunction> fun;``
- Precondition: The type of ``baby`` is ``BabyFunction``. ``BabyFunction`` must be `Default Constructible`_ for the latter valid expression.
- Returns: A `Functor`_ that supports `Boost.ResultOf`_.


``by_value``
^^^^^^^^^^^^
- Header: ``<pstade/egg/by_value.hpp>``
- Valid expression: ``by_value<T>``
- Returns: ``boost::remove_cv<typename boost::decay<T>::type>``


``PSTADE_EGG_FUNCTION``
^^^^^^^^^^^^^^^^^^^^^^^
There are some pitfalls when you define a `function`_ under namespace scope.
So you should prefer this macro.

- Header: ``<pstade/egg/function.hpp>``
- Valid expression: ``PSTADE_EGG_FUNCTION(Name, BabyFunction)``
- Precondition: placed under namespace scope and ``BabyFunction`` is `Default Constructible`_.
- Effects: ``typedef function<BabyFunction> Name##_fun; function<BabyFunction> const Name;``


``PSTADE_EGG_PIPABLE``
^^^^^^^^^^^^^^^^^^^^^^
- Header: ``<pstade/egg/pipable.hpp>``
- Valid expression: ``PSTADE_EGG_PIPBLE(Name, BabyFunction)``
- Precondition: same as ``PSTADE_EGG_FUNCTION``'s
- Effects: Makes ``in|Name(a0,a1,...aN)`` call ``function<BabyFunction>()(in,a0,a1,...aN)``.


``PSTADE_EGG_MAX_ARITY``
^^^^^^^^^^^^^^^^^^^^^^^^
The default maximum arity of functors Egg makes is five. If you want more arity, define ``PSTADE_EGG_MAX_ARITY`` before
any Egg headers. Note that compilers require an exponentially increasing amount of time
as the number increases.



Acknowledgments
---------------
- `P-Stade`_
- `Boost C++ Libraries`_



Release Notes
-------------

Version 0.90.0
^^^^^^^^^^^^^^
- Released initial version.

Version 0.90.1
^^^^^^^^^^^^^^
- Added ``PSTADE_EGG_PIPABLE``.

Version 0.90.2
^^^^^^^^^^^^^^
- Now `Baby Function`_ can have members.

Version 0.90.3
^^^^^^^^^^^^^^
- Fixed a bug that passes a ``egg::function`` object to ``BabyFunction``\'s constructor.
- Renamed ``decay_function`` to ``by_value``.

