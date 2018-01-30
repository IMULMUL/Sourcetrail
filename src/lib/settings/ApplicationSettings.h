#ifndef APPLICATION_SETTINGS_H
#define APPLICATION_SETTINGS_H

#include <memory>

#include "settings/Settings.h"

class TimeStamp;
class Version;

class ApplicationSettings
	: public Settings
{
public:
	static std::shared_ptr<ApplicationSettings> getInstance();

	static const size_t VERSION;

	ApplicationSettings();
	~ApplicationSettings();

	bool load(const FilePath& filePath);

	bool operator==(const ApplicationSettings& other) const;

	int getMaxRecentProjectsCount() const;

	// application
	std::string getFontName() const;
	void setFontName(const std::string& fontName);

	int getFontSize() const;
	void setFontSize(int fontSize);

	std::string getTextEncoding() const;
	void setTextEncoding(const std::string& textEncoding);

	FilePath getColorSchemePath() const;
	void setColorSchemePath(const FilePath& colorSchemePath);

	int getFontSizeMax() const;
	void setFontSizeMax(const int fontSizeMax);

	int getFontSizeMin() const;
	void setFontSizeMin(const int fontSizeMin);

	int getFontSizeStd() const;
	void setFontSizeStd(const int fontSizeStd);

	bool getUseAnimations() const;
	void setUseAnimations(bool useAnimations);

	bool getShowBuiltinTypesInGraph() const;
	void setShowBuiltinTypesInGraph(bool showBuiltinTypes);

	int getWindowBaseWidth() const;
	int getWindowBaseHeight() const;

	float getScrollSpeed() const;
	void setScrollSpeed(float scrollSpeed);

	bool getGraphControlsVisible() const;
	void setGraphControlsVisible(bool visible);

	// screen
	int getScreenAutoScaling() const;
	void setScreenAutoScaling(int autoScaling);

	float getScreenScaleFactor() const;
	void setScreenScaleFactor(float scaleFactor);

	// logging
	bool getLoggingEnabled() const;
	void setLoggingEnabled(bool loggingEnabled);

	bool getVerboseIndexerLoggingEnabled() const;
	void setVerboseIndexerLoggingEnabled(bool loggingEnabled);

	int getLogFilter() const;
	void setLogFilter(int mask);

	int getStatusFilter() const;
	void setStatusFilter(int mask);

	// indexing
	int getIndexerThreadCount() const;
	void setIndexerThreadCount(const int count);

	bool getMultiProcessIndexingEnabled() const;
	void setMultiProcessIndexingEnabled(bool enabled);

	FilePath getJavaPath() const;
	void setJavaPath(const FilePath& path);

	int getJavaMaximumMemory() const;
	void setJavaMaximumMemory(int size);

	std::vector<FilePath> getJreSystemLibraryPaths() const;
	std::vector<FilePath> getJreSystemLibraryPathsExpanded() const;
	bool setJreSystemLibraryPaths(const std::vector<FilePath>& jreSystemLibraryPaths);

	FilePath getMavenPath() const;
	void setMavenPath(const FilePath& path);

	std::vector<FilePath> getHeaderSearchPaths() const;
	std::vector<FilePath> getHeaderSearchPathsExpanded() const;
	bool setHeaderSearchPaths(const std::vector<FilePath>& headerSearchPaths);

	std::vector<FilePath> getFrameworkSearchPaths() const;
	std::vector<FilePath> getFrameworkSearchPathsExpanded() const;
	bool setFrameworkSearchPaths(const std::vector<FilePath>& frameworkSearchPaths);

	// code
	int getCodeTabWidth() const;
	void setCodeTabWidth(int codeTabWidth);

	int getCodeSnippetSnapRange() const;
	void setCodeSnippetSnapRange(int range);

	int getCodeSnippetExpandRange() const;
	void setCodeSnippetExpandRange(int range);

	bool getCodeViewModeSingle() const;
	void setCodeViewModeSingle(bool enabled);

	// user
	std::vector<FilePath> getRecentProjects() const;
	bool setRecentProjects(const std::vector<FilePath>& recentProjects);

	int getAcceptedEulaVersion() const;
	void setAcceptedEulaVersion(int version);

	std::string getUserToken() const;
	void setUserToken(std::string token);

	bool getAutomaticUpdateCheck() const;
	void setAutomaticUpdateCheck(bool automaticUpdates);

	TimeStamp getLastUpdateCheck() const;
	void setLastUpdateCheck(const TimeStamp& time);

	Version getSkipUpdateForVersion() const;
	void setSkipUpdateForVersion(const Version& version);

	std::string getUpdateDownloadUrl() const;
	void setUpdateDownloadUrl(const std::string& url);

	Version getUpdateVersion() const;
	void setUpdateVersion(const Version& version);

	bool getSeenErrorHelpMessage() const;
	void setSeenErrorHelpMessage(bool seen);

	// network
	int getPluginPort() const;
	void setPluginPort(const int pluginPort);

	int getSourcetrailPort() const;
	void setSourcetrailPort(const int sourcetrailPort);

	// controls
	int getControlsMouseBackButton() const;
	int getControlsMouseForwardButton() const;

	bool getControlsGraphZoomOnMouseWheel() const;
	void setControlsGraphZoomOnMouseWheel(bool zoomingDefault);

	// license
	std::string getLicenseString() const;
	void setLicenseString(const std::string& licenseString);

	std::string getLicenseCheck() const;
	void setLicenseCheck(const std::string& hash);

	bool getNonCommercialUse() const;
	void setNonCommercialUse(bool nonCommercialUse);

private:
	ApplicationSettings(const ApplicationSettings&);
	void operator=(const ApplicationSettings&);

	static std::shared_ptr<ApplicationSettings> s_instance;
};

#endif // APPLICATION_SETTINGS_H
