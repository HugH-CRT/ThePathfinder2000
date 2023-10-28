/**
* @file c_path.h
* @brief  
*
* @authors yoan.laurain@ynov.com // hugo.carricart@ynov.com // kritofer.ledoux@ynov.com
*
* @copyright TeamRandom (c) 2023
* @version 1.0.0
* @date 28/10/2023
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
	std::string ProjectDir();
}

#endif /* __C_PATH_H__ */