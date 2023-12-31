#include "../skipbo.h"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>

namespace
{
    TEST_CASE( "Card" )
    {
        Card test_card;

        SECTION( "Ctor" )
        {
            CHECK( Card::s_skipbo == test_card.m_value );
        }
    }

    void check_card_counts( Skipbo::Deck const& deck )
    {
        CHECK( 18 == std::ranges::count_if( deck, []( auto const& card ) { return card.m_value == Card::s_skipbo; } ) );
        CHECK( 12 == std::ranges::count_if( deck, []( auto const& card ) { return card.m_value == 1; } ) );
        CHECK( 12 == std::ranges::count_if( deck, []( auto const& card ) { return card.m_value == 2; } ) );
        CHECK( 12 == std::ranges::count_if( deck, []( auto const& card ) { return card.m_value == 3; } ) );
        CHECK( 12 == std::ranges::count_if( deck, []( auto const& card ) { return card.m_value == 4; } ) );
        CHECK( 12 == std::ranges::count_if( deck, []( auto const& card ) { return card.m_value == 5; } ) );
        CHECK( 12 == std::ranges::count_if( deck, []( auto const& card ) { return card.m_value == 6; } ) );
        CHECK( 12 == std::ranges::count_if( deck, []( auto const& card ) { return card.m_value == 7; } ) );
        CHECK( 12 == std::ranges::count_if( deck, []( auto const& card ) { return card.m_value == 8; } ) );
        CHECK( 12 == std::ranges::count_if( deck, []( auto const& card ) { return card.m_value == 9; } ) );
        CHECK( 12 == std::ranges::count_if( deck, []( auto const& card ) { return card.m_value == 10; } ) );
        CHECK( 12 == std::ranges::count_if( deck, []( auto const& card ) { return card.m_value == 11; } ) );
        CHECK( 12 == std::ranges::count_if( deck, []( auto const& card ) { return card.m_value == 12; } ) );
    }

    TEST_CASE( "Skipbo" ) // NOLINT: cognitive Complexity
    {
        Skipbo test_game;

        SECTION( "Ctor" )
        {
            CHECK( test_game.m_deck.size() == s_expected_skipbo_deck_size );
            check_card_counts( test_game.m_deck );
        }

        SECTION( "Shuffle_expectSameNumberOfEachCardDifferentOrder" )
        {
            Skipbo unshuffled_game;
            CHECK( unshuffled_game.m_deck == test_game.m_deck );
            shuffle( test_game.m_deck );
            check_card_counts( test_game.m_deck );
            CHECK( unshuffled_game.m_deck != test_game.m_deck );
        }

        SECTION( "TakeCard_gameDeckFullAndNotShuffled_expectSkipbo" )
        {
            CHECK( Card::s_skipbo == take_card( test_game ).m_value );
            CHECK( s_expected_skipbo_deck_size - 1 == test_game.m_deck.size() );
        }

        SECTION( "TakeCard_gameDeckSize7_expectSkipbo" )
        {
            test_game.m_deck.erase( std::next( test_game.m_deck.cbegin(), 7 ), test_game.m_deck.cend() );

            CHECK( Card::s_skipbo == take_card( test_game ).m_value );
            CHECK( 6 == test_game.m_deck.size() );
        }

        SECTION( "TakeCard_gameDeckSize6_expectSkipboAndTopCardsInSameOrder" )
        {
            test_game.m_deck.erase( std::next( test_game.m_deck.cbegin(), 6 ), test_game.m_deck.cend() );
            Skipbo::Trash_pile const unshuffled_trash{ Card{ 1 }, Card{ 2 }, Card{ 3 }, Card{ 4 }, Card{ 5 }, Card{ 6 }, Card{ 7 }, Card{ 8 }, Card{ 9 }, Card{ 10 } };
            test_game.m_trash_pile = unshuffled_trash;
            CHECK( Card::s_skipbo == take_card( test_game ).m_value );
            REQUIRE( 15 == test_game.m_deck.size() );
            CHECK( Card::s_skipbo == test_game.m_deck.at( 0 ).m_value );
            CHECK( Card::s_skipbo == test_game.m_deck.at( 1 ).m_value );
            CHECK( Card::s_skipbo == test_game.m_deck.at( 2 ).m_value );
            CHECK( Card::s_skipbo == test_game.m_deck.at( 3 ).m_value );
            CHECK( Card::s_skipbo == test_game.m_deck.at( 4 ).m_value );
            test_game.m_deck.erase( test_game.m_deck.cbegin(), std::next( test_game.m_deck.cbegin(), 5 ) );
            CHECK( unshuffled_trash.size() == test_game.m_deck.size() );
            CHECK( unshuffled_trash != test_game.m_deck );
        }

        SECTION( "DealMagicPiles" )
        {
            auto const magic_piles{ deal_magic_piles( test_game, 1, 5 ) };
            REQUIRE( 1 == magic_piles.size() );
            CHECK( 5 == magic_piles.at( 0 ).size() );
        }

        SECTION( "DealMagicPiles_zeroPlayers" )
        {
            auto const magic_piles{ deal_magic_piles( test_game, 0, 5 ) };
            CHECK( magic_piles.empty() );
        }

        SECTION( "DealMagicPiles_negativePlayers" )
        {
            CHECK_THROWS_AS( ( ( void )deal_magic_piles( test_game, -1, 5 ) ), std::runtime_error );
        }

        SECTION( "DealMagicPiles_negativeCardCount" )
        {
            CHECK_THROWS_AS( ( ( void )deal_magic_piles( test_game, 1, -5 ) ), std::runtime_error );
        }

        SECTION( "ReplenishHand_emptyHand" )
        {
            Player::Hand test_hand;
            shuffle( test_game.m_deck );
            replenish_hand( test_game, test_hand );
            CHECK( test_hand.size() == 5 );
            CHECK( test_game.m_deck.size() == s_expected_skipbo_deck_size - 5 );
            CHECK( ( std::is_sorted( test_hand.begin(), test_hand.end() ) ) );
        }

        SECTION( "ReplenishHand_fullHand" )
        {
            Player::Hand test_hand( 5 );
            shuffle( test_game.m_deck );
            replenish_hand( test_game, test_hand );
            CHECK( test_hand.size() == 5 );
            CHECK( test_game.m_deck.size() == s_expected_skipbo_deck_size );
            CHECK( ( std::is_sorted( test_hand.begin(), test_hand.end() ) ) );
        }

        SECTION( "ReplenishHand_partialHand" )
        {
            Player::Hand test_hand( 2 );
            shuffle( test_game.m_deck );
            replenish_hand( test_game, test_hand );
            CHECK( test_hand.size() == 5 );
            CHECK( test_game.m_deck.size() == s_expected_skipbo_deck_size - 3 );
            CHECK( ( std::is_sorted( test_hand.begin(), test_hand.end() ) ) );
        }
    }
}