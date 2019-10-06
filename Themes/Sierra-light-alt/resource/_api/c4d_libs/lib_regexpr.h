/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef _LIB_REG_EXPR_H_
#define _LIB_REG_EXPR_H_

#define REG_EXP_PARSER    1011197

#define OPERATOR_CONCAT       1
#define ANY_CHAR              2
#define ANY_DIGIT             3

enum RegParseMode { RegParseMatch = 1, RegParseContains, RegParseStarts, RegParseEnds } ENUM_END_LIST(RegParseMode);

class RegularExprParser
{
private:
	RegularExprParser() { }
public:
	static RegularExprParser* Alloc();
	static void Free(RegularExprParser* p);

	Bool Init(const String &strExprssion);
	Bool FindFirst(const String &strText, RegParseMode mode, Bool bOnlyFirst, Int32 &lPos, String &strPattern);
	Bool FindNext(Int32 &lPos, String &strPattern);
	void CleanUp();
};


// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

class RegExpParser;
struct RegExprLib : public C4DLibrary
{
	RegExpParser* (*RegExprLib_Alloc)();
	void          (*RegExprLib_Free)(RegExpParser *&p);
	Bool          (RegExpParser::*Init)(const String &strExprssion);
	Bool          (RegExpParser::*FindFirst)(const String &strText, RegParseMode mode, Bool bOnlyFirst, Int32 &lPos, String &strPattern);
	Bool          (RegExpParser::*FindNext)(Int32 &lPos, String &strPattern);
	void          (RegExpParser::*CleanUp)();
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF


#endif // _LIB_REG_EXPR_H_
