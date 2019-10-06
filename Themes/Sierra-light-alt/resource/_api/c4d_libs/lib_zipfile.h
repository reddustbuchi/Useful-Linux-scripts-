#ifndef _LIB_ZIPFILE_H_
#define _LIB_ZIPFILE_H_

// based upon zlib, see http://www.gzip.org/zlib/ for more information

#include "c4d_library.h"

// external attributes
#define ZIP_FLAG_READONLY							0x00000001
#define ZIP_FLAG_DIRECTORY						0x00000010

#define ZIP_FILE_FLAG_OWNER_R					0x01000000
#define ZIP_FILE_FLAG_OWNER_W					0x00800000
#define ZIP_FILE_FLAG_OWNER_X					0x00400000
#define ZIP_FILE_FLAG_GROUP_R					0x00200000
#define ZIP_FILE_FLAG_GROUP_W					0x00100000
#define ZIP_FILE_FLAG_GROUP_X					0x00080000
#define ZIP_FILE_FLAG_PUBLIC_R				0x00040000
#define ZIP_FILE_FLAG_PUBLIC_W				0x00020000
#define ZIP_FILE_FLAG_PUBLIC_X				0x00010000
#define ZIP_FILE_FLAG_UNIX_MASK				0x01ff0000
#define ZIP_FILE_FLAG_USE_UNIX_FLAGS	0x80000000

// internal attributes
#define ZIP_FILE_FLAG_UNIX_ATTR				0x00000001

#define ZIP_EXTRACT_CREATE_SUBDIR			0x00000001
#define ZIP_EXTRACT_IGNORE_READONLY		0x00000002
#define ZIP_EXTRACT_IGNORE_PATH_CASE	0x00000004 // ignore path case on Linux (if the path or parts of it already exist)

struct ZipFileTime
{
	UINT nSec; // seconds (0..59)
	UINT nMin; // minutes (0..59)
	UINT nHour; // hour (0..23)
	UINT nMDay; // day of month (1..31)
	UINT nMonth; // month (0..11)
	UINT nYear; // (1980..2044)
};

struct ZipFileGlobalInfo
{
	UInt32 lEntries;       // the number of entries in the zip file
	UInt32 lCommentSize;   // the size of the global comment
};

struct ZipFileInfo
{
	UInt32 lVersion;
	UInt32 lVersionNeeded;
	UInt32 lFlags;
	UInt32 lCompressionMethod;
	UInt32 lDOSDate;
	UInt32 lCRC32;
	UInt32 lCompressedSize;
	UInt32 lUncompressedSize;
	UInt32 lSizeFilename;
	UInt32 lSizeExtraField;
	UInt32 lSizeFileComment;
	UInt32 lDiskNumberStart;
	UInt32 lInternalAttr;
	UInt32 lExternalAttr;
	ZipFileTime t;
};

struct ZipWriteInfo
{
	ZipFileTime ti; // the time of the file in the zip file
	UInt32 lInternalAttr, lExternalAttr; // currently private
};

enum ZipMethod { ZipMethodDeflate, ZipMethodStore };

typedef Bool (*ExtractDirectoryCallbackEx)(const Filename &fnSrc, const Filename &fnDest, void* pData); // return false if you want to cancel

typedef Int32 (*ExtractDirectoryCallback)(const Filename &fnSrc, const Filename &fnDest, void* pData, Int32 lInfo);
#define EXTRACT_INFO_SUCCESS													0
#define EXTRACT_INFO_FAILED														1
#define EXTRACT_INFO_CANT_WRITE												2
	#define EXTRACT_INFO_CANT_WRITE_R_FORCE_OVERWRITE		2
	#define EXTRACT_INFO_CANT_WRITE_R_IGNORE						3
#define EXTRACT_INFO_R_CANCEL													1

#define ZIP_APPEND_CREATE					0
#define ZIP_APPEND_CREATEAFTER		1
#define ZIP_APPEND_ADDINZIP				2

class ZipFile
{
private:
	ZipFile();
	~ZipFile();

public:
	static ZipFile* Alloc();
	static void Free(ZipFile *&p);

