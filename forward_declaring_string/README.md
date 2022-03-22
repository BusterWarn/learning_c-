# Forward Declaring String

A common issue I have run into is including the string library in header files without the ability to forward declare them. At least not without breaking [SEI CERT DCL58-CPP. Do not modify the standard namespaces](https://wiki.sei.cmu.edu/confluence/display/cplusplus/DCL58-CPP.+Do+not+modify+the+standard+namespaces).

In https://github.com/Philip-Trettner/cpp-std-fwd a solution for this was found. In this file I test the solution and it seems to work.

Next step is to test the solution from [Forward declaring std::string in C++](http://jonjagger.blogspot.com/2011/04/forward-declaring-stdstring-in-c.html).