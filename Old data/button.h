#include <iostream>
#include <math.h>
#include <stdio.h>
#include<bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <stdio.h>
using namespace std;

namespace style
    {
        enum
        {
            none = 0,
            save = 1,
            cancel = 2,
            clean = 3,
        };
    };

    namespace state
    {
        enum
        {
            normal = 0,
            hovered = 1,
            clicked = 2
        };
    };




class button : public sf::Drawable{
    public:
        button();
        button(std::string s, sf::Vector2f position, sf::Vector2f size);
        void setColorTextNormal(sf::Color text){m_textNormal = text;};
        void setColorNormal(sf::Color bgNormal){m_bgNormal = bgNormal;};
        void setPosition(sf::Vector2f position){m_position = position;};
        void setSize(unsigned int size);
        void setText(std::string s)
        {
            m_text.setString(s);
            m_shadow = m_text;
        };
        sf::Vector2f getPosition(){return m_position;};
        virtual void update(sf::Event& e, sf::RenderWindow& curr_window, sf::RenderWindow& console_window);
        virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;
        void draw_it(sf::RenderWindow& window);
    public:
        sf::Color m_bgNormal;
        sf::Color m_textNormal;
        sf::Vector2f m_size;
        sf::Vector2f m_position;
        sf::Uint32 m_btnstate;
        
        sf::RectangleShape m_button;
        sf::Font m_font;
        unsigned int m_fontSize;
        sf::Text m_text;
        sf::Text m_shadow;
};




button::button(std::string s, sf::Vector2f position, sf::Vector2f size)
{
    //set position
    m_position = position;
    m_size = size;
    
    //set initial state
    m_btnstate = state::normal;

    //set button style
    

    m_textNormal = sf::Color(255,200,155);
    m_bgNormal = sf::Color(55,230,155,100);
    
    //set up text
    m_text.setString(s);
    // std::cout<<m_text.getGlobalBounds().width<<" , "<<m_text.getGlobalBounds().height<<"\n";
    m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
    m_text.setColor(m_textNormal);

    //set some defauts
    
    
    // m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, m_text.getGlobalBounds().height * 1.5f);

    m_button = sf::RectangleShape(m_size);

    m_button.setOrigin(m_size.x/1.5, m_size.y/1.5);
    m_button.setFillColor(m_bgNormal);
    m_button.setPosition(m_position);

    sf::Vector2f textPosition = sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_button.getGlobalBounds().height/4);

    m_text.setPosition(textPosition);

    // m_shadow.setFont(font);
    m_shadow = m_text;
    m_shadow.setOrigin(m_shadow.getGlobalBounds().width/2, m_shadow.getGlobalBounds().height/2);
    m_shadow.setPosition(m_text.getPosition().x + 3.f, m_text.getPosition().y + 3.f);
}


void button::setSize(unsigned int size)
{
    m_text.setCharacterSize(m_fontSize);
    m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
    m_shadow.setCharacterSize(m_fontSize);
    m_shadow.setOrigin(m_shadow.getGlobalBounds().width/2, m_shadow.getGlobalBounds().height/2);
    m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, (m_text.getGlobalBounds().height + m_text.getGlobalBounds().height) * 1.5f);
    m_button = sf::RectangleShape(m_size);
}



void button::draw(sf::RenderTarget& target,sf::RenderStates states) const
{   
    target.draw(m_button, states);
    target.draw(m_shadow, states);
    target.draw(m_text, states);
    // cout<<"in draw\n";
    // switch(m_style)
    // {
    //     case gui::style::none:
    //     {
            
    //     }
    //     break;

    //     case gui::style::save:
    //     {
    //         target.draw(m_button, states);
    //         target.draw(m_shadow, states);
    //         target.draw(m_text, states);
    //     }
    //     break;

    //     case gui::style::cancel:
    //     {
    //         target.draw(m_button, states);
    //         target.draw(m_shadow, states);
    //         target.draw(m_text, states);
    //     }
    //     break;

    //     case gui::style::clean:
    //     {
    //         target.draw(m_button, states);
    //         target.draw(m_shadow, states);
    //         target.draw(m_text, states);
    //     }
    //     break;

    //     default:
    //         break;
    // }
}

void button::draw_it(sf::RenderWindow& window){
    sf::RectangleShape S(sf::Vector2f(120, 50));
    window.draw(S);
    window.draw(m_button);
}


class manualButton: public button{  
    public:
    manualButton(std::string s, sf::Vector2f position, sf::Vector2f size){
        button(s,position,size);
    }

    void update(sf::Event& e, sf::RenderWindow& curr_window, sf::RenderWindow& console_window)
    {
        // m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, m_text.getGlobalBounds().height * 1.75f);
        // cout<<m_size.x<<" "<<m_size.y<<" size\n";
        m_button = sf::RectangleShape(m_size);
        m_button.setOrigin(m_size.x/1.5, m_size.y/1.5);
        // m_button.setFillColor(m_bgNormal);
        m_button.setPosition(m_position);
        m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
        sf::Vector2f textPosition = sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_button.getGlobalBounds().height/4);
        m_text.setPosition(textPosition);
        m_text.setColor(m_textNormal);
        m_shadow.setOrigin(m_shadow.getGlobalBounds().width/2, m_shadow.getGlobalBounds().height/2);
        m_shadow.setPosition(m_text.getPosition().x + 3.f, m_text.getPosition().y + 3.f);
        m_shadow.setColor(sf::Color(0,0,0));

        //perform updates for settings from user
        

        //perform updates for user mouse interactions
        sf::Vector2i m_mousePosition = sf::Mouse::getPosition(curr_window);

        bool mouseInButton =    m_mousePosition.x >= m_button.getPosition().x - m_button.getGlobalBounds().width/2
                                && m_mousePosition.x <= m_button.getPosition().x + m_button.getGlobalBounds().width/2
                                && m_mousePosition.y >= m_button.getPosition().y - m_button.getGlobalBounds().height/2
                                && m_mousePosition.y <= m_button.getPosition().y + m_button.getGlobalBounds().height/2;

        
        if(e.type == sf::Event::MouseMoved)
        {
            if(mouseInButton)
            {
                std::cout<<"Hoverered"<<endl;
            }
        }

        if (e.type == sf::Event::MouseButtonPressed)
        {
            switch(e.mouseButton.button)
            {
            case sf::Mouse::Left:
            {
                std::cout<<m_mousePosition.x<<" "<<m_mousePosition.y<<"\n";
                if(mouseInButton)
                {   
                    std::cout<<"Clicked\n";
                    console_window.create(sf::VideoMode(500, 500), "SFML works!");
                }
            }
            break;
            }
        }

        // if (e.type == sf::Event::MouseButtonReleased)
        // {
        //     switch(e.mouseButton.button)
        //     {
        //     case sf::Mouse::Left:
        //     {
        //         if(mouseInButton)
        //         {
        //             m_btnstate = gui::state::hovered;
        //         }

        //         else
        //         {
        //             m_btnstate = gui::state::normal;
        //         }
        //     }
        //     }
        // }

        // switch(m_btnstate)
        // {
        // case gui::state::normal:
        // {
        //     m_button.setFillColor(m_bgNormal);
        //     m_text.setColor(m_textNormal);
        // }
        // break;

        // case gui::state::hovered:
        // {
        //     m_button.setFillColor(m_bgHover);
        //     m_text.setColor(m_textHover);
        // }
        // break;

        // case gui::state::clicked:
        // {
        //     m_button.setFillColor(m_bgClicked);
        //     m_text.setColor(m_textClicked);
        // }
        // break;
        // }
    }

};