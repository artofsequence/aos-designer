AOS Designer
============

Digital Story Editor

See Art Of Sequence: http//artofsequence.org

**AOS Designer (AOSD)** is an tool for artists to create digital stories. 

AOSD uses AOSL to define digital stories, to allow any kind of sequence to be created.
It also works with exporters which will generate other formats for different interpreters.

If you want to develop for this project, [check the wiki for setup](https://github.com/artofsequence/aos-designer/wiki/).

### Dependencies

Both **back-end and front-end** implementations are using:

 * [Boost](http://boost.org): to complete the standard C++ library;
 * [AOSLCPP](https://github.com/artofsequence/aosl-cpp): library to read, write and interpret AOSL data;
 * [UtilCPP](https://github.com/artofsequence/utilcpp): some useful C++ tools;
 * [Google Test](https://code.google.com/p/googletest/): unit tests;
 

The **back-end** also relies on:

 * [Intel TBB](http://threadingbuildingblocks.org): concurrent containers and other concurrency tools;

The **default front-end** relies on Qt:

 * [Qt5](http://qt-project.org): used for GUI implementation;
 
