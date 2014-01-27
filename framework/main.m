
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
	
	NSString*	firstParam = [sParamBlock parameterAtIndex: 0];
	if( [firstParam isEqualToString: @"!"] )
	{
		[sParamBlock setReturnValue: @"1.0, (c) 2014 by Uli Kusterer, all rights reserved."];
		return 0;
	}
	if( [firstParam isEqualToString: @"?"] )
	{
		[sParamBlock setReturnValue: @"put framework(\"Framework1\"[,\"Framework2\"[,...]])"];
		return 0;
	}
		
	NSMutableString*	errs = [NSMutableString string];
	
	// Load requested frameworks:
	for( int x = 0; x < [sParamBlock parameterCount]; x++ )
	{
		NSString*	theFramework = [sParamBlock parameterAtIndex: x];
		if( [theFramework rangeOfString: @"/"].location == NSNotFound )
		{
			theFramework = [NSString stringWithFormat: @"/System/Library/Frameworks/%1$@.framework", theFramework];
		}
		
		NSBundle	*	frameworkBundle = [NSBundle bundleWithPath: theFramework];
		if( !frameworkBundle )
		{
			[errs appendFormat: @"Couldn't find \"%@\".\r", theFramework];
			continue;
		}
		if( [frameworkBundle isLoaded] )
		{
			[errs appendFormat: @"\"%@\" already loaded.\r", theFramework];
			continue;
		}
		if( ![frameworkBundle load] )
		{
			[errs appendFormat: @"Couldn't load \"%@\".\r", theFramework];
			continue;
		}
	}
	
	[sParamBlock setReturnValue: errs];
	
	return 0;
}	

