
#include <vgStableHeaders.h>

#include <vgAutoBuild/vgAutoBuildSaver.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgKernel/vgkSystemUtility.h>
#include <vgAutoBuild/vgvAutoBuildManager.h>

namespace vgAutoBuild {

	bool AutoBuildSaver::writeAutoBuildToFile(const String &save_absolute_path, const String &attachDataPath)
	{
		String filePath = vgKernel::StringUtility::
			getPathFromAbsoluteFilename(save_absolute_path);

		String fileName = vgKernel::StringUtility::
			getFilenameWithoutExtFromAbsPath(save_absolute_path);
		fileName += ".autobd";

		filePath += fileName;

		CFile file;

		if (! file.Open(filePath.c_str(), CFile::modeCreate | CFile::modeWrite, NULL))
		{
			VGK_SHOW("Warning. Create AutoBuild File Failed. \n");
			return false;
		}

		return vgAutoBuild::AutoBuildManager::getSingleton().writeToVGFile(&file, filePath);
	}

	bool AutoBuildSaver::readAutoBuildFromFile(const String& save_absolute_path, const String& attachDataPath)
	{
		String filePath = vgKernel::StringUtility::
			getPathFromAbsoluteFilename(save_absolute_path);

		String fileName = vgKernel::StringUtility::
			getFilenameWithoutExtFromAbsPath(save_absolute_path);
		fileName += ".autobd";

		filePath += fileName;

		bool isFileExist = vgKernel::SystemUtility::checkFileExist(filePath);

		if (!isFileExist)
		{
			return false;
		}

		CFile file;

		if (! file.Open(filePath.c_str(), CFile::modeRead, NULL))
		{
			VGK_SHOW("Warning. Open AutoBuild File Failed. \n");
			return false;
		}

		return vgAutoBuild::AutoBuildManager::getSingleton().readFromVGFile(&file, filePath);

	}

}// end of namespace vgGlobal
