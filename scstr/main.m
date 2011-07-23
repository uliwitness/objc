
/*
 * �����������������������������������������������������������������������������
 *  main.c
 *  scstr XFcn
 *
 *  Created by Uli Kusterer on 2011-07-22.
 *  Copyright Uli Kusterer 2011. All rights reserved.
 * �����������������������������������������������������������������������������
 */


/*
 * �����������������������������������������������������������������������������
 *	Includes
 * �����������������������������������������������������������������������������
 */

#import "SCParamBlock.h"


SCParamBlock*		sParamBlock = NULL;


int	ExternalMain( XCmdPtr inParamBlock ) __asm("_main");


/*
 * �����������������������������������������������������������������������������
 *	Script Entry Point
 * �����������������������������������������������������������������������������
 */

int	ExternalMain( XCmdPtr inParamBlock )
{
	sParamBlock = [[SCParamBlock alloc] initWithXCmdBlock: inParamBlock];
	
	NSString*	theString = [sParamBlock parameterAtIndex: 0];
	NSString*	actualString = (NSString*) [theString integerValue];
	
	[sParamBlock setReturnValue: actualString];
	
	[sParamBlock release];
	
	return 0;
}	

