/**
* @file c_path.h
* @brief
* 
* @author hugo.carricart@ynov.com	
* 
* @copyright TeamRandom (c) 2023
* @version 0.1
* 
* @date 21/10/2023
*/
#ifndef __C_PATH_H__
#define __C_PATH_H__

#include <string>

#define DEBUG_LOG 1

/**
* @namespace C_PATH
*/
namespace C_PATH
{
	std::string TempDir();
	std::string CurrentDir();
	std::string UserDir();
	std::string DocumentDir();
}


#endif /* __C_PATH_H__ */