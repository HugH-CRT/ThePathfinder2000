/**
* @file logger.cpp
* @brief
* 
* @author hugo.carricart@ynov.com
* 
* @copyright TeamRandom (c) 2023
* @version 0.1
*
* @date 21/10/2023
*/
#include "logger.h"

#include <iostream>

#include <chrono>
#include <ctime>
#include <sstream>

#define CURRENT_DATE []() { \
    auto now = std::chrono::system_clock::now(); \
    auto time = std::chrono::system_clock::to_time_t(now); \
    struct std::tm* timeinfo = std::localtime(&time); \
    std::stringstream ss; \
    ss << std::put_time(timeinfo, "%d/%m/%Y"); \
    return ss.str(); \
}()

#define CURRENT_TIME []() { \
    auto now = std::chrono::system_clock::now(); \
    auto time = std::chrono::system_clock::to_time_t(now); \
    struct std::tm* timeinfo = std::localtime(&time); \
    std::stringstream ss; \
    ss << std::put_time(timeinfo, "%H:%M:%S"); \
    return ss.str(); \
}()


Logger::Log::Log()
{
	this->setupLoggerFile();
	this->initLoggerMessageTypeMapper();
	setConsoleLog_OFF();
}

Logger::Log::Log(std::string path)
{
	this->logger_filepath = path;

	this->setupLoggerFile();
	this->initLoggerMessageTypeMapper();
	setConsoleLog_OFF();
}

Logger::Log::~Log()
{
	//
}

void Logger::Log::debug(std::string content)
{
	setPrefixLine();
	addConsoleLog(LOGGER_MESSAGE_TYPE::SYS_DEBUG, content);
	addLog(LOGGER_MESSAGE_TYPE::SYS_DEBUG, content);
}

void Logger::Log::info(std::string content)
{
	setPrefixLine();
	addConsoleLog(LOGGER_MESSAGE_TYPE::SYS_INFO, content);
	addLog(LOGGER_MESSAGE_TYPE::SYS_INFO, content);
}

void Logger::Log::warning(std::string content)
{
	setPrefixLine();
	addConsoleLog(LOGGER_MESSAGE_TYPE::SYS_WARN, content);
	addLog(LOGGER_MESSAGE_TYPE::SYS_WARN, content);
}

void Logger::Log::error(std::string content)
{
	setPrefixLine();
	addConsoleLog(LOGGER_MESSAGE_TYPE::SYS_ERROR, content);
	addLog(LOGGER_MESSAGE_TYPE::SYS_ERROR, content);
}

void Logger::Log::critical(std::string content)
{
	setPrefixLine();
	addConsoleLog(LOGGER_MESSAGE_TYPE::SYS_CRITICAL, content);
	addLog(LOGGER_MESSAGE_TYPE::SYS_CRITICAL, content);
}

void Logger::Log::custom(std::string content, LOGGER_MESSAGE_TYPE type)
{
	setPrefixLine();
	addConsoleLog(type, content);
	addLog(type, content);
}

void Logger::Log::setConsoleLog_ON()
{
	b_console_log = true;
}

void Logger::Log::setConsoleLog_OFF()
{
	b_console_log = false;
}

void Logger::Log::addLog(const LOGGER_MESSAGE_TYPE& type, const std::string& logString)
{
	std::string logType = loggerMessageTypeMapper[type];

	// Stream file

}

void Logger::Log::addConsoleLog(const LOGGER_MESSAGE_TYPE& type, const std::string& logString)
{
	if (b_console_log == true)
	{
		std::string logType = loggerMessageTypeMapper[type];
		std::cout << prefixLine << " [" << logType << "] " << logString << std::endl;
	}
}

void Logger::Log::setupLoggerFile()
{
	// Setup Logger File 

	// Path : temp_

	// Filename 
}

void Logger::Log::initLoggerMessageTypeMapper()
{
	loggerMessageTypeMapper[LOGGER_MESSAGE_TYPE::SYS_CRITICAL] = "CRITICAL";
	loggerMessageTypeMapper[LOGGER_MESSAGE_TYPE::SYS_ERROR] = "ERROR";
	loggerMessageTypeMapper[LOGGER_MESSAGE_TYPE::SYS_WARN] = "WARNING";
	loggerMessageTypeMapper[LOGGER_MESSAGE_TYPE::SYS_INFO] = "INFO";
	loggerMessageTypeMapper[LOGGER_MESSAGE_TYPE::SYS_DEBUG] = "DEBUG";
	loggerMessageTypeMapper[LOGGER_MESSAGE_TYPE::SYS_NONE] = "NONE";
}

void Logger::Log::setPrefixLine()
{
		prefixLine = "[" + CURRENT_DATE + " - " + CURRENT_TIME + "] ";
}

void Logger::debug(std::string content)
{
	Log* log = new Log;
	if (log == nullptr) { return; }

	if (withConsoleLog == true)
	{
		log->setConsoleLog_ON();
	}

	log->debug(content);	

	delete log;
	log = nullptr;
}

void Logger::info(std::string content)
{
	Log* log = new Log;
	if (log == nullptr) { return; }

	if (withConsoleLog == true)
	{
		log->setConsoleLog_ON();
	}

	log->info(content);

	delete log;
	log = nullptr;
}

void Logger::warning(std::string content)
{
	Log* log = new Log;
	if (log == nullptr) { return; }

	if (withConsoleLog == true)
	{
		log->setConsoleLog_ON();
	}

	log->warning(content);

	delete log;
	log = nullptr;
}

void Logger::error(std::string content)
{
	Log* log = new Log;
	if (log == nullptr) { return; }

	if (withConsoleLog == true)
	{
		log->setConsoleLog_ON();
	}

	log->error(content);

	delete log;
	log = nullptr;
}

void Logger::critical(std::string content)
{
	Log* log = new Log;
	if (log == nullptr) { return; }

	if (withConsoleLog == true)
	{
		log->setConsoleLog_ON();
	}

	log->critical(content);

	delete log;
	log = nullptr;
}

void Logger::custom(std::string content, LOGGER_MESSAGE_TYPE type)
{
	Log* log = new Log;
	if (log == nullptr) { return; }

	if (withConsoleLog == true)
	{
		log->setConsoleLog_ON();
	}

	log->custom(content, type);

	delete log;
	log = nullptr;
}

void Logger::setConsoleLog_ON()
{
	withConsoleLog = true;
}

void Logger::setConsoleLog_OFF()
{
	withConsoleLog = false;
}
