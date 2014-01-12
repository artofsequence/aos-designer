AOS Designer
============

Digital Story Editor

This is a sub-project of Art Of Sequence: [http//artofsequence.org][aos-website]

**AOS Designer (AOSD)** is an tool for artists to create digital stories. 

AOSD uses [AOSL][aosl-github] format to define digital stories.
It also works with exporters which will generate other formats for different interpreters.

### Documentation

See the [./docs][docs] directory for development setup, guidelines, etc.

### Dependencies

Both **back-end and front-end** implementations are using:

 * [Boost][boost-org]: to complete the standard C++ library;
 * [Google Test][gtest]: unit tests;
 * [TBB][tbb-site]: concurrency tools (when not available in Boost or the C++ standard);
 * [AOSLCPP][aoslcpp-dir]: library to read, write, interpret and process AOSL data;
  * [XSD/Tree][xsd-site]: used to generate C++ types and parsing algorithms from the xsd AOSL definition file
 * [UtilCPP][utilcpp-dir]: some useful C++ tools;
 

The **default front-end** relies on Qt:

 * [Qt5](http://qt-project.org): used for GUI implementation;
 
[aos-website]: http://artofsequence.org
[docs]: ./docs/
[aosl-github]: http://github.com/artofsequence/aosl/
[boost-org]: http://boost.org
[gtest]: https://code.google.com/p/googletest/
[aoslcpp-dir]: ./aosl-cpp
[utilcpp-dir]: ./utilcpp
[tbb-site]: http://threadingbuildingblocks.org
[xsd-site]: http://www.codesynthesis.com/products/xsd/

