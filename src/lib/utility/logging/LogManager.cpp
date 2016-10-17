#include "utility/logging/LogManager.h"

#include <algorithm>

#include "utility/logging/LogMessage.h"
#include "utility/logging/logging.h"
#include "utility/Version.h"

std::shared_ptr<LogManager> LogManager::createInstance()
{
	if (s_instance.use_count() == 0)
	{
		s_instance = std::shared_ptr<LogManager>(new LogManager());
	}
	return s_instance;
}

std::shared_ptr<LogManager> LogManager::getInstance()
{
	return s_instance;
}

void LogManager::destroyInstance()
{
	s_instance.reset();
}

LogManager::~LogManager()
{
}

void LogManager::setLoggingEnabled(bool enabled)
{
	m_loggingEnabled = enabled;
	if (m_loggingEnabled)
	{
		LOG_INFO("Enabled logging for Coati " + Version::getApplicationVersion().toDisplayString());
	}
}

void LogManager::addLogger(std::shared_ptr<Logger> logger)
{
	m_logManagerImplementation.addLogger(logger);
}

void LogManager::removeLogger(std::shared_ptr<Logger> logger)
{
	m_logManagerImplementation.removeLogger(logger);
}

void LogManager::removeLoggersByType(const std::string& type)
{
	m_logManagerImplementation.removeLoggersByType(type);
}

void LogManager::clearLoggers()
{
	m_logManagerImplementation.clearLoggers();
}

int LogManager::getLoggerCount() const
{
	return m_logManagerImplementation.getLoggerCount();
}

void LogManager::logInfo(
	const std::string& message,
	const std::string& file,
	const std::string& function,
	const unsigned int line
)
{
	if (m_loggingEnabled)
	{
		m_logManagerImplementation.logInfo(message, file, function, line);
	}
}

void LogManager::logWarning(
	const std::string& message,
	const std::string& file,
	const std::string& function,
	const unsigned int line
)
{
	if (m_loggingEnabled)
	{
		m_logManagerImplementation.logWarning(message, file, function, line);
	}
}

void LogManager::logError(
	const std::string& message,
	const std::string& file,
	const std::string& function,
	const unsigned int line
)
{
	if (m_loggingEnabled)
	{
		m_logManagerImplementation.logError(message, file, function, line);
	}
}

std::shared_ptr<LogManager> LogManager::s_instance;

LogManager::LogManager()
	: m_loggingEnabled(false)
{
}
