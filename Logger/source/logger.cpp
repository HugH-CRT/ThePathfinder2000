/**
* @file logger.cpp
* @brief  
*
* @authors yoan.laurain@ynov.com // hugo.carricart@ynov.com // kritofer.ledoux@ynov.com
*
* @copyright TeamRandom (c) 2023
* @version 1.0.0
* @date 28/10/2023
*/
#include "logger.h"

#include <iostream>
#include <fstream>

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

/**
* @fn Log
* @brief Default constructor
*/
Logger::Log::Log()
{
	this->setupLoggerFile();
	this->initLoggerMessageTypeMapper();
	setConsoleLog_OFF();
}

/**
* @fn Log
* @brief Second constructor : precise file path
* @param path : std::string
*/
Logger::Log::Log(std::string path)
{
	this->logger_filepath = path;

	this->setupLoggerFile();
	this->initLoggerMessageTypeMapper();
	setConsoleLog_OFF();
}

/**
* @fn ~Log
* @brief Default destructor
*/
Logger::Log::~Log()
{
	//
}

/**
* @fn debug
* @brief Add debug log type. 
* @param content : std::string
*/
void Logger::Log::debug(std::string content)
{
	setPrefixLine();
	addConsoleLog(LOGGER_MESSAGE_TYPE::SYS_DEBUG, content);
	addLog(LOGGER_MESSAGE_TYPE::SYS_DEBUG, content);
}

/**
* @fn info
* @brief Add info log type.
* @param content : std::string
*/
void Logger::Log::info(std::string content)
{
	setPrefixLine();
	addConsoleLog(LOGGER_MESSAGE_TYPE::SYS_INFO, content);
	addLog(LOGGER_MESSAGE_TYPE::SYS_INFO, content);
}

/**
* @fn warning
* @brief Add warning log type.
* @param content : std::string
*/
void Logger::Log::warning(std::string content)
{
	setPrefixLine();
	addConsoleLog(LOGGER_MESSAGE_TYPE::SYS_WARN, content);
	addLog(LOGGER_MESSAGE_TYPE::SYS_WARN, content);
}

/**
* @fn error
* @brief Add error log type.
* @param content : std::string
*/
void Logger::Log::error(std::string content)
{
	setPrefixLine();
	addConsoleLog(LOGGER_MESSAGE_TYPE::SYS_ERROR, content);
	addLog(LOGGER_MESSAGE_TYPE::SYS_ERROR, content);
}

/**
* @fn critical
* @brief Add critical log type.
* @param content : std::string
*/
void Logger::Log::critical(std::string content)
{
	setPrefixLine();
	addConsoleLog(LOGGER_MESSAGE_TYPE::SYS_CRITICAL, content);
	addLog(LOGGER_MESSAGE_TYPE::SYS_CRITICAL, content);
}

/**
* @fn custom
* @brief Add custom log type. Need to precise logger message type. 
* @param content : std::string 
* @param type : LOGGER_MESSAGE_TYPE 
*/
void Logger::Log::custom(std::string content, LOGGER_MESSAGE_TYPE type)
{
	setPrefixLine();
	addConsoleLog(type, content);
	addLog(type, content);
}

/**
* @fn setConsoleLog_ON
* @brief Set log string ON in output console. 
*/
void Logger::Log::setConsoleLog_ON()
{
	b_console_log = true;
}

/**
* @fn setConsoleLog_OFF
* @brief Set log string OFF in output console.
*/
void Logger::Log::setConsoleLog_OFF()
{
	b_console_log = false;
}

/**
* @fn addLog
* @brief Add log string in file. 
* @param type : LOGGER_MESSAGE_TYPE&
* @param logString : std::string&
*/
void Logger::Log::addLog(const LOGGER_MESSAGE_TYPE& type, const std::string& logString)
{
	std::string logType = loggerMessageTypeMapper[type];

	std::string filePath = logger_filepath + logger_filename;

	if (!std::filesystem::exists(filePath)) {}

	std::ofstream file;
	file.open(filePath, std::ios_base::app);
	file << prefixLine << " [" << logType << "] " << logString;
	file << "\n";
	file.close();

}

/**
* @fn addConsoleLog
* @brief Add log string in console output.
* @param type : LOGGER_MESSAGE_TYPE&
* @param logString : std::string&
*/
void Logger::Log::addConsoleLog(const LOGGER_MESSAGE_TYPE& type, const std::string& logString)
{
	if (b_console_log == true)
	{
		std::string logType = loggerMessageTypeMapper[type];
		std::cout << prefixLine << " [" << logType << "] " << logString << "\n";
	}
}

/**
* @fn setupLoggerFile
* @brief Setup logger filepath and filename
*/
void Logger::Log::setupLoggerFile()
{
	// Path : temp_
	logger_filepath = std::filesystem::temp_directory_path().generic_string();

	// Filename 
	logger_filename = "ThePathfinder2000_"+CURRENT_DATE;
	std::replace(logger_filename.begin(), logger_filename.end(), '/', '_');
}

/**
* @fn initLoggerMessageTypeMapper
* @brief Setup loggerMessageTypeMapper. 
* @details : Enum LOGGER_MESSAGE_TYPE -> std::string
*/
void Logger::Log::initLoggerMessageTypeMapper()
{
	loggerMessageTypeMapper[LOGGER_MESSAGE_TYPE::SYS_CRITICAL] = "CRITICAL";
	loggerMessageTypeMapper[LOGGER_MESSAGE_TYPE::SYS_ERROR] = "ERROR";
	loggerMessageTypeMapper[LOGGER_MESSAGE_TYPE::SYS_WARN] = "WARNING";
	loggerMessageTypeMapper[LOGGER_MESSAGE_TYPE::SYS_INFO] = "INFO";
	loggerMessageTypeMapper[LOGGER_MESSAGE_TYPE::SYS_DEBUG] = "DEBUG";
	loggerMessageTypeMapper[LOGGER_MESSAGE_TYPE::SYS_NONE] = "NONE";
}

/**
* @fn setPrefixLine
* @brief Set prefixLine for log string.
* @details Add CURRENT_DATE and CURRENT_TIME
*/
void Logger::Log::setPrefixLine()
{
	prefixLine = "[" + CURRENT_DATE + " - " + CURRENT_TIME + "] ";
}

/**
* @fn debug
* @brief Add debug log type.
* @details NAMESPACE Logger
* @param content : std::string
*/
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

/**
* @fn info
* @brief Add info log type.
* @details NAMESPACE Logger
* @param content : std::string
*/
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

/**
* @fn warning
* @brief Add warning log type.
* @details NAMESPACE Logger
* @param content : std::string
*/
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

/**
* @fn error
* @brief Add error log type.
* @details NAMESPACE Logger
* @param content : std::string
*/
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

/**
* @fn critical
* @brief Add critical log type.
* @details NAMESPACE Logger
* @param content : std::string
*/
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

/**
* @fn custom
* @brief Add custom log type. Need to precise logger message type.
* @details NAMESPACE Logger
* @param content : std::string
* @param type : LOGGER_MESSAGE_TYPE
*/
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

/**
* @fn setConsoleLog_ON
* @details NAMESPACE Logger
* @brief Set log string ON in output console.
*/
void Logger::setConsoleLog_ON()
{
	withConsoleLog = true;
}

/**
* @fn setConsoleLog_OFF
* @details NAMESPACE Logger
* @brief Set log string OFF in output console.
*/
void Logger::setConsoleLog_OFF()
{
	withConsoleLog = false;
}
