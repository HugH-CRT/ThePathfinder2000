/**
* @file UICHeckBox.h
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

#ifndef UI_CHECKBOX_H
#define UI_CHECKBOX_H

#include "UIElements/UIElement.h"
#include "UIElements/UI_Text/UIText.h"
#include "UIElements/UI_Image/UIImage.h"
#include "Events/UIEvent.h"

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Font.hpp"

#include <memory>
#include <string>
#include <functional>

class UICheckbox : public UIElement, public UIEvent
{
public:
	explicit UICheckbox(sf::Vector2f size);
	explicit UICheckbox(UIElement* parent, sf::Vector2f size, std::string& name);

	~UICheckbox() override;

	void Init(sf::Texture& uncheckedTexture, sf::Texture& checkedTexture, std::string text, sf::Font& font);
	void InitTexture(sf::Texture& uncheckedTexture, sf::Texture& checkedTexture);
	UIText& GetText();
	UIImage& GetSprite();

	void SetPosition(float positionX, float positionY) override;
	void SetScale(float scaleX, float scaleY) override;
	void Draw(sf::RenderWindow& window) const override;

	template<typename C>
	void BindOnClick(C* ctx, void(C::* fn)());
	void HandleEvents(sf::Event& event, sf::RenderWindow& window) override;

	void SwitchState();

private:
	std::unique_ptr<UIText> _text;
	std::unique_ptr<UIImage> _sprite;
	sf::Texture _uncheckedTexture;
	sf::Texture _checkedTexture;
	bool _isChecked = false;

	std::function<void()> OnClickEvent;
};

template <typename C>
void UICheckbox::BindOnClick(C* ctx, void(C::* fn)())
{
	if (!OnClickEvent)
	{
		OnClickEvent = std::bind_front(fn, ctx);
	}
}

#endif /* UI_CHECKBOX_H */
