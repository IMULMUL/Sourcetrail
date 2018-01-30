#include "utility/path_detector/cxx_header/CxxVs10To14HeaderPathDetector.h"

#include <string>

#include <QSettings>
#include <QSysInfo>

#include "utility/file/FilePath.h"
#include "utility/path_detector/cxx_header/utilityCxxHeaderDetection.h"
#include "utility/utility.h"

CxxVs10To14HeaderPathDetector::CxxVs10To14HeaderPathDetector(VisualStudioType type, bool isExpress, ApplicationArchitectureType architecture)
	: PathDetector(visualStudioTypeToString(type) + (isExpress ? " Express" : "") + (architecture == APPLICATION_ARCHITECTURE_X86_64 ? " 64 Bit" : ""))
	, m_version(visualStudioTypeToVersion(type))
	, m_isExpress(isExpress)
	, m_architecture(architecture)
{
}

CxxVs10To14HeaderPathDetector::~CxxVs10To14HeaderPathDetector()
{
}

std::vector<FilePath> CxxVs10To14HeaderPathDetector::getPaths() const
{
	const FilePath vsInstallPath = getVsInstallPathUsingRegistry();

	// vc++ headers
	std::vector<FilePath> headerSearchPaths;
	if (vsInstallPath.exists())
	{
		for (const std::wstring& subdirectory : { L"vc/include" , L"vc/atlmfc/include" })
		{
			FilePath headerSearchPath = vsInstallPath.getConcatenated(subdirectory);
			if (headerSearchPath.exists())
			{
				headerSearchPaths.push_back(headerSearchPath.makeCanonical());
			}
		}
	}

	if (!headerSearchPaths.empty())
	{
		utility::append(headerSearchPaths, utility::getWindowsSdkHeaderSearchPaths(m_architecture));
	}

	return headerSearchPaths;
}

int CxxVs10To14HeaderPathDetector::visualStudioTypeToVersion(const VisualStudioType t)
{
	switch (t)
	{
	case VISUAL_STUDIO_2010: 
		return 10;
	case VISUAL_STUDIO_2012: 
		return 11;
	case VISUAL_STUDIO_2013: 
		return 12;
	case VISUAL_STUDIO_2015: 
		return 14;
	}
	return 0;
}

std::string CxxVs10To14HeaderPathDetector::visualStudioTypeToString(const VisualStudioType t)
{
	std::string ret = "Visual Studio";
	switch (t)
	{
	case VISUAL_STUDIO_2010: 
		ret += " 2010";
	case VISUAL_STUDIO_2012: 
		ret += " 2012";
	case VISUAL_STUDIO_2013: 
		ret += " 2013";
	case VISUAL_STUDIO_2015: 
		ret += " 2015";
	}
	return ret;
}

FilePath CxxVs10To14HeaderPathDetector::getVsInstallPathUsingRegistry() const
{
	QString key = "HKEY_LOCAL_MACHINE\\SOFTWARE\\";
	if (m_architecture == APPLICATION_ARCHITECTURE_X86_32)
	{
		key += "Wow6432Node\\";
	}
	key += "Microsoft\\";
	key += (m_isExpress ? "VCExpress" : "VisualStudio");
	key += "\\" + QString::number(m_version) + ".0";

	QSettings expressKey(key, QSettings::NativeFormat); // NativeFormat means from Registry on Windows.
	QString value = expressKey.value("InstallDir").toString() + "../../";

	FilePath path(value.toStdWString());
	if (path.exists())
	{
		return path;
	}

	return FilePath();
}
