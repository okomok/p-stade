+++++++++++++++++++++++++++++++
The Ketchup Message Map Library
+++++++++++++++++++++++++++++++

.. include:: ../../doc/refs.rst

:Author: MB
:Contact: mb2act@yahoo.co.jp
:License: Distributed under the `Boost Software License Version 1.0`_
:Version: 1.01.4



.. image:: ./doc/logo.png
   :alt: Ketchup



.. epigraph::

	"*So, he turns around and squishes Baby Tomato and says, 'Catch up. Ketchup.'*"
	
	-- Mia Wallace



.. _Entries: Entry_


.. contents:: **Table of Contents**
.. section-numbering::



Motivation
----------
Four yeas ago, I made a program.
Everything WTL_ originally had other than win32 thin wrappers was almost useless.
``CUpdateUI`` was the one of them, so I made a replacement by using macros.
Later, I read the book, `C++ Template Metaprogramming`_
where I was inspired by a sample code, the finite state machine.
It could let me remove ``BEGIN_MSG_MAP`` macros and then the result was named Ketchup.

In time, the experience of making Biscuit__ gave me the way of avoiding compile-time crashes.
Now that Ketchup is the type-safe synonym of ``BEGIN_MSG_MAP``
to help WTL_ catch up the modern programming.

__ ../biscuit/index.html


Introduction
------------
Ketchup is a message map generator framework implemented using class templates.
The templates allow us to write type-safe ``BEGIN_MSG_MAP``.

A simple ``BEGIN_MSG_MAP`` macro snippet::

	D:\Importance\Document\p-stade.sourceforge.net\pstade\libs\ketchup\doc\inline\introduction_0.ipp

is approximated using Ketchup's facilities as seen in this code snippet::

	D:\Importance\Document\p-stade.sourceforge.net\pstade\libs\ketchup\doc\inline\introduction_1.ipp



Requirements
------------
- `WTL Version 7.5`__
- `Boost C++ Libraries Version 1.33.1`__ or later (no compilation required)
- `P-Stade C++ Libraries Version 0.98.x`__ or later (no compilation required, give a higher priority than Boost headers)

__ WTL_
__ Boost_
__ http://sourceforge.net/project/showfiles.php?group_id=141222&package_id=173059



Tested Under
------------
- Microsoft Visual C++ 2005 Express Edition
- Microsoft Visual C++ .NET Version 7.1



Quick Start
-----------
1. Include Ketchup headers and make ``CMainFrame`` a model of Derived_::

	D:\Importance\Document\p-stade.sourceforge.net\pstade\libs\ketchup\doc\inline\quick_start_0.ipp

2. Define message handlers::

	D:\Importance\Document\p-stade.sourceforge.net\pstade\libs\ketchup\doc\inline\quick_start_1.ipp

