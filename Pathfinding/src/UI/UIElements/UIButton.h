#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include <functional>

#include "UIImage.h"
#include "UI/UIElement.h"
#include "UI/Events/UIEvent.h"

class UIButton final : public UIElement, public UIEvent
{
public:
	explicit UIButton(sf::Vector2f size);
	UIButton(UIElement& parent, sf::Vector2f size, std::string& name);

	virtual ~UIButton() override;

	virtual void SetPosition(float positionX, float positionY) override;
	virtual void SetScale(float scaleX, float scaleY) override;
	virtual void Draw(sf::RenderWindow& window) const override;

	void SetBackgroundColor(sf::Color& color) const;
	void SetBackgroundImage(sf::Texture& texture);

	template<typename C>
	void BindOnClick(C* ctx, void(C::* fn)());
	void HandleEvents(sf::Event& event, sf::RenderWindow& window) override;

private:
	class UIImage* _backgroundImage;
	std::function<void()> OnClickEvent;
};

template <typename C>
void UIButton::BindOnClick(C* ctx, void(C::* fn)())
{
	OnClickEvent = std::bind_front(fn, ctx);
}

#endif /* UI_BUTTON_H */
