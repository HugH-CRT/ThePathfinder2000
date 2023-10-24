/**
* @file logger.h
* @brief
* 
* @author hugo.carricart@ynov.com	
* 
* @copyright TeamRandom (c) 2023
* @version 0.1
* 
* @date 21/10/2023
*/
#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <filesystem>
#include <string>
#include <map>

#define TEMP_PATH std::filesystem::temp_directory_path().generic_string()


typedef enum 
{
	SYS_NONE = -1,
	SYS_DEBUG = 0,
	SYS_INFO = 1,
	SYS_WARN = 2,
	SYS_ERROR = 3,
	SYS_CRITICAL = 4,
} LOGGER_MESSAGE_TYPE;

namespace Logger
{
	class Log
	{

	public:

		Log();
		explicit Log(std::string path);
		~Log();

		void debug(std::string content);
		void info(std::string content);
		void warning(std::string content);
		void error(std::string content);
		void critical(std::string content);
		void custom(std::string content, LOGGER_MESSAGE_TYPE type);

		void setConsoleLog_ON();
		void setConsoleLog_OFF();

	private:

		void addLog(const LOGGER_MESSAGE_TYPE& type, const std::string& logString);
		void addConsoleLog(const LOGGER_MESSAGE_TYPE& type, const std::string& logString);

		void setupLoggerFile();
		void initLoggerMessageTypeMapper();
		void setPrefixLine();

		std::string prefixLine;

		std::string logger_filepath = "";
		std::string logger_filename = "";

		bool b_console_log = false;

		std::map<LOGGER_MESSAGE_TYPE, std::string> loggerMessageTypeMapper;
	};

	void debug(std::string content);
	void info(std::string content);
	void warning(std::string content);
	void error(std::string content);
	void critical(std::string content);
	void custom(std::string content, LOGGER_MESSAGE_TYPE type);

	void setConsoleLog_ON();
	void setConsoleLog_OFF();

	static bool withConsoleLog = false;
}

#endif /* __LOGGER_H__ */