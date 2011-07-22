
/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *  main.c
 *  objc XFcn
 *
 *  Created by Uli Kusterer on 2011-07-22.
 *  Copyright Uli Kusterer 2011. All rights reserved.
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	Includes
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

#import "SCParamBlock.h"


SCParamBlock*		sParamBlock = NULL;


int	main( XCmdPtr inParamBlock );


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	Script Entry Point
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

int	main( XCmdPtr inParamBlock )
{
	sParamBlock = [[SCParamBlock alloc] initWithXCmdBlock: inParamBlock];
	
	NSInvocation	*	theInvocation = nil;
	NSMethodSignature*	theSignature = nil;
	
	// Load requested frameworks:
	NSString*	theFrameworks = [sParamBlock parameterAtIndex: 0];
	NSArray*	frameworksArray = [theFrameworks componentsSeparatedByString: @"\r"];
	for( NSString* theFramework in frameworksArray )
	{
		if( [theFramework rangeOfString: @"/"].location == NSNotFound )
		{
			theFramework = [NSString stringWithFormat: @"/System/Library/Frameworks/%1$@.framework", theFramework];
		}
		
		NSBundle	*	frameworkBundle = [NSBundle bundleWithPath: theFramework];
		if( frameworkBundle && ![frameworkBundle isLoaded] )
			[frameworkBundle load];
	}
	
	// Find class or object to call:
	NSString*	theObjectStr = [sParamBlock parameterAtIndex: 1];
	id			theObject = nil;
	
	if( [[theObjectStr stringByTrimmingCharactersInSet: [NSCharacterSet decimalDigitCharacterSet]] length] == 0 )	// Raw pointer.
		theObject = (id) [theObjectStr integerValue];
	else
		theObject = NSClassFromString( theObjectStr );
	
	// No parameters? Call directly:
	NSString	*	methodName = [sParamBlock parameterAtIndex: 2];
	if( [methodName characterAtIndex: [methodName length] -1] != ':' )
	{
		SEL theSelector = NSSelectorFromString(methodName);
		theSignature = [theObject methodSignatureForSelector: theSelector];
		theInvocation = [NSInvocation invocationWithMethodSignature: theSignature];
		[theInvocation setTarget: theObject];
		[theInvocation setSelector: theSelector];
	}
	else	// Parameters? Build selector name and add parameters:
	{
		// Every second  parameter is a label:
		NSMutableString*	selectorString = [[methodName mutableCopy] autorelease];
		NSInteger			numParams = [sParamBlock parameterCount];
		for( int x = 4; x < numParams; x += 2 )
		{
			[selectorString appendString: [sParamBlock parameterAtIndex: x]];
		}
		
		// Build invocation:
		SEL theSelector = NSSelectorFromString(selectorString);
		theSignature = [theObject methodSignatureForSelector: theSelector];
		theInvocation = [NSInvocation invocationWithMethodSignature: theSignature];
		[theInvocation setTarget: theObject];
		[theInvocation setSelector: theSelector];
		
		// Add parameters to invocation, which are the params following the selector bits:
		for( int x = 3; x < numParams; x += 2 )
		{
			NSString	*	theParam = [sParamBlock parameterAtIndex: x +2];	//
			const char*	theType = [theSignature getArgumentTypeAtIndex: x];
			if( strcmp( theType, @encode(id) ) == 0 )
			{
				id	paramObj = (id) [theParam integerValue];
				[theInvocation setArgument: &paramObj atIndex: x +2];
			}
			else if( strcmp( theType, @encode(BOOL) ) == 0 )
			{
				int	paramInt = ([theParam caseInsensitiveCompare: @"true"] == NSOrderedSame) || ([theParam caseInsensitiveCompare: @"YES"] == NSOrderedSame);
				[theInvocation setArgument: &paramInt atIndex: x +2];
			}
			else if( strcmp( theType, @encode(int) ) == 0 )
			{
				int	paramInt = [theParam intValue];
				[theInvocation setArgument: &paramInt atIndex: x +2];
			}
			else if( strcmp( theType, @encode(long long) ) == 0 )
			{
				long long	paramLongLong = [theParam longLongValue];
				[theInvocation setArgument: &paramLongLong atIndex: x +2];
			}
			else if( strcmp( theType, @encode(unichar) ) == 0 )
			{
				unichar	paramUniChar = [theParam characterAtIndex:0];
				[theInvocation setArgument: &paramUniChar atIndex: x +2];
			}
			else if( strcmp( theType, @encode(char) ) == 0 )
			{
				char	paramChar = [theParam UTF8String][0];
				[theInvocation setArgument: &paramChar atIndex: x +2];
			}
			else if( strcmp( theType, @encode(NSPoint) ) == 0 )
			{
				NSArray*	parts = [theParam componentsSeparatedByString: @","];
				NSPoint	paramPoint = NSMakePoint([[parts objectAtIndex: 0] doubleValue], [[parts objectAtIndex: 1] doubleValue]);
				[theInvocation setArgument: &paramPoint atIndex: x +2];
			}
			else if( strcmp( theType, @encode(NSRect) ) == 0 )
			{
				NSArray*	parts = [theParam componentsSeparatedByString: @","];
				NSRect		paramRect = NSMakeRect([[parts objectAtIndex: 0] doubleValue], [[parts objectAtIndex: 1] doubleValue], [[parts objectAtIndex: 2] doubleValue], [[parts objectAtIndex: 3] doubleValue]);
				[theInvocation setArgument: &paramRect atIndex: x +2];
			}
		}
	}
	
	// Now set up a place for the return value, call the method and return the value to SC:
	const char*	returnType = [theSignature methodReturnType];
	if( strcmp( returnType, @encode(id) ) == 0 )
	{
		id	paramObj = nil;
		[theInvocation invoke];
		[theInvocation getReturnValue: &paramObj];
		
		[sParamBlock setReturnValue: [NSString stringWithFormat: @"%lld", (long long)paramObj]];
	}
	else if( strcmp( returnType, @encode(BOOL) ) == 0 )
	{
		BOOL	paramBool = NO;
		[theInvocation invoke];
		[theInvocation getReturnValue: &paramBool];
		
		[sParamBlock setReturnValue: (paramBool ? @"true" : @"false")];
	}
	else if( strcmp( returnType, @encode(int) ) == 0 )
	{
		int		paramInt = -1;
		[theInvocation invoke];
		[theInvocation getReturnValue: &paramInt];
		
		[sParamBlock setReturnValue: [NSString stringWithFormat: @"%d", paramInt]];
	}
	else if( strcmp( returnType, @encode(long long) ) == 0 )
	{
		long long paramLongLong = -1;
		[theInvocation invoke];
		[theInvocation getReturnValue: &paramLongLong];
		
		[sParamBlock setReturnValue: [NSString stringWithFormat: @"%lld", paramLongLong]];
	}
	else if( strcmp( returnType, @encode(unichar) ) == 0 )
	{
		unichar		paramUniChar = 0;
		[theInvocation invoke];
		[theInvocation getReturnValue: &paramUniChar];
		
		[sParamBlock setReturnValue: [[[NSString alloc] initWithCharacters: &paramUniChar length: 1] autorelease]];
	}
	else if( strcmp( returnType, @encode(char) ) == 0 )
	{
		char		paramChar = 0;
		[theInvocation invoke];
		[theInvocation getReturnValue: &paramChar];
		
		[sParamBlock setReturnValue: [[[NSString alloc] initWithBytes: &paramChar length: 1 encoding: NSUTF8StringEncoding] autorelease]];
	}
	else if( strcmp( returnType, @encode(NSPoint) ) == 0 )
	{
		NSPoint		paramPoint = { 0, 0 };
		[theInvocation invoke];
		[theInvocation getReturnValue: &paramPoint];
		
		[sParamBlock setReturnValue: [NSString stringWithFormat:@"%f,%f", paramPoint.x, paramPoint.y]];
	}
	else if( strcmp( returnType, @encode(NSRect) ) == 0 )
	{
		NSRect		paramRect = { { 0, 0 }, { 0, 0 } };
		[theInvocation invoke];
		[theInvocation getReturnValue: &paramRect];
		
		[sParamBlock setReturnValue: [NSString stringWithFormat:@"%f,%f,%f,%f", paramRect.origin.x, paramRect.origin.y, paramRect.size.width, paramRect.size.height]];
	}
	
	[sParamBlock release];
	
	return 0;
}	

