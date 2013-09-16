AOS Designer
============

Digital Story Editor

See Art Of Sequence: http//artofsequence.org

**AOS Designer (AOSD)** is an tool for artists to create digital stories. 

AOSD uses [AOSL](http://github.com/artofsequence/aosl/) format to define digital stories.
It also works with exporters which will generate other formats for different interpreters.

### Dependencies

Both **back-end and front-end** implementations are using:

 * [Boost](http://boost.org): to complete the standard C++ library;
 * [Google Test](https://code.google.com/p/googletest/): unit tests;
 * [TBB](https://code.google.com/p/googletest/): concurrency tools (when not available in Boost or the C++ standard);
 * [AOSLCPP](https://github.com/artofsequence/aosl-cpp): library to read, write, interpret and process AOSL data;
  * [XSD/Tree](http://www.codesynthesis.com/products/xsd/): 
 * [UtilCPP](https://github.com/artofsequence/utilcpp): some useful C++ tools;
 * [AOS Web Player](https://

The **default front-end** relies on Qt:

 * [Qt5](http://qt-project.org): used for GUI implementation;
 

### Development Setup

To develop this project, first you have to have installed:

 * [CMake](http://www.cmake.org/): We use CMake to define our projects and generate editor project files.
 * [Python]
 * [Boost](http://boost.org)
 * 

