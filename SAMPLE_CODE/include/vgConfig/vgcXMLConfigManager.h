#ifndef __VGCXMLCONFIGMANAGER_H__
#define __VGCXMLCONFIGMANAGER_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>
#include <vgKernel/vgkTrace.h>
#include <vgConf/XMLProfile.h>

namespace vgConfig{
	//@date   2009.10.24
	//@author kinghj

	//@XML 配置文件相关

	typedef struct FileData_t
	{
		CString section;
		CString key;
		CString keyvalue;

	}FileData;

	typedef struct SectionData_t
	{
		std::vector<CString>  _Currentkey;
		std::vector<CString>  _Currentkeyvalue;
	}SectionData;

	class VGK_EXPORT Error
	{
	public:
		Error (const char *msg):message (msg) {};
	private:
		const char * message;
	};

	class VGK_EXPORT XMLConfigManager : public vgKernel::Singleton<XMLConfigManager>
	{


		friend class vgKernel::Singleton<XMLConfigManager>;
	private:
		XMLConfigManager();

		~XMLConfigManager()
		{
			VGK_TRACE(_T("XMLConfigManager destroyed."));
		}

	protected:
		virtual bool initialise()
		{
			return true;
		}
		virtual bool shutdown()
		{
			return true;
		}

	public:

		bool LoadXmlDocument(CString filename);
		float GetFloatValue(CString section, CString  key);
		int GetIntValue(CString section, CString  key);
		void AddKeys(CString section, CString key, CString keyvalue);
		bool FindSection(CString section);
		void SaveXML(CString filename);
		void GetKeyValue(CXmlProfile& profile);
		CString SetIntToCtrValue(int intvalue);
		CString SetFloatToCtrValue(float  floatvalue);
		SectionData GetCurrentValue(CString section);
		void RemoveKeys(CString section, CString key);
		void RemoveSection(CString section);

	protected:
		CXmlProfile m_Profile;
		CString FileName;	
		int flag;
		//CXListBox m_ListBox;
	public:
	   SectionData sectiondata;
	public:
		std::vector<FileData> dataGroup;

	};
		

}
#endif