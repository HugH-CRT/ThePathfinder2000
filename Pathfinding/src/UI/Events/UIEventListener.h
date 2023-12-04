/**
* @file UIEventListener.h
*
* @brief
*
* @author yoan.laurain@ynov.com // hugo.carricart@ynov.com // kritofer.ledoux@ynov.com
*
* @copyright TeamRandom (c) 2023
* @version 0.1
*
* @date 21/10/2023
*/

#ifndef UI_EVENT_LISTENER_H
#define UI_EVENT_LISTENER_H

#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class UIEventListener
{
public:
	UIEventListener();
	virtual ~UIEventListener();
	virtual void HandleEvents(sf::Event& event, sf::RenderWindow& window);
};

#endif /* UI_EVENT_LISTENER_H */
