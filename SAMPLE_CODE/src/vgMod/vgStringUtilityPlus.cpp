


#include <vgStableHeaders.h>
#include <vgMod/vgStringUtilityPlus.h>


namespace vgMod {


	//----------------------------------------------------------------
	void StringUtilityPlus::writeString(const String& strWrite,CFile* pCFile)
	{
		int	nStringSize = strWrite.size();
		pCFile->Write( &nStringSize, sizeof(int));
		pCFile->Write( strWrite.c_str(), nStringSize);
	}
	//----------------------------------------------------------------
	void StringUtilityPlus::readString(String& strRead,CFile* pCFile)
	{
		char	strTemp[64];
		int	nStringSize = 0;
		pCFile->Read( &nStringSize, sizeof(int));
		pCFile->Read( strTemp, nStringSize);
		strTemp[nStringSize] = '\0';

		strRead = String(strTemp);
	}
	//----------------------------------------------------------------
	int   StringUtilityPlus::readString(String& strRead,char* pBuffer)
	{
		long	posRelative	= 0;
		int	nStringSize = 0;
		char	strTemp[64];

		nStringSize = *(int *)(pBuffer + posRelative);
		posRelative += sizeof(int);

		memcpy( strTemp, pBuffer + posRelative, nStringSize);
		posRelative += nStringSize;
		strTemp[nStringSize] = '\0';

		strRead = String(strTemp);

		return	posRelative;
	}

}// end of namespace vgCore
