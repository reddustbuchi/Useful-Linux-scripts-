#ifndef __GE_MAC_FLAGS__
#define __GE_MAC_FLAGS__

#define __MAC
#define	__DEBUGGING__	// avoid conflicts with DebugAssert() definition for the Mac

#if __LP64__
	#define __C4D_64BIT
#endif

#endif
