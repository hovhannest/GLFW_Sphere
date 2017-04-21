#include "GEFile.h"

#include "GEFile.h"

//////////////////////////////////////////////////////////////////////
// FILE OPERATORS
//////////////////////////////////////////////////////////////////////

// File operations

CGEFile::CGEFile()
{
	m_File = 0;
}

CGEFile::CGEFile(const char* pFileName, bool bRead)
{
	m_File = 0;
	OpenSimple(pFileName, bRead);
}

CGEFile::CGEFile(const char* pFileName, const char* mode)
{
	m_File = 0;
	Open(pFileName, mode);
}

CGEFile::~CGEFile()
{
	Close();
}

bool CGEFile::OpenSimple(const char* pFileName, bool bRead)
{
	return Open(pFileName, bRead ? "rb" : "wb");
}

bool CGEFile::Open(const char* pFileName, const char* mode)
{
	// shouldn't open an already open file (it will leak)
	m_File = fopen(pFileName, mode);

	return m_File != 0;
}

bool CGEFile::Open(FILE* file)
{
	m_File = file;
	return m_File != 0;
}

bool CGEFile::OpenFromMemoty(void* buffer, unsigned int bufferLen)
{
// 	m_File = fopen("tmpFile", "wb+");
// 	m_File = ::FILEOpenFromMemory(buffer, bufferLen);

	return m_File != 0;
}

void CGEFile::Close()
{
	if (m_File != 0)
	{
		fclose(m_File);
		m_File = 0;
	}
}

unsigned int CGEFile::Write(const void* lpBuf, unsigned int nCount)
{
	if (m_File == 0)
		return 0;
	return fwrite(lpBuf, 1, nCount, m_File);
}

unsigned int CGEFile::Read(void* lpBuf, unsigned int nCount)
{
	if (m_File == 0)
		return 0;

	return fread(lpBuf, 1, nCount, m_File);
}

unsigned int CGEFile::Seek(long nOff, unsigned int nFrom)
{
	if (m_File == 0)
		return 0;

	return fseek(m_File, nOff, nFrom);
}

unsigned int CGEFile::GetPosition()
{
	return ftell(m_File);
}

unsigned int CGEFile::GetSize()
{
	unsigned int position = ftell(m_File);
	fseek(m_File, 0L, SEEK_END);
	unsigned int retval = ftell(m_File);
	fseek(m_File, position, SEEK_SET);
	return retval;
}

unsigned int CGEFile::SetSize(unsigned int nSize)
{
	return GetSize();
}

bool CGEFile::Flush()
{
	return fflush(m_File) == 0;
}

FILE* CGEFile::GetFile()
{
	return m_File;
}

CGEFile& CGEFile::operator<<(char c)
{
	Write(&c, sizeof(char));
	return *this;
}

CGEFile& CGEFile::operator<<(short w)
{
	Write(&w, sizeof(short));
	return *this;
}

CGEFile& CGEFile::operator<<(int i)
{
	Write(&i, sizeof(int));
	return *this;
}

CGEFile& CGEFile::operator<<(long l)
{
	Write(&l, sizeof(long));
	return *this;
}

CGEFile& CGEFile::operator<<(int64_t i64)
{
	Write(&i64, sizeof(int64_t));
	return *this;
}

CGEFile& CGEFile::operator<<(unsigned char b)
{
	Write(&b, sizeof(unsigned char));
	return *this;
}

CGEFile& CGEFile::operator<<(unsigned short w)
{
	Write(&w, sizeof(unsigned short));
	return *this;
}

CGEFile& CGEFile::operator<<(unsigned int ui)
{
	Write(&ui, sizeof(unsigned int));
	return *this;
}

CGEFile& CGEFile::operator<<(unsigned long ul)
{
	Write(&ul, sizeof(unsigned long));
	return *this;
}

CGEFile& CGEFile::operator<<(uint64_t ui64)
{
	Write(&ui64, sizeof(uint64_t));
	return *this;
}


CGEFile& CGEFile::operator<<(float f)
{
	Write(&f, sizeof(float));
	return *this;
}

CGEFile& CGEFile::operator<<(double d)
{
	Write(&d, sizeof(double));
	return *this;
}

CGEFile& CGEFile::operator<<(bool b)
{
	Write(&b, sizeof(bool));
	return *this;
}

CGEFile& CGEFile::operator<<(const CGEString& str)
{
	WriteString(str);
	return *this;
}

CGEFile& CGEFile::operator<<(const CGEStringW& strw)
{
	WriteString(strw);
	return *this;
}

CGEFile& CGEFile::operator<<(const char* pstr)
{
	WriteString(pstr);
	return *this;
}

CGEFile& CGEFile::operator<<(const wchar_t* pstrw)
{
	WriteString(pstrw);
	return *this;
}

// Stream extraction operations
CGEFile& CGEFile::operator >> (char& c)
{
	Read(&c, sizeof(char));
	return *this;
}

