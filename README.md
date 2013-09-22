AOS Designer
============

Digital Story Editor

This is a sub-project of Art Of Sequence: [http//artofsequence.org](http//artofsequence.org)

**AOS Designer (AOSD)** is an tool for artists to create digital stories. 

AOSD uses [AOSL](http://github.com/artofsequence/aosl/) format to define digital stories.
It also works with exporters which will generate other formats for different interpreters.

### Documentation

See the [./docs](./docs) directory for development setup, guidelines, etc.

### Dependencies

Both **back-end and front-end** implementations are using:

 * [Boost](http://boost.org): to complete the standard C++ library;
 * [Google Test](https://code.google.com/p/googletest/): unit tests;
 * [TBB](https://code.google.com/p/googletest/): concurrency tools (when not available in Boost or the C++ standard);
 * [AOSLCPP](./aosl-cpp): library to read, write, interpret and process AOSL data;
  * [XSD/Tree](http://www.codesynthesis.com/products/xsd/): 
 * [UtilCPP](./utilcpp): some useful C++ tools;
 

The **default front-end** relies on Qt:

 * [Qt5](http://qt-project.org): used for GUI implementation;
 
