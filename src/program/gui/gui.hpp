/**
 * @file src/program/gui/gui.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2 for MinGW GCC
 * Used compiler: GNU GCC
 */

#ifndef gui_h
#define gui_h

#include <SFML/Graphics.hpp>
#include <vector>
#include "../funcs/funcs.hpp"
#include "../game/item/item.hpp"

namespace rr {

    class Button;
    class Checkbox;
    class Image;
    class Item;
    class Slot;
    class Text;
    class Window;

/// Abstract class for all the GUI components
    class Component {
    private:
        Component* parentComponent;
    public:
    /// Virtual destructor
        virtual ~Component() {}

    /// Method telling if this component is touched by the mouse cursor
        virtual bool         containsMouseCursor(sf::RenderWindow&) = 0;

    /// Returns the current component being an instance of class Text
        virtual Text*        getText            ()                  = 0;

    /// Method drawing the component on the screen
        virtual void         draw               (sf::RenderWindow&) = 0;

    /// Sets the component's body's position
        virtual void         setPosition        (sf::Vector2f)      = 0;

    /// Sets the component's body's size
        virtual void         setSize            (sf::Vector2f)      = 0;

    /// Returns the component's body's position
        virtual sf::Vector2f getPosition        ()                  = 0;

    /// Returns the component's body's size
        virtual sf::Vector2f getSize            ()                  = 0;

    /// Sets the component's parent component
        void                 setParentComponent (Component* p) { parentComponent = p; }

    /// Returns the component's parent component
        Component*           getParentComponent ()             { return parentComponent; }
    };

/// Class for an internal window component which also can be a component of another internal window component
    class Window :public Component {
    private:
        sf::RectangleShape      body;
        std::vector<Component*> components;
        Text*                   header;
        bool                    visible;
    public:
         Window(sf::String head, sf::Vector2f size, sf::Vector2f position, sf::Color = sf::Color(128, 128, 128));
        ~Window();

    /// Adds a given component to the internal window
        void         addComponent      (Component*, bool attached);

    /// Sets the internal window visible or not, depending on the value of the given argument
        void         setVisible        (bool);

        void         setPosition       (sf::Vector2f pos)   override { body.setPosition(pos); }
        void         setSize           (sf::Vector2f siz)   override { body.setSize(siz); }
        void         draw              (sf::RenderWindow&)  override;

    /// Method telling if the internal window is visible
        bool         isVisible         ()                            { return visible; }

        sf::Vector2f getSize           ()                   override { return body.getSize(); }
        sf::Vector2f getPosition       ()                   override { return body.getPosition(); }

    /// Returns the internal window's component of a given type and index
        template<typename T>
        T*           getComponent      (unsigned index)              { if (std::is_base_of<Component, T>::value) {
                                                                          for (unsigned i=0; i<components.size(); i++) {
                                                                              if (instanceof < T, Component>(components[i])) {
                                                                                  if (index-- == 0) return (T*)components[i];
                                                                              }
                                                                          }
                                                                      } else {
                                                                          puts("element of given type not found");
                                                                          return nullptr;
                                                                      }
                                                                      puts("element with a given index not found");
                                                                      return nullptr;
                                                                  }

        bool         containsMouseCursor(sf::RenderWindow&) override { return false; }
        Text*        getText()                              override { return header; }
    };

/// Class for a vertical or a horizontal bar component representing any value you assign it to
    class Bar :public Component {
    private:
        sf::RectangleShape border;
        sf::RectangleShape bar;
        sf::Vector2f       position;
    public:
        enum Plain {
            HORIZONTAL,
            VERTICAL
        };
         Bar(Plain, int max_length, sf::Color, sf::Vector2f pos);
        ~Bar();

        void         setPosition        (sf::Vector2f)      override;
        void         setSize            (sf::Vector2f)      override;
        void         draw               (sf::RenderWindow&) override;

        sf::Vector2f getPosition        ()                  override { return border.getPosition(); }
        sf::Vector2f getSize            ()                  override { return border.getSize(); }

