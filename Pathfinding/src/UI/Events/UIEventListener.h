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
