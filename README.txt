OBJC XFCN

A SuperCard XFcn for calling an Objective-C method. Syntax is:

	objc( <frameworks>, <receiver>, <method label>[, <parameter1>[, <label2>, <parameter2> [, ...]] )

Where

frameworks	-	Is a return-delimited list of the frameworks to load. If the framework name contains a slash, it is assumed to be a valid path to the framework directory. Otherwise, for a line that reads "Cocoa", it will load "/System/Library/Frameworks/Cocoa.framework".

receiver	-	If this is a number, this is expected to be an object address returned by a previous call to this XFcn. If this is not a number, it is assumed to be the name of a class to which you want to send a message.

method label	-	If the method takes no parameters, this is the method name. Otherwise, this is the part of the method name up to the first colon.

parameter1 ... parameterN	-	Parameters will be converted according to whatever type the arguments of the given method are expected to have. Object pointers are returned and passed as simple numbers, just like other numbers. Characters are converted to UTF8 before passing them to Cocoa as a 'char'. Points are expected to be two floating point numbers separated by a comma (horizontal,vertical). Rectangles are four floating point numbers separated by commas, stored as horizontal,vertical,width,height. 