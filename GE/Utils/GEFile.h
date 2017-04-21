#pragma once

#include "Utils.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// FILE
//////////////////////////////////////////////////////////////////////

/** This class used for encapsulating the reading of data.
It's an abstract class.
*/
class CGEFile
{
protected:
	FILE*	m_File;
public:
	enum SeekPosition { begin = 0x0, current = 0x1, end = 0x2 };
public:
	//Default constructor does nothing
	CGEFile();
	//Constructs  FileStream by filename in ASCII
	CGEFile(const char* pFileName, bool bRead = true);
	//Constructs  FileStream by filename in UNICODE
	CGEFile(const char* pFileName, const char* mode);

	//Destructor
	virtual ~CGEFile();

	//Simplify opens FileStream by filename in UNICODE
	bool OpenSimple(const char* pFileName, bool bRead = true);
	bool Open(const char* pFileName, const char* mode);
	bool Open(FILE* file);
	bool OpenFromMemoty(void* buffer, unsigned int bufferLen);


	//Closes file
	virtual void Close();

	//Writes data from a buffer to the FileStream
	virtual unsigned int Write(const void* lpBuf, unsigned int nCount);
	//Reads data into a buffer from the FileStream
	virtual unsigned int Read(void* lpBuf, unsigned int nCount);
	//Positions the current file pointer
	virtual unsigned int Seek(long nOff, unsigned int nFrom);
	//Obtains the current logical length of the file in bytes
	virtual unsigned int GetSize();
	//Call this function to change the length of the file
	virtual unsigned int SetSize(unsigned int nSize);
	//Call this method to get the current file pointer position
	virtual unsigned int GetPosition();

	bool  Flush();
	//Retrieves the file handle of the FileStream
	FILE* GetFile();

	// insertion operations
	CGEFile& operator<<(char c);
	CGEFile& operator<<(short w);
	CGEFile& operator<<(int i);
	CGEFile& operator<<(long l);
	CGEFile& operator<<(int64_t i64);

	CGEFile& operator<<(unsigned char b);
	CGEFile& operator<<(unsigned short w);
	CGEFile& operator<<(unsigned int ui);
	CGEFile& operator<<(unsigned long ul);
	CGEFile& operator<<(uint64_t ui64);

	CGEFile& operator<<(float f);
	CGEFile& operator<<(double d);

	CGEFile& operator<<(bool b);

	CGEFile& operator<<(const char* pstr);
	CGEFile& operator<<(const wchar_t* pstrw);

	CGEFile& operator<<(const CGEString& str);
	CGEFile& operator<<(const CGEStringW& strw);

	// extraction operations
	CGEFile& operator >> (char& c);
	CGEFile& operator >> (short& w);
	CGEFile& operator >> (int& i);
	CGEFile& operator >> (long& l);
	CGEFile& operator >> (int64_t& i64);

	CGEFile& operator >> (unsigned char& b);
	CGEFile& operator >> (unsigned short& w);
	CGEFile& operator >> (unsigned int& ui);
	CGEFile& operator >> (unsigned long& ul);
	CGEFile& operator >> (uint64_t& ui64);

	CGEFile& operator >> (float& f);
	CGEFile& operator >> (double& d);

	CGEFile& operator >> (bool& b);

	CGEFile& operator >> (CGEString& str);
	CGEFile& operator >> (CGEStringW& strw);

	//String Read/Write
	void WriteString(const char* pstr, size_t size);
	void WriteString(const char* pstr);
	void WriteString(const CGEString& str);

	void ReadString(char* pstr, size_t size);
	void ReadString(CGEString& str);

	void WriteString(const wchar_t* pstrw, size_t size);
	void WriteString(const wchar_t* pstrw);
	void WriteString(const CGEStringW& strw);

	void ReadString(wchar_t* pstrw, size_t size);
	void ReadString(CGEStringW& strw);

protected:
	size_t ReadStringLength();
	void WriteStringLength(size_t size);
};

/** Shared pointer to allow data streams to be passed around without
worrying about deallocation
*/
//	typedef SharedPtr<ES::Stream> StreamPtr;

//--------------------------------------------------------------------
// MEMORY STREAM
//--------------------------------------------------------------------
/** Common subclass of Stream for handling data from memory.
*/
class CGEMemoryFile : public CGEFile
{
protected:
	/// Length of the memory chunk in bytes
	unsigned int	m_nSize;
	/// Current position in the memory in bytes
	unsigned int	m_nPosition;
	/// Pointer to the start of the data area
	void*	m_pData;
public:
	//Default constructor
	CGEMemoryFile();
	//Copy constructor
	CGEMemoryFile(const CGEMemoryFile& mem);
	//Constructing CGEMemoryFile by loading from the Stream
	CGEMemoryFile(CGEFile& stream);
	//Destructor
	~CGEMemoryFile();

	//This metod loads CGEMemoryFile from the Stream
	bool	Load(CGEFile& stream);
	//This metod saves CGEMemoryFile to the Stream
	bool	Save(CGEFile& stream);
	//Closes a CGEMemoryFile
	void	Close();

	//Clones a CGEMemoryFile
	unsigned int Clone(CGEMemoryFile** ppMem);

	//Writes data from a buffer to the CGEMemoryFile
	unsigned int Write(const void* lpBuf, unsigned int nCount);
	//Reads data into a buffer from the CGEMemoryFile
	unsigned int Read(void* lpBuf, unsigned int nCount);
	//Positions the current stream pointer
	unsigned int Seek(long nOff, unsigned int nFrom);
	//Obtains the current logical length of the stream in bytes
	unsigned int GetSize() { return m_nSize; }
	//Call this function to change the length of the CGEMemoryFile
	unsigned int SetSize(unsigned int nSize);
	//Call this method to get the current pointer position
	unsigned int GetPosition() { return m_nPosition; }

	//Retrieves the memory buffer pointer of the CGEMemoryFile
	void* GetData() { return m_pData; }
};