        bool         containsMouseCursor(sf::RenderWindow&) override { return false; }
        virtual      Text* getText      ()                  override { return nullptr; }
    };

/// Class for a button component which by being clicked can cause any action you assign to it
    class Button :public Component {
    protected:
        sf::Color          color;
        sf::RectangleShape body;
        Image*             image;
        Text*              text;
    public:
         Button(sf::Vector2f position, sf::String, unsigned chsize, sf::Color = sf::Color::White);
        ~Button();

        bool         containsMouseCursor(sf::RenderWindow&) override;
        Text*        getText            ()                  override { return text; }
        sf::Vector2f getPosition        ()                  override { return body.getPosition(); }
        sf::Vector2f getSize            ()                  override { return body.getSize(); }
        void         setPosition        (sf::Vector2f)      override;
        void         draw               (sf::RenderWindow&) override;

        void         setSize            (sf::Vector2f)      override {}
    };

/// Class for a checkbox component which can be checked or unchecked, depending on the parity of the number of clicks performed on it
    class Checkbox :public Component {
    private:
        sf::Color          color;
        sf::RectangleShape body;
        sf::Vector2f       position;
        Image*             image;
        Text*              text;
        bool               checked;
    public:
         Checkbox(sf::Vector2f pos, sf::String txt, int chsize, sf::Color = sf::Color(110, 110, 110, 128));
        ~Checkbox();

    /// Sets the checkbox checked or not, depending on the value of the given argument
        void         check(bool b);

        void         draw               (sf::RenderWindow& rw) override;
        void         setPosition        (sf::Vector2f)         override;

        bool         containsMouseCursor(sf::RenderWindow&)    override;
        sf::Vector2f getPosition        ()                     override { return body.getPosition(); }
        sf::Vector2f getSize            ()                     override { return body.getSize(); }

    /// Method telling if the checkbox is checked
        bool         isChecked          ()                              { return checked; }

        Text*        getText            ()                     override { return text; }

        void         setSize            (sf::Vector2f)         override {}
    };

/// Class for an image component which can be loaded from a file
    class Image :public Component {
    private:
        sf::Sprite      body;
        int             icn;
    public:
         Image(sf::Vector2f position, int iconSize, unsigned index);
        ~Image();

        void          setPosition         (sf::Vector2f)      override;
        void          setSize             (sf::Vector2f)      override;

    /// Method changing the image's index
        void          change              (unsigned index);

    /// Method changing the image's body and texture
        void          change              (sf::Sprite, sf::Texture);

    /// Method scaling the body's size
        void          scale               (sf::Vector2f);

    /// Method painting the body to a given color
        void          paint               (sf::Color);

        void          draw                (sf::RenderWindow&) override;

    /// Returns the image's body
        sf::Sprite    getBody             ()                           { return body; }

        sf::Vector2f  getPosition         ()                  override { return body.getPosition(); }
        sf::Vector2f  getSize             ()                  override { return sf::Vector2f(body.getGlobalBounds().width, body.getGlobalBounds().height); }

        virtual bool  containsMouseCursor (sf::RenderWindow&) override { return false; }
        virtual Text* getText             ()                  override { return nullptr; }
    };

/// Class for a slider component
    class Slider :public Component {
    public:
        enum Plain {
            HORIZONTAL,
            VERTICAL
        };
    private:
        sf::RectangleShape border;
        sf::Vector2f       valueLimit;
        Button*            indicator;
        Button*            bLeft;
        Button*            bRight;
        Text*              label;
        Plain              plain;
        float              value;
    public:
         Slider(Plain, sf::Vector2f position, sf::Vector2f size, sf::Vector2f min_max = sf::Vector2f(0, 100));
        ~Slider();

        void         setPosition        (sf::Vector2f)      override;
        void         setSize            (sf::Vector2f)      override;

    /// Sets the actual value of the slider
        void         setValue           (int);
        void         draw               (sf::RenderWindow&) override;
        void         buttonEvents       (sf::RenderWindow&);

        sf::Vector2f getPosition        ()                  override { return bLeft->getPosition(); }
        sf::Vector2f getSize            ()                  override { return border.getSize(); }
        Text*        getText            ()                  override { return label; }