	static Bool CreateLocalFileName(const Filename &fn, String& str);
	static Bool CreateFilename(const String& str, Filename &fn);
	static Bool GetFileCRC(const Filename &fn, UInt32 &ulCRC);
	static UInt32 CalcCRC32(const void* pBuffer, Int32 lBufferLen, UInt32 ulOldCRC = 0);

	// set lAppend = ZIP_APPEND_*, if you want to append the zip file to an existing file
	Bool Open(const Filename &fn, const Bool bRead, const Int32 lAppend = ZIP_APPEND_CREATE);
	// OpenEncrypted uses AES encryption
	Bool OpenEncrypted(const Filename &fn, const Bool bRead, const char* pchKey, Int32 lKeyLength, Int32 lBlockLength, UInt32 lAESFlags, const Int32 lAppend = ZIP_APPEND_CREATE);
	Bool SetSpanning(UInt32 ulSpan, Bool bOverwrite); // call immediately after opening the file for writing

	Bool ExtractToDirectory(const Filename& fnZip, const Filename& fnDir, Int32 lFlags = ZIP_EXTRACT_CREATE_SUBDIR, ExtractDirectoryCallback fn = nullptr,
		void* pData = nullptr, const char* pChPassword = nullptr);
	Bool ExtractToDirectoryEx(const Filename& fnZip, const Filename& fnDir, Int32 lFlags = ZIP_EXTRACT_CREATE_SUBDIR, ExtractDirectoryCallbackEx fn = nullptr,
		void* pData = nullptr, const char* pChPassword = nullptr);

	// closes the file
	Bool Close();
	// comments are only written if the file is saved
	Bool Close(const char* pchGlobalComment);
	Bool Close(const String& strGlobalComment);

	// only for writing zip files

	// creates a new file in the current zip archive. Directories must be separated by a slash /
	Bool CreateFileInZip(const String& strName, ZipWriteInfo* pInfo, void* pExtraFieldLocal, UInt32 lExtraSizeLocal, void* pExtraFieldGlobal, UInt32 lExtraSizeGlobal,
											 String* pstrComment, ZipMethod method, INT lLevel, const char* pchPassword = nullptr, UInt32 ulCryptingCRC = 0);  // level may range from 0 to 9
	Bool WriteInFileInZip(const void* pBuffer, const UInt32 lLen, const Int32 lExpectedSize = -1);
	Bool CopyInFileInZip(const Filename& fn, const String& str, const char* pchPassword = nullptr);
	Bool CopyInFileInZip(const Filename& fn, const String& str, UInt32 ulInternalAttributes, UInt32 ulExternalAttributes, const char* pchPassword = nullptr);
	Bool CloseFileInZip();
	Bool CreateDirectoryInZip(const String& strName, ZipFileTime* pTime); // a slash is added if necessary

	// only for reading
	Bool GetGlobalInfo(ZipFileGlobalInfo &i);
	Bool GetGlobalComment(String& str);
	Bool GoToFirstFile();
	Bool GoToNextFile();
	Bool LocateFile(const String& strName);
	Bool GetCurrentFileInfo(ZipFileInfo &i);
	Bool GetCurrentFileInfo(String* pstrName, String* pstrComment = nullptr, void* pExtraField = nullptr, UInt32 lExtraFieldSize = 0);
	Bool ExtractCurrentFile(const Filename& fnDir, BaseThread* pThread, Int32 lFlags = ZIP_EXTRACT_CREATE_SUBDIR, const char* pchPassword = nullptr, Filename* pfnDest = nullptr);
	Bool ExtractCurrentFile(const Filename& fnDir, Int32 lFlags = ZIP_EXTRACT_CREATE_SUBDIR, const char* pchPassword = nullptr, Filename* pfnDest = nullptr);
	Bool OpenCurrentFile(const char* pChPassword = nullptr);
	Bool CloseCurrentFile();
	Int32 ReadCurrentFile(void* pBuffer, UInt32 lBufferSize); // returns the number of read bytes, < 0 if there was an error
	Int32 GetCurrentFileReadPosition();
	Bool EndOfCurrentFile();

