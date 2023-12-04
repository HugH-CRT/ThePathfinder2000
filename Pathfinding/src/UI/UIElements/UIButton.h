/**
* @file UIButton.h
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

#ifndef UI_BUTTON_H
#define UI_BUTTON_H


#include "UIImage.h"
#include "UI/UIElement.h"
#include "UI/Events/UIEvent.h"

#include <functional>

class UIButton : public UIElement, public UIEvent
{
public:
	explicit UIButton(sf::Vector2f size);
	explicit UIButton(UIElement& parent, sf::Vector2f size, std::string& name);

	~UIButton() override;

	void SetPosition(float positionX, float positionY) override;
	void SetScale(float scaleX, float scaleY) override;
	void Draw(sf::RenderWindow& window) const override;

	void SetBackgroundColor(sf::Color& color) const;
	void SetBackgroundImage(sf::Texture& texture);

	template<typename C>
	void BindOnClick(C* ctx, void(C::* fn)());
	template<typename C>
	void BindOnHover(C* ctx, void(C::* fn)());
	template<typename C>
	void BindOnUnHover(C* ctx, void(C::* fn)());
	void HandleEvents(sf::Event& event, sf::RenderWindow& window) override;

private:
	std::unique_ptr<UIImage> _backgroundImage;
	std::function<void()> OnClickEvent;
	std::function<void()> OnHoverEvent;
	std::function<void()> OnUnHoverEvent;
	bool _isHover = false;
};

template <typename C>
void UIButton::BindOnClick(C* ctx, void(C::* fn)())
{
	if(!OnClickEvent)
	{
		OnClickEvent = std::bind_front(fn, ctx);
	}
}

template <typename C>
void UIButton::BindOnHover(C* ctx, void(C::* fn)())
{
	if(!OnHoverEvent)
	{
		OnHoverEvent = std::bind_front(fn, ctx);
	}
}

template <typename C>
void UIButton::BindOnUnHover(C* ctx, void(C::* fn)())
{
	if(!OnUnHoverEvent)
	{
		OnUnHoverEvent = std::bind_front(fn, ctx);
	}
}

#endif /* UI_BUTTON_H */
