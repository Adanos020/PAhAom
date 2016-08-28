/**
 * @file src/program/game/item/Food.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef ITEM_FOOD_HPP
#define ITEM_FOOD_HPP

#include "Item.hpp"

namespace rr
{

    class Food : public Item
    {
    private: ////////////////////////////////////////////////////////////////////////
             /// \brief Initializes the food.
             ////////////////////////////////////////////////////////////////////////
     virtual void initialize() override;
    
    public:  enum Type
             {
                 MEAT,
                 SANDVICH,
                 APPLE,
                 BEER,
                 HOT_DOG,
                 HAMBURGER,
                 BAGUETTE
             };

             ////////////////////////////////////////////////////////////////////////
             /// \brief Regular constructor.
             ////////////////////////////////////////////////////////////////////////
             Food(Type = MEAT, int amount = 1, sf::Vector2i position = sf::Vector2i(0, 0));

             ////////////////////////////////////////////////////////////////////////
             /// \brief Copy constructor.
             ////////////////////////////////////////////////////////////////////////
             Food(Food const&);

             ////////////////////////////////////////////////////////////////////////
             /// \brief Creates an exact copy of the food.
             ////////////////////////////////////////////////////////////////////////
             virtual Entity* clone() const override { return new Food(*this); }

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the food's type.
             ///
             /// The possible values are:
             /// - MEAT
             /// - SANDVICH
             /// - APPLE
             /// - BEER
             /// - HOT_DOG
             /// - HAMBURGER
             /// - BAGUETTE
             ////////////////////////////////////////////////////////////////////////
             Type getType() { return type_; }
         
             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the food's name.
             ////////////////////////////////////////////////////////////////////////
             virtual sf::String getName() const override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Returns the food's description.
             ////////////////////////////////////////////////////////////////////////
             virtual sf::String getDescription() const override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Reads the food from the file.
             ////////////////////////////////////////////////////////////////////////
             virtual std::ifstream& operator<<(std::ifstream&) override;

             ////////////////////////////////////////////////////////////////////////
             /// \brief Saves the food to the file.
             ////////////////////////////////////////////////////////////////////////
             virtual std::ofstream& operator>>(std::ofstream&) override;

    private: Type type_;
    };

}

#endif // ITEM_FOOD_HPP