	// call before open/init
	Bool SetCompressionLevel(Int32 lLevel);
	Int32 GetCompressionLevel() const;
};

#define FILETIME_CREATED			0
#define FILETIME_MODIFIED			1
#define FILETIME_ACCESS				2
Bool GetFileTime(const Filename &fn, UINT &nYear, UINT &nMonth, UINT &nDay, UINT &nHour, UINT &nMinute, UINT &nSec, Int32 lType, Bool bIsDir);
Bool SetFileTime(const Filename &fn, UINT nYear, UINT nMonth, UINT nDay, UINT nHour, UINT nMinute, UINT nSec, Int32 lType, Bool bIsDir);
// level may range from 0 to 9, plDestLen must be 0.1% larger than lSrcLen + 12 Bytes, plDestLen is filled with the compressed data length
// pDestData is an array of *plDestLen bytes. lSrcLen may not be greater than 2 GiB
Bool CompressDataRaw(const void* pSrcData, Int lSrcLen, void* pDestData, Int* plDestLen, Int32 lLevel);
// plDestLen must have the same value as lSrcLen in CompressData. pDestData is an array of *plDestLen bytes, lSrcLen may not be greater than 2 GiB
Bool UncompressDataRaw(const void* pSrcData, Int lSrcLen, void* pDestData, Int* plDestLen, Int* plRead = nullptr);

// Similar to the functions above, but the array is created internally. Use DeleteMem to delete it
#define COMPRESS_DATA_32_BYTE_PADDING		0x00000100 // may be ORed with lLevel to make lDestLen a multiple of 32
Bool CompressData(const void* pSrcData, Int lSrcLen, void *&pDestData, Int &lDestLen, Int32 lLevel); // lSrcLen may not be greater than 2 GiB
Bool UncompressData(const void* pSrcData, Int lSrcLen, void *&pDestData, Int &lDestLen, Int* plRead = nullptr); // lSrcLen may not be greater than 2 GiB

struct ZHandle;
ZHandle* CompressDataInit(Int32 lLevel);
Bool CompressDataDoIt(ZHandle *handle, const void* pSrcData, Int lSrcLen, void *&pDestData, Int &lDestLen, Int32 lFlags);
void CompressDataFree(ZHandle *&handle);

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#define LIBRARY_ZIPFILE     1011188

class iZipFile;

struct ZipFileLib : public C4DLibrary
{
	ZipFile*  (*ZipFile_Alloc)();
	void      (*ZipFile_Free)(ZipFile *&p);
	Bool      (*ZipFile_CreateLocalFileName)(const Filename &fn, String& str);
	Bool      (*ZipFile_CreateFilename)(const String& str, Filename &fn);
	Bool      (*ZipFile_GetFileCRC)(const Filename &fn, UInt32 &ulCRC);
	UInt32     (*ZipFile_CalcCRC32)(const void* pBuffer, Int32 lBufferLen, UInt32 ulOldCRC);

	Bool      (iZipFile::*Open)(const Filename& fn, const Bool bRead, const Int32 lAppend);
	Bool      (iZipFile::*ExtractToDirectoryEx)(const Filename& fnZip, const Filename& fnDir, Int32 lFlags, ExtractDirectoryCallbackEx fn, void* pData, const char* pChPassword);
	Bool      (iZipFile::*CloseNC)();
	Bool      (iZipFile::*CloseCC)(const char* pComment);
	Bool      (iZipFile::*CloseSC)(const String& strComment);

	// write
	Bool      (iZipFile::*CreateFileInZip)(const String& strName, ZipWriteInfo* pInfo, void* pExtraFieldLocal, UInt32 lExtraSizeLocal, void* pExtraFieldGlobal, UInt32 lExtraSizeGlobal,
											 String* pstrComment, ZipMethod method, INT lLevel, const char* pchPassword, UInt32 ulCryptingCRC);
	Bool      (iZipFile::*WriteInFileInZipEx)(const void* pBuffer, UInt32 lLen, Int32 lExpectedSize);
	Bool      (iZipFile::*CopyInFileInZipA)(const Filename& fn, const String& str, const char* pchPassword);
	Bool      (iZipFile::*CloseFileInZip)();
	Bool      (iZipFile::*CreateDirectoryInZip)(const String& strName, ZipFileTime* pTime);

