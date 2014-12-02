#define ANGELSCRIPT_DLL_LIBRARY_IMPORT
#include <angelscript.h>

// Fix of incorrect define (r (c::*)p changed to r (c::*)(p))
#undef asMETHODPR
#define asMETHODPR(c,m,p,r) asSMethodPtr<sizeof(void (c::*)())>::Convert(AS_METHOD_AMBIGUITY_CAST(r (c::*)(p))(&c::m))