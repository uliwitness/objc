OBJC XFCN

A SuperCard XFcn for calling an Objective-C method. Syntax is:

	objc( <receiver>, <method label>[, <parameter1>[, <label2>, <parameter2> [, ...]] )

Where

frameworks	-	Is a return-delimited list of the frameworks to load. If the framework name contains a slash, it is assumed to be a valid path to the framework directory. Otherwise, for a line that reads "Cocoa", it will load "/System/Library/Frameworks/Cocoa.framework".

receiver	-	If this is a number, this is expected to be an object address returned by a previous call to this XFcn. If this is not a number, it is assumed to be the name of a class to which you want to send a message.

method label	-	If the method takes no parameters, this is the method name. Otherwise, this is the part of the method name up to the first colon.

parameter1 ... parameterN	-	Parameters will be converted according to whatever type the arguments of the given method are expected to have. Object pointers are returned and passed as simple numbers, just like other numbers. Characters are converted to UTF8 before passing them to Cocoa as a 'char'. Points are expected to be two floating point numbers separated by a comma (horizontal,vertical). Rectangles are four floating point numbers separated by commas, stored as horizontal,vertical,width,height. 

Because you can't be sure what frameworks have already been loaded, there is a
'framework' XCMD that you can use to load the needed frameworks before you use objc.


IMPORTANT:

To build this, you need to check out UliKit into the directory next to objc.


EXAMPLES:

	theAB = [ABAddressBook sharedAddressBook];

turns into

	framework "Foundation","AppKit","AddressBook"
	put objc( "ABAddressBook", "sharedAddressBook" ) into theAB

Where "Foundation" and "AddressBook" are the names of the frameworks that contain the classes you want to use, "ABAddressBook" is the name of the class you're sending a message to, and "sharedAddressBook" is the name of the message to send. The address of the shared address book object will then be returned as a number in the variable "theAB".

	NSBezierPath* theBezierPath = [NSBezierPath bezierPathWithRoundedRect: NSMakeRect(10,10,100,100) xRadius: 8.0 yRadius: 8.0];

turns into

	put objc("NSBezierPath","bezierPathWithRoundedRect:","10,10,100,100","xRadius:",8,"yRadius:",8) into theBezierPath

Where "NSBezierPath" is again the name of the class to send the message to, "bezierPathWithRoundedRect:" is the first part of the message to send, followed by the first parameter, then "xRadius:" continues the message name, followed by that parameter, and so on. Again, theBezierPath contains a number, the address o the new bezier path this just created.

	[theBezierPath fill];

turns into

	get objc(theBezierPath,"fill")

Where the first parameter is this time not the name of a class, but actually the address of the object we created above.


WARNING:

You are writing raw Objective C code here. You will not get the garbage collector, you will have to do all your memory management yourself (the calls above all return auto-released objects, so there is actually no need to call get objc("",theBezierPath,"release") in this case. But you will have to retain and release, especially if you want to remember an object beyond the duration of the current script.


HELPER XFCNS:

objc() can detect NSPoint, NSRect, int, BOOL, long long, unichar, and objects (NSObject*, id etc.) automatically, but for strings, you will have to use the objcstr() XFcn, where

	@"foobar"

turns into

	objcstr("foobar")

which will create an autoreleased NSString object. To get at the actual string inside an NSString*, use the scstr() XFcn. So essentially scstr(objcstr("foobar")) will be equivalent to just writing "foobar", because scstr() is the reverse of objcstr().