	// read
	Bool      (iZipFile::*GetGlobalInfo)(ZipFileGlobalInfo &i);
	Bool      (iZipFile::*GetGlobalComment)(String& str);
	Bool      (iZipFile::*GoToFirstFile)();
	Bool      (iZipFile::*GoToNextFile)();
	Bool      (iZipFile::*LocateFile)(const String& strName);
	Bool      (iZipFile::*GetCurrentFileInfoA)(ZipFileInfo &i);
	Bool      (iZipFile::*GetCurrentFileInfoB)(String* pstrName, String* pstrComment, void* pExtraField, UInt32 lExtraFieldSize);
	Bool      (iZipFile::*OpenCurrentFile)(const char* pChPassword);
	Bool      (iZipFile::*CloseCurrentFile)();
	Int32      (iZipFile::*ReadCurrentFile)(void* pBuffer, UInt32 lBufferSize);
	Int32      (iZipFile::*GetCurrentFileReadPosition)();
	Bool      (iZipFile::*EndOfCurrentFile)();

	// other stuff
	Bool      (*GetFileTime)(const Filename &fn, UINT &nYear, UINT &nMonth, UINT &nDay, UINT &nHour, UINT &nMinute, UINT &nSec, Int32 lType, Bool bIsDir);
	Bool      (*SetFileTime)(const Filename &fn, UINT nYear, UINT nMonth, UINT nDay, UINT nHour, UINT nMinute, UINT nSec, Int32 lType, Bool bIsDir);
	Bool      (*CompressDataRaw)(const void* pSrcData, Int lSrcLen, void* pDestData, Int* plDestLen, Int32 lLevel);
	Bool      (*UncompressDataRaw)(const void* pSrcData, Int lSrcLen, void* pDestData, Int* plDestLen, Int* plRead);
	Bool      (*CompressData2)(const void* pSrcData, Int lSrcLen, void *&pDestData, Int &lDestLen, Int32 lLevel);
	Bool      (*UncompressData2)(const void* pSrcData, Int lSrcLen, void *&pDestData, Int &lDestLen, Int* plRead);

	Bool      (iZipFile::*ExtractCurrentFile)(const Filename& fnDir, Int32 lFlags, const char* pchPassword, Filename* pfnDest);
	Bool      (iZipFile::*ExtractToDirectory)(const Filename& fnZip, const Filename& fnDir, Int32 lFlags, ExtractDirectoryCallback fn, void* pData, const char* pChPassword);

	Bool      (iZipFile::*SetSpanning)(UInt32 ulSpan, Bool bOverwrite);
	Bool      (iZipFile::*OpenEncrypted)(const Filename &fn, const Bool bRead, const char* pKey, Int32 lKeyLength, Int32 lBlockLength, UInt32 lAESFlags, const Int32 lAppend);

	Bool      (iZipFile::*ExtractCurrentFileT)(const Filename& fnDir, BaseThread* pThread, Int32 lFlags, const char* pchPassword, Filename* pfnDest);

	ZHandle*	(*CompressDataInit)(Int32 lLevel);
	Bool			(*CompressDataDoIt)(ZHandle *handle, const void* pSrcData, Int lSrcLen, void *&pDestData, Int &lDestLen, Int32 flags);
	void			(*CompressDataFree)(ZHandle *&handle);

	Bool			(iZipFile::*CopyInFileInZipB)(const Filename& fn, const String& str, UInt32 ulInternalAttributes, UInt32 ulExternalAttributes, const char* pchPassword);

	Bool			(iZipFile::*SetCompressionLevel)(Int32 lLevel);
	Int32			(iZipFile::*GetCompressionLevel)() const;

	Bool      (iZipFile::*WriteInFileInZip)(const void* pBuffer, UInt lLen, Int64 lExpectedSize);
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF


#endif // _LIB_ZIPFILE_H_
