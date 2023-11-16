#ifndef UI_CHECKBOX_H
#define UI_CHECKBOX_H

#include "UI/UIElement.h"
#include "UI/UIElements/UIText.h"
#include "UIImage.h"
#include "UI/Events/UIEvent.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Font.hpp"
#include <memory>
#include <string>
#include <functional>

class UICheckbox : public UIElement, public UIEvent
{
public:
	explicit UICheckbox(sf::Vector2f size);
	UICheckbox(UIElement& parent, sf::Vector2f size, std::string& name);
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