CGEFile& CGEFile::operator >> (short& w)
{
	Read(&w, sizeof(short));
	return *this;
}

CGEFile& CGEFile::operator >> (int& i)
{
	Read(&i, sizeof(int));
	return *this;
}

CGEFile& CGEFile::operator >> (long& l)
{
	Read(&l, sizeof(long));
	return *this;
}

CGEFile& CGEFile::operator >> (int64_t& i64)
{
	Read(&i64, sizeof(int64_t));
	return *this;
}

CGEFile& CGEFile::operator >> (unsigned char& b)
{
	Read(&b, sizeof(unsigned char));
	return *this;
}

CGEFile& CGEFile::operator >> (unsigned short& w)
{
	Read(&w, sizeof(unsigned short));
	return *this;
}

CGEFile& CGEFile::operator >> (unsigned int& ui)
{
	Read(&ui, sizeof(unsigned int));
	return *this;
}

CGEFile& CGEFile::operator >> (unsigned long& ul)
{
	Read(&ul, sizeof(unsigned long));
	return *this;
}

CGEFile& CGEFile::operator >> (uint64_t& ui64)
{
	Read(&ui64, sizeof(uint64_t));
	return *this;
}


CGEFile& CGEFile::operator >> (float& f)
{
	Read(&f, sizeof(float));
	return *this;
}

CGEFile& CGEFile::operator >> (double& d)
{
	Read(&d, sizeof(double));
	return *this;
}

CGEFile& CGEFile::operator >> (bool& b)
{
	Read(&b, sizeof(bool));
	return *this;
}

CGEFile& CGEFile::operator >> (CGEString& str)
{
	ReadString(str);
	return *this;
}

CGEFile& CGEFile::operator >> (CGEStringW& strw)
{
	ReadString(strw);
	return *this;
}

//String Read/Write-------------------------------
void CGEFile::WriteStringLength(size_t size)
{
	if (size < 0xFF)
	{
		*this << (static_cast<unsigned char>(size));
	}
	else if (size < 0xFFFF)
	{
		*this << (unsigned char)0xFF;
		*this << (static_cast<unsigned short>(size));
	}
	else
	{
		*this << (unsigned char)0xFF;
		*this << (unsigned short)0xFFFF;
		*this << (static_cast<unsigned int>(size));
	}
}

size_t CGEFile::ReadStringLength()
{
	unsigned int nRealSize = 0;
	unsigned char bSize;
	unsigned short wSize;
	*this >> bSize;
	if (bSize != 0xFF)
	{
		nRealSize = bSize;
	}
	else
	{
		*this >> wSize;
		if (wSize != 0xFFFF)
		{
			nRealSize = wSize;
		}
		else
		{
			*this >> nRealSize;
		}
	}

	return nRealSize;
}

//CHAR STRING---------------------------------------------------------
void CGEFile::WriteString(const char* pstr, size_t size)
{
	WriteStringLength(size);
	if (size > 0)
		Write(pstr, static_cast<unsigned int>(size));
}

void CGEFile::WriteString(const char* pstr)
{
	WriteString(pstr, strlen(pstr));
}

void CGEFile::WriteString(const CGEString& str)
{
	WriteString(str.data(), str.length());
}

void CGEFile::ReadString(char* pstr, size_t size)
{
	size_t realsize = ReadStringLength();

	if (realsize == 0)
	{
		pstr[0] = 0;
		return;
	}

	if (realsize >= size)
	{
		Read(pstr, static_cast<unsigned int>(size));
		pstr[size] = 0;
		Seek(static_cast<long>(realsize - size), current);
		return;
	}

	Read(pstr, static_cast<long>(realsize));
	pstr[realsize] = 0;
}

void CGEFile::ReadString(CGEString& str)
{
	size_t realsize = ReadStringLength();

	if (realsize == 0)
	{
		str.clear();
		return;
	}

	str.resize(realsize);
	Read(const_cast<char*>(str.data()), static_cast<unsigned int>(realsize));
}

//WCHAR STRING---------------------------------------------------------
void CGEFile::WriteString(const wchar_t* pstrw, size_t size)
{
	WriteStringLength(size);
	if (size > 0)
		Write(pstrw, static_cast<unsigned int>(size) * sizeof(wchar_t));
}

void CGEFile::WriteString(const wchar_t* pstrw)
{
	WriteString(pstrw, wcslen(pstrw));
}

void CGEFile::WriteString(const CGEStringW& strw)
{
	WriteString(strw.data(), strw.length());
}

void CGEFile::ReadString(wchar_t* pstrw, size_t size)
{
	size_t realsize = ReadStringLength();

	if (realsize == 0)
	{
		pstrw[0] = 0;
		return;
	}

	if (realsize >= size)
	{
		Read(pstrw, static_cast<unsigned int>(size) * sizeof(wchar_t));
		pstrw[size] = 0;
		Seek(static_cast<long>(realsize - size) * sizeof(wchar_t), current);
		return;
	}

	Read(pstrw, static_cast<unsigned int>(realsize));
	pstrw[realsize] = 0;
}

