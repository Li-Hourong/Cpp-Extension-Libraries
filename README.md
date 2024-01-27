# C++ Extension Libraries
/*
This is a bunch of libraries written in C++.
On the internet, so many people talk about the advantages and disadvantages of C++. And the most serious one is that C++ is getting more and more complicated. There're too many features that make C++ difficult to study and use. So I decided to not use some of the features of C++.
At the same time, many people talk about the lack of C++ open sourse libraries, so this is just a place to store my projects.
*/
/*
Jan 27, 2024
Today I updated the "Allocator.h". This is a simple packet of the malloc() and free() functions.
However, this header file can help with memory leaks and dangling pointers.
That does not means you can just allocate memory and don't release them.(In this case the performance of the allocator will drop rapidly.)
It is just an ensurance  that in case you forget to release or you can't release on time. And you should always remember to use the del() in the header file.
*/