3. Make ``CMainFrame`` a model of `Message Processor`_ [#]_::

	D:\Importance\Document\p-stade.sourceforge.net\pstade\libs\ketchup\doc\inline\quick_start_2.ipp

Note that declarations of message handlers must be placed before the Entry_.


.. [#] `Standard C++`_ doesn't allow you to abbreviate the syntax of member function pointers.
       (See: 5.3.1 Unary operators -3- of `Standard C++ Draft`_)



Basic Concepts
--------------


Message Map Container
^^^^^^^^^^^^^^^^^^^^^
A ``MessageMapContainer`` [#]_ is any type that has the member function, whether virtual or not::

	D:\Importance\Document\p-stade.sourceforge.net\pstade\libs\ketchup\doc\inline\basic_concepts_message_map_container.ipp

The return value is ``TRUE`` if the message is fully handled; otherwise, it is ``FALSE``.


Chain Class
^^^^^^^^^^^
A ``ChainClass`` [#]_ is any base class that is a model of `Message Map Container`_.


Derived
^^^^^^^
A ``Derived`` is any type that is derived from ketchup::message_processor<Derived_, `Chain Class`_\0, `Chain Class`_\1, ... >


Entry
^^^^^
An ``Entry`` is any type that has the static member function::

	D:\Importance\Document\p-stade.sourceforge.net\pstade\libs\ketchup\doc\inline\basic_concepts_entry.ipp


Entry Wrapper
^^^^^^^^^^^^^
An ``EntryWrapper`` is a class template that provides a interface for creating an Entry_.


Message Processor
^^^^^^^^^^^^^^^^^
A ``MessageProcessor`` is any type that has the accessible member variable of Entry_ named ``end_msg_map``.


id
^^
An ``id`` is any static constant of window message id or command id.


func
^^^^
A ``func`` is any member function of Derived_.


Value Functor Class
^^^^^^^^^^^^^^^^^^^
A ``ValueFunctorClass`` is any `Default Constructible`_ `Functor`_ type that has the member function::

	D:\Importance\Document\p-stade.sourceforge.net\pstade\libs\ketchup\doc\inline\basic_concepts_value_functor_class.ipp

This is for crossing the compile-time/runtime boundary.


.. [#] This concept comes from ATL. A type that has ``BEGIN_MSG_MAP`` conforms to it.

.. [#] This concept and name come from ATL. 



ketchup::process_window_message
-------------------------------
Ketchup defines the only one function::

	D:\Importance\Document\p-stade.sourceforge.net\pstade\libs\ketchup\doc\inline\process_window_message.ipp

The return value is ``TRUE`` if the message is fully handled by the `Message Processor`_; otherwise, it is ``FALSE``.



ketchup::message_processor
--------------------------
``ketchup::message_processor`` is the base class template that provides predefined `Entry Wrapper`_\s.
If a `Chain Class`_ is not `Default Constructible`_, you cannot pass it to ``ketchup::message_processor``
for the constructor call. Then, your Derived_ class can't conform to `Message Map Container`_ because of the name ambiguity.
So you must explicitly add the member function::

	D:\Importance\Document\p-stade.sourceforge.net\pstade\libs\ketchup\doc\inline\message_processor.ipp


Predefined Entry Wrappers
-------------------------
All the predefined `Entry Wrapper`_\s are in the scope of ketchup::message_processor<Derived_>, which 
defines a nested ``_`` type that refers to the Derived_.


message_handler
^^^^^^^^^^^^^^^
``message_handler`` creates an Entry_ from id_ and func_::

	D:\Importance\Document\p-stade.sourceforge.net\pstade\libs\ketchup\doc\inline\entry_wrappers_message_handler.ipp


begin_msg_map
^^^^^^^^^^^^^
``begin_msg_map`` creates a sequential Entry_ from multiple Entries_.
The maximum number of Entries_ is thirty.
If the number of your Entries_ comes greater than thirty,
you can chain the Entries_. Keep in mind that
the type created by begin_msg_map_ is also an Entry_::

	D:\Importance\Document\p-stade.sourceforge.net\pstade\libs\ketchup\doc\inline\entry_wrappers_begin_msg_map_0.ipp

Or you can extract the maximum power from `Boost.Preprocessor`_ in exchange for giving credit to VC++7.1 preprocessor::

	D:\Importance\Document\p-stade.sourceforge.net\pstade\libs\ketchup\doc\inline\entry_wrappers_begin_msg_map_1.ipp

The available number of template parameters depends on `/Zm`__ option, aside from compiler limitations on the number of template parameters.

__ http://msdn.microsoft.com/library/default.asp?url=/library/en-us/vccore/html/_core_.2f.zm.asp


alt_msg_map
^^^^^^^^^^^
``alt_msg_map`` creates an indexed Entry_, which is a replacement for ``ALT_MSG_MAP`` of ATL::

	D:\Importance\Document\p-stade.sourceforge.net\pstade\libs\ketchup\doc\inline\entry_wrappers_alt_msg_map.ipp

As a default Entry_ is not indexed, 0 indexed Entry is always required if `Message Map Container`_ must
have multiple message map ids.


chain_msg_map
^^^^^^^^^^^^^
``chain_msg_map`` creates an Entry_ from a `Chain Class`_.


chain_msg_map_member
^^^^^^^^^^^^^^^^^^^^
``chain_msg_map_member`` creates an Entry_ from a `Value Functor Class`_::

	D:\Importance\Document\p-stade.sourceforge.net\pstade\libs\ketchup\doc\inline\entry_wrappers_chain_msg_map_member.ipp

As an `Entry wrapper`_ is a class template and an object cannot be passed directly,
you must write a `Value Functor Class`_ for every chained member object.


and...
^^^^^^
Every synonym of ``BEGIN_MSG_MAP`` macro are fully defined.



Cracked Handlers
----------------
Ketchup supports cracked handlers of WTL_::

	D:\Importance\Document\p-stade.sourceforge.net\pstade\libs\ketchup\doc\inline\cracked_handlers.ipp

``SetMsgHandled`` of WTL_ was rejected for transparency [#]_ .
Instead you can refer using Entry_ by passing ``not_handled`` as the last argument.
To determine whether or not to handle the message at compile-time makes your program a little smaller and faster.
If you want to decide it at runtime, you must use message_handler_.


.. [#] Cracked handlers might have had an extra argument ``bHandled`` as normal handlers do.
       I recall normal handlers in ``BEGIN_MSG_MAP_EX`` made some troubles.



MFC Update Command UI
---------------------
Ketchup supports Updating Command UI mechanism of MFC and the limited automatic-disabling::

	D:\Importance\Document\p-stade.sourceforge.net\pstade\libs\ketchup\doc\inline\mfc_update_command_ui.ipp

This is a replacement for ``CUpdateUI`` of WTL_. 
``update_menu_cmd_ui`` generates a ``ketchup::cmd_ui`` object from ``WM_INITMENUPOPUP``.
``enable_cmd_ui_if_handled`` enables a ``ketchup::cmd_ui`` object if it is handled; otherwise, disables it.



Compatibility
-------------
Ketchup is compatible with ``BEGIN_MSG_MAP``.
``PSTADE_KETCHUP_CHAIN_MSG`` makes it::

	D:\Importance\Document\p-stade.sourceforge.net\pstade\libs\ketchup\doc\inline\compatibility.ipp



Combatting Two-phase Name Lookup
--------------------------------
When your Derived_ class is a template, a conforming compiler
cannot find any Entry_ from `ketchup::message_processor`_
without user workaround::

	D:\Importance\Document\p-stade.sourceforge.net\pstade\libs\ketchup\doc\inline\combatting_two_phase_name_lookup.ipp

VC++ doesn't support two-phase name lookup, but you must add somewhat ugly prefix for `Standard C++`_ [#]_.


.. [#] It is surprising that almost all of WTL is illegal.
       Note that this workaround cannot work around weird GCC3.4.4.



Points of Interest
------------------
The last point is the performance. The program size seems not to be a problem. VC++7.1 generates
the same size program as ``BEGIN_MSG_MAP``, because Ketchup's message map is almost same as ``BEGIN_MSP_MAP``.
But VC++7.1 can't inline message handlers unlike ``BEGIN_MSG_MAP``.
Could this be a problem of the speed?

I did not intend to emulate the appearance of ``BEGIN_MSG_MAP``.
It is not just a syntax sugar but the coincidence as the result of naming consistency with ATL/WTL_.
It was an amazing discovery for me.

By the way, Ketchup might be the first application using `Boost.Xpressive`_,
which is used as the source code generator.



References
----------
- `Forum at Code Project`__
- `P-Stade`_
- `C++ Template Metaprogramming`_
- `Boost C++ Libraries`_
- `Boost.MPL`_
- `Boost.Preprocessor`_
- `Boost.Wave`_
- `Boost.Xpressive`_
- `Hassle Free Clip Art.com`_


__ http://www.codeproject.com/wtl/ketchup.asp



Release Notes
-------------

Version 1.01.0
^^^^^^^^^^^^^^
- Namespace moved to ``pstade::ketchup``.
- Removed requirements for overriding ``ProcessWindowMessage``.
- Added document of Two-phase name lookup workaround.
- Removed eVC4 support.

Version 1.01.1
^^^^^^^^^^^^^^
- Fixed a bug of toolbar ``cmd_ui``.

Version 1.01.2
^^^^^^^^^^^^^^
- Removed nullary ``begin_msg_map`` for `Standard C++`_.

Version 1.01.3
^^^^^^^^^^^^^^
- Changed `Cracked Handlers`_ templates parameter.

Version 1.01.4
^^^^^^^^^^^^^^
- Fixed the fatal overflow bug.


