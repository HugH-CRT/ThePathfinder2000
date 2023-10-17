/**
* @file macro.h
* @brief 
* 
* @author hugo.carricart@ynov.com 
* 
* @copyright TeamRandom (c) 2023
* @version 0.1
* 
* @date 12/10/2023
*/

#define DELETE_PTR(ptr) if(ptr != nullptr) { delete ptr; ptr = nullptr; }
