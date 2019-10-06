#include "c4d_string.h"
#include "c4d_memory.h"

Char* String::GetCStringCopy(STRINGENCODING type) const
{
	Int32 len = StCall(GetCStringLen) (type);
	if (!len)
		return 0;

	Char* txt = NewMemClear(Char, len + 2);
	if (!txt)
		return nullptr;

	StCall(GetCString) (txt, len + 2, type);
	txt[len] = 0;

	return txt;
}

#if (defined _DEBUG) && (defined __PC)
static Char array[1000];

Char* cstr(String& str)
{
	str.GetCString(array, 1000);
	return array;
}

Char* cstr(const String& str)
{
	str.GetCString(array, 1000);
	return array;
}

#include "c4d_baselist.h"

Char* cstr(GeListNode* node)
{
	if (node->IsInstanceOf(Tbaselist2d))
		((BaseList2D*)node)->GetName().GetCString(array, 1000);
	else
		strcpy(array, "no baselist");
	return array;
}

#include "c4d_file.h"

Char* cstr(Filename& fn)
{
	fn.GetString().GetCString(array, 1000);
	return array;
}

Char* cstr(const Filename& fn)
{
	fn.GetString().GetCString(array, 1000);
	return array;
}

#endif