void CGEFile::ReadString(CGEStringW& strw)
{
	size_t realsize = ReadStringLength();

	if (realsize == 0)
	{
		strw.clear();
		return;
	}

	strw.resize(realsize);
	Read(const_cast<wchar_t*>(strw.data()), static_cast<unsigned int>(realsize) * sizeof(wchar_t));
}


//////////////////////////////////////////////////////////////////////
// MEMORY STREAM
//////////////////////////////////////////////////////////////////////
CGEMemoryFile::CGEMemoryFile()
{
	m_nSize = 0;
	m_nPosition = 0;
	m_pData = NULL;
}

CGEMemoryFile::CGEMemoryFile(CGEFile& stream)
{
	m_nSize = 0;
	m_nPosition = 0;
	m_pData = NULL;

	SetSize(stream.GetSize());
	stream.Seek(0, CGEFile::begin);

	if (m_nSize)
		stream.Read(m_pData, m_nSize);
}

CGEMemoryFile::CGEMemoryFile(const CGEMemoryFile& mem)
{
	m_nSize = 0;
	m_nPosition = 0;
	m_pData = NULL;
	SetSize(mem.m_nSize);
	memcpy(m_pData, mem.m_pData, m_nSize);
}

CGEMemoryFile::~CGEMemoryFile()
{
	Close();
}

unsigned int CGEMemoryFile::SetSize(unsigned int nSize)
{
	if (nSize < m_nPosition) m_nPosition = nSize;
	m_nSize = 0;
	if (nSize)
	{
		m_pData = realloc(m_pData, nSize + 4);
		if (m_pData == NULL)
		{
			m_nPosition = 0;
			return 0;
		}
	}
	else
	{
		free(m_pData);
		m_pData = NULL;
	}

	m_nSize = nSize;
	return m_nSize;
}

bool CGEMemoryFile::Load(CGEFile& stream)
{
	m_nPosition = 0;
	stream.Read(&m_nSize, sizeof(m_nSize));

	if (m_pData)
		free(m_pData);
	m_pData = NULL;
	m_pData = malloc(m_nSize);
	if (m_pData == NULL)
		return false;

	if (m_nSize)
		stream.Read(m_pData, m_nSize);
	return true;
}

bool CGEMemoryFile::Save(CGEFile& stream)
{
	stream.Write(&m_nSize, sizeof(m_nSize));

	if (m_nSize)
		stream.Write(m_pData, m_nSize);

	return true;
}

void CGEMemoryFile::Close()
{
	if (m_pData)
	{
		free(m_pData);
		m_pData = NULL;
	}

	m_nSize = 0;
	m_nPosition = 0;
}

unsigned int CGEMemoryFile::Write(const void* lpBuf, unsigned int nCount)
{
	if (nCount == 0 || lpBuf == NULL)
		return 0;

	if (nCount + m_nPosition > m_nSize)
	{
		if (0 == SetSize(m_nPosition + nCount))
			return 0;
	}

	memcpy(((unsigned char*)m_pData) + m_nPosition, lpBuf, nCount);

	m_nPosition += nCount;
	return nCount;
}

unsigned int CGEMemoryFile::Read(void* lpBuf, unsigned int nCount)
{
	if (m_pData == NULL || m_nPosition == m_nSize)
		return 0;

	if (nCount > m_nSize - m_nPosition)
		nCount = m_nSize - m_nPosition;

	if (nCount == 0)
		return 0;

	memcpy(lpBuf, ((unsigned char*)m_pData) + m_nPosition, nCount);

	m_nPosition += nCount;
	return nCount;
}

unsigned int CGEMemoryFile::Seek(long nOff, unsigned int nFrom)
{
	if (m_pData == NULL)
		return 0;
	switch (nFrom)
	{
	case begin:
		m_nPosition = nOff;
		break;

	case current:
		m_nPosition += nOff;
		break;

	case end:
		if (nOff > static_cast<long>(m_nSize))
			m_nPosition = 0;
		else
			m_nPosition = m_nSize - nOff;
		break;
	}

	if (m_nPosition > m_nSize)
		m_nPosition = m_nSize;

	return m_nPosition;
}

unsigned int CGEMemoryFile::Clone(CGEMemoryFile** ppCGEMemoryFile)
{
	*ppCGEMemoryFile = new CGEMemoryFile();
	if (*ppCGEMemoryFile == NULL)
		return -1;

	if (m_nSize)
	{
		(*ppCGEMemoryFile)->SetSize(m_nSize);
		memcpy((*ppCGEMemoryFile)->GetData(), m_pData, m_nSize);
	}
	return m_nSize;
}
