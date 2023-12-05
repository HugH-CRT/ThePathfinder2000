/**
* @file UITextField.h
*
* @brief Input text field.
*
* @author yoan.laurain@ynov.com // hugo.carricart@ynov.com // kritofer.ledoux@ynov.com
*
* @copyright TeamRandom (c) 2023
* @version 0.1
*
* @date 05/12/2023
*/

#ifndef UI_TEXTFIELD_H
#define UI_TEXTFIELD_H

#include "UIElements/UIElement.h"
#include "Events/UIEvent.h"

#include <string>
#include <functional>

/**
* @class UITextField
* @brief //
*/
class UITextField : public UIElement, public UIEvent
{
public:
    explicit UITextField(sf::Vector2f size, unsigned int maxChars = 128);
    explicit UITextField(UIElement* parent, sf::Vector2f size, std::string& name, unsigned int maxChars = 128);

    ~UITextField() override;

    void Draw(sf::RenderWindow& window) const override;
    void SetPosition(float positionX, float positionY) override;
    void SetScale(float scaleX, float scaleY) override;

    void SetNumericsOnly(bool check);
    void SetFont(sf::Font& font);
    std::string GetText() const;

    void HandleEvents(sf::Event& event, sf::RenderWindow& window) override;

private:

    void Init(void);

    unsigned int _size;
    sf::Text _drawText;
    std::string _text;
    sf::RectangleShape _rect;
    bool _hasFocus = false;
    bool _numericsOnly = false;

};

#endif /* UI_TEXTFIELD_H */