    /// Returns the actual value of the slider
        int          getValue           ()                           { return value; }

        virtual bool containsMouseCursor(sf::RenderWindow&) override { return false; }
    };

/// Class for a slot component which can contain any instance of the class Item
    class Slot :public Component {
    private:
        sf::Color          color;
        sf::RectangleShape body;
        sf::Vector2f       position;
        Image*             itemSkin;
        Image*             image;
        Item*              item;
        Text*              text;
        bool               hollow;
    public:
         Slot(sf::Vector2f size, sf::Vector2f pos, int icon = 0, sf::Color = sf::Color(110, 110, 110, 128));
        ~Slot();

    /// Adds an item to the slot
        bool         addItem            (double ID, int amount);

    /// Removes the item from the slot
        void         removeItem         (int);

        void         setPosition        (sf::Vector2f)      override;
        void         draw               (sf::RenderWindow&) override;

        bool         containsMouseCursor(sf::RenderWindow&) override;
        Text*        getText            ()                  override { return nullptr; }
        sf::Vector2f getPosition        ()                  override { return body.getPosition(); }
        sf::Vector2f getSize            ()                  override { return body.getSize(); }

    /// Returns the item contained in the slot
        Item*        getItem            ()                           { if (!hollow)
                                                                           return item;
                                                                           return nullptr;
                                                                     }

    /// Method telling if the slot is empty
        bool         isEmpty            ()                           { return hollow; }
        void         setSize            (sf::Vector2f) override      {}
    };

/// Class for a switch component which can contain as many options you add to it and switch between them
    class Switch :public Component {
    private:
        sf::RectangleShape      body;
        std::vector<sf::String> options;
        Button*                 left;
        Button*                 right;
        Text*                   text;
        mutable unsigned        counter;
    public:
         Switch(sf::Vector2f size, sf::Vector2f position);
        ~Switch();

        void                 setPosition        (sf::Vector2f)      override;
        void                 setSize            (sf::Vector2f)      override;

    /// Method for handling the button events
        void                 buttonEvents       (sf::RenderWindow&);

    /// Adds an option to the switch
        void                 addOption          (sf::String);

    /// Sets the current option
        void                 setCurrentOption   (sf::String);

        void                 draw               (sf::RenderWindow&) override;

    /// Returns the current option
        sf::String           getCurrentOption   ()                           { return options[counter]; }
        virtual sf::Vector2f getPosition        ()                  override { return left->getPosition(); }
        virtual sf::Vector2f getSize            ()                  override { return body.getSize(); }

        virtual bool         containsMouseCursor(sf::RenderWindow&) override { return false; }
        virtual Text*        getText            ()                  override { return text; }
    };

/// A class for a text component
    class Text :public Component {
    private:
        sf::Text text;
    public:
         Text(sf::String, sf::Font&, unsigned chsize = 30, sf::Color = sf::Color::White);
         Text(sf::Vector2f position, sf::String, sf::Font&, unsigned chsize = 30, sf::Color = sf::Color::White);
        ~Text();

        void          setPosition        (sf::Vector2f)      override;

    /// Sets the text's character size
        void          setCharacterSize   (unsigned);

    /// Sets the text's color
        void          setColor           (sf::Color);

    /// Sets the text's string
        void          setString          (sf::String);

    /// Sets the text's font
        void          setFont            (sf::Font);

        sf::Vector2f  getSize            ()                  override { return sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height); }
        sf::Vector2f  getPosition        ()                  override { return text.getPosition(); }

    /// Returns the text's character size
        int           getCharacterSize   ()                           { return text.getCharacterSize(); }

    /// Returns the text's color
        sf::Color     getColor           ()                           { return text.getColor(); }

    /// Returns the text's string
        sf::String    getString          ()                           { return text.getString(); }

        void          draw               (sf::RenderWindow&) override;

        virtual bool  containsMouseCursor(sf::RenderWindow&) override { return false; }
        virtual Text* getText            ()                  override { return this; }
        void          setSize            (sf::Vector2f)      override {}
    };

}

#endif // gui_h
