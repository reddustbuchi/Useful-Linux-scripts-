#ifdef USE_API_MAXON

Error

#elif !defined(C4DMISC_DEBUGGLOBALS_H__)
#define C4DMISC_DEBUGGLOBALS_H__

#include "../general.h"

namespace maxon {

class DebuggerC4D
{
public:
	static Bool	IsPresent();
};

} // C4D_MISC_END

#endif
