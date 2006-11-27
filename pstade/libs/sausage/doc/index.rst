+++++++++++++++++++++++++++++++++++++++
The Sausage Coroutine Iteration Library
+++++++++++++++++++++++++++++++++++++++

.. include:: ../../doc/refs.rst

:Author: MB
:Contact: mb2act@yahoo.co.jp 
:License: Distributed under the `Boost Software License Version 1.0`_
:Version: 0.90.0



.. epigraph::

    "*Everything has an end, but the sausage has two.*"

    -- German idiom



.. contents:: **Table of Contents**
.. section-numbering::



Introduction
------------

Sausage emulates the coroutine iteration.
All the types, functions and objects are defined in ``namespace pstade::sausage``.



Requirements
------------

- `Boost C++ Libraries Version 1.33.1`__ or later (Boost.Thread compilation required)
- `P-Stade C++ Libraries Version 1.01.7`__ or later (no compilation required, give a higher priority than Boost headers)

__ Boost_
__ http://sourceforge.net/project/showfiles.php?group_id=141222&package_id=173059



Tested Under
------------

- Microsoft Visual C++ 2005 Express Edition
- Microsoft Visual C++ .NET Version 7.1
- GCC 3.4.4



Quick Start
-----------

1. Define a type that is a model of `Routine`_::

	E:\p-stade.sourceforge.net\pstade\libs\sausage\doc\inline\quick_start0.ipp


2. Iterate the range made by `yielded`_::

	E:\p-stade.sourceforge.net\pstade\libs\sausage\doc\inline\quick_start1.ipp


Note that ``operator()`` must be a function template.
The ``Yield`` object is magically passed by Sausage, and its type is unspecified.



Basic Concepts
--------------

``Routine``
^^^^^^^^^^^
``Routine`` is any type that the following expressions are valid.

- ``Routine::routine_result_type``
- ``rou(y)``, where ``rou`` is a ``Routine`` object, and ``y`` is a ``Yield`` object.

Note that ``Routine`` is also a model of unary FunctionObject,
which can be used without reference to Sausage.


``Yield``
^^^^^^^^^
``Yield`` is any type that the following expressions are valid.

- ``y(x)``, where ``y`` is a ``Yield`` object, and ``x`` is any object.



Reference
---------

``yielded``
^^^^^^^^^^^^
- Header: ``<pstade/sausage/yield_range.hpp>``
- Valid expression: ``rou|yielded``, where ``rou`` is a ``Routine`` object.
- Returns: A SinglePassRange whose ``reference`` is ``routine_result_type`` of ``rou``.



Acknowledgments
---------------
- `P-Stade`_
- `Hamigaki C++ Libraries`__
- `Boost C++ Libraries`_
- `Boost.Coroutine`__
- `Sausage - Wikipedia`__

__ http://sourceforge.jp/projects/hamigaki/
__ http://www.boost-consulting.com/vault/index.php?&directory=Concurrent%20Programming
__ http://en.wikipedia.org/wiki/Sausage



Release Notes
-------------

Version 0.90.0
^^^^^^^^^^^^^^
- Released initial version.


