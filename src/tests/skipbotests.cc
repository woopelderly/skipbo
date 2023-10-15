#include "../skipbo.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE( "Card" )
{
    Card test_card;

    SECTION( "Ctor" )
    {
        CHECK( Card::s_skipbo == test_card.m_value );
    }
}

TEST_CASE( "Skipbo" )
{
    Skipbo test_game;

    SECTION( "Ctor" )
    {
        static std::size_t constexpr s_expected_skipbo_deck_size{ 162 };
        CHECK( test_game.m_deck.size() == s_expected_skipbo_deck_size );
    }
}