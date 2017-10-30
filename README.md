# os-malloc
This directory contains:

myAllocator.c: a first-fit allocator
myAllocator.h: its header file

myAllocatorTest1.c: a test program for my allocator 

malloc.c: a replacement for malloc that uses my allocator
test1.c: a test program that uses this replacement malloc

There are two different testers as some implementations of printf
call malloc to allocate buffer space. This causes test1 to behave
improperly as it uses myAllocator as a malloc replacement. In this
case myAllocatorTest1 will function correctly. The only difference
between the programs is that test1 uses myAllocator as a malloc
replacement and myAllocatorTest1 uses myAllocator directly.

Makefile: a fairly portable "makefile", targets "all" and "clean"

To compile: 
 $ make 
To clean:
 $ make clean

The cygwin runtime uses malloc() and brk() extensively.  It is
interesting to compare the output of test1 & myAllocatorTest1.  All
those extra allocated regions are being used by cygwin's libraries!

# Lab Mods

In accordance to the lab we were requested to do, I modified the
resizeRegion method in myAllocator in order to make it so that if the
next block was free, and contained enough memory to complete the
request in conjunction with the curent size the block are resized.

This is all done in myAllocator.c
Also changed myAllocatorTest1.c in order to test the proper workings of
the methods.
This is seen as  the first block is reallocated to be 512 instead of 256
and the 2nd block loses exactly 256.