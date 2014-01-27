
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


int	ExternalMain( XCmdPtr inParamBlock ) __asm("_main");


/*
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 *	Script Entry Point
 * ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
 */

int	ExternalMain( XCmdPtr inParamBlock )
{
	sParamBlock = [[SCParamBlock alloc] initWithXCmdBlock: inParamBlock];
	
	NSInvocation	*	theInvocation = nil;
	NSMethodSignature*	theSignature = nil;
		
	// Find class or object to call:
	NSString*	theObjectStr = [sParamBlock parameterAtIndex: 0];
	id			theObject = nil;
	
	if( [theObjectStr isEqualToString: @"!"] )
	{
		[sParamBlock setReturnValue: @"1.1, (c) 2014 by Uli Kusterer, all rights reserved."];
		return 0;
	}
	if( [theObjectStr isEqualToString: @"?"] )
	{
		[sParamBlock setReturnValue: @"put objc({\"NSClassName\"|address},\"methodName:\"[,param1[,\"part2OfMethodName:\",param2[,...]]])"];
		return 0;
	}
		
	if( [[theObjectStr stringByTrimmingCharactersInSet: [NSCharacterSet decimalDigitCharacterSet]] length] == 0 )	// Raw pointer.
	{
		theObject = (id) [theObjectStr integerValue];
		if( !theObject )	// Shortcut message sends to 0 to another 0.
		{
			[sParamBlock setReturnValue: @"0"];
			return 0;
		}
	}
	else
	{
		theObject = NSClassFromString( theObjectStr );
		if( !theObject )
		{
			[sParamBlock setReturnValue: [NSString stringWithFormat: @"Can't find class '%@'.", theObjectStr]];
			return 0;
		}
	}
	
	// No parameters? Call directly:
	NSString	*	methodName = [sParamBlock parameterAtIndex: 1];
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
		for( int x = 3; x < numParams; x += 2 )
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
		for( int y = 2; y < numParams; y += 2 )
		{
			NSString	*	theParam = [sParamBlock parameterAtIndex: y];
			int	x = (y +1) / 2;
			const char*	theType = [theSignature getArgumentTypeAtIndex: x];
			if( strcmp( theType, @encode(id) ) == 0 )
			{
				id	paramObj = (id) [theParam integerValue];
				[theInvocation setArgument: &paramObj atIndex: x];
			}
			else if( strcmp( theType, @encode(BOOL) ) == 0 )
			{
				int	paramInt = ([theParam caseInsensitiveCompare: @"true"] == NSOrderedSame) || ([theParam caseInsensitiveCompare: @"YES"] == NSOrderedSame);
				[theInvocation setArgument: &paramInt atIndex: x];
			}
			else if( strcmp( theType, @encode(int) ) == 0 )
			{
				int	paramInt = [theParam intValue];
				[theInvocation setArgument: &paramInt atIndex: x];
			}
			else if( strcmp( theType, @encode(long long) ) == 0 )
			{
				long long	paramLongLong = [theParam longLongValue];
				[theInvocation setArgument: &paramLongLong atIndex: x];
			}
			else if( strcmp( theType, @encode(unichar) ) == 0 )
			{
				unichar	paramUniChar = [theParam characterAtIndex:0];
				[theInvocation setArgument: &paramUniChar atIndex: x];
			}
			else if( strcmp( theType, @encode(char) ) == 0 )
			{
				char	paramChar = [theParam UTF8String][0];
				[theInvocation setArgument: &paramChar atIndex: x];
			}
			else if( strcmp( theType, @encode(NSPoint) ) == 0 )
			{
				NSArray*	parts = [theParam componentsSeparatedByString: @","];
				NSPoint	paramPoint = NSMakePoint([[parts objectAtIndex: 0] doubleValue], [[parts objectAtIndex: 1] doubleValue]);
				[theInvocation setArgument: &paramPoint atIndex: x];
			}
			else if( strcmp( theType, @encode(NSRect) ) == 0 )
			{
				NSArray*	parts = [theParam componentsSeparatedByString: @","];
				NSRect		paramRect = NSMakeRect([[parts objectAtIndex: 0] doubleValue], [[parts objectAtIndex: 1] doubleValue], [[parts objectAtIndex: 2] doubleValue], [[parts objectAtIndex: 3] doubleValue]);
				[theInvocation setArgument: &paramRect atIndex: x];
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

