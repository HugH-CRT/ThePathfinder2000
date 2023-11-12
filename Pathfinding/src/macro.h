/**
* @file macro.h
* @brief 
* 
* @author yoan.laurain@ynov.com // hugo.carricart@ynov.com // kritofer.ledoux@ynov.com
*
* @copyright TeamRandom (c) 2023
* @version 0.1
*
* @date 21/10/2023
*/
#define DELETE_PTR(ptr) if(ptr != nullptr) { delete ptr; ptr = nullptr; }