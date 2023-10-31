#include "UIElement.h"

class UIImage : public UIElement
{
public:
	explicit UIImage(UIWidget& uiContext);
	UIImage(UIWidget& uiContext, std::string name);

	virtual ~UIImage();

	virtual void Draw(sf::RenderWindow& window) const override;
};