#include "version.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <random>
#include <ranges>
#include <vector>

struct card
{
    static int constexpr s_skipbo{};
    std::uint8_t m_value{};
};

std::ostream& operator<<( std::ostream& stream, card card )
{
    return stream << ( card.m_value == card::s_skipbo ? "SkipBo" : std::to_string( card.m_value ) );
}

struct skipbo
{
    using deck = std::vector< card >;
    deck m_deck{ [] {
        std::vector< card > deck( 162, card{ card::s_skipbo } );
        int card_count{ 18 };
        std::fill_n( std::next( deck.begin(), card_count ), 12, card{ 1 } );
        std::fill_n( std::next( deck.begin(), card_count += 12 ), 12, card{ 2 } );
        std::fill_n( std::next( deck.begin(), card_count += 12 ), 12, card{ 3 } );
        std::fill_n( std::next( deck.begin(), card_count += 12 ), 12, card{ 4 } );
        std::fill_n( std::next( deck.begin(), card_count += 12 ), 12, card{ 5 } );
        std::fill_n( std::next( deck.begin(), card_count += 12 ), 12, card{ 6 } );
        std::fill_n( std::next( deck.begin(), card_count += 12 ), 12, card{ 7 } );
        std::fill_n( std::next( deck.begin(), card_count += 12 ), 12, card{ 8 } );
        std::fill_n( std::next( deck.begin(), card_count += 12 ), 12, card{ 9 } );
        std::fill_n( std::next( deck.begin(), card_count += 12 ), 12, card{ 10 } );
        std::fill_n( std::next( deck.begin(), card_count += 12 ), 12, card{ 11 } );
        std::fill_n( std::next( deck.begin(), card_count += 12 ), 12, card{ 12 } );
        return deck;
    }() };

    using play_pile = std::vector< card >;
    std::array< play_pile, 4 > m_play_piles;

    using trash_pile = std::vector< card >;
    trash_pile m_trash_pile;
};

std::ostream& operator<<( std::ostream& stream, skipbo::deck const& deck )
{
    int count{};
    for( auto const& card : deck )
    {
        stream << static_cast< int >( card.m_value ) << ' ';
        if( ++count % 9 == 0 )
        {
            stream << '\n';
        }
    }
    return stream;
}

void shuffle( skipbo::deck& deck )
{
    std::random_device rd;
    std::mt19937 gen{ rd() };
    std::ranges::shuffle( deck, gen );
}

card take_card( skipbo& game_state )
{
    auto card{ game_state.m_deck.at( 0 ) };
    game_state.m_deck.erase( game_state.m_deck.begin() );

    if( game_state.m_deck.size() < 6 )
    {
        game_state.m_deck.insert( game_state.m_deck.end(), game_state.m_trash_pile.begin(), game_state.m_trash_pile.end() );
        game_state.m_trash_pile.clear();
        shuffle( game_state.m_deck );
    }
    return card;
}

using magic_pile = std::vector< card >;
std::vector< magic_pile > deal_magic_piles( skipbo& game_state, int const player_count = 2, int const magic_pile_size = 10 )
{
    std::vector< magic_pile > magic_piles( player_count );
    for( auto& pile : magic_piles )
    {
        pile.reserve( magic_pile_size );
    }

    int cards_dealt{};
    while( cards_dealt++ < magic_pile_size )
    {
        for( auto& pile : magic_piles )
        {
            pile.push_back( take_card( game_state ) );
        }
    }

    return magic_piles;
}

struct player
{
    static int constexpr s_max_hand_size{ 5 };
    using hand = std::vector< card >;
    hand m_hand;
    magic_pile m_magic_pile;
    using discard  = std::vector< card >;
    using discards = std::array< discard, 4 >;
    discards m_discards;
};

void replenish_hand( skipbo& game_state, player::hand& hand )
{
    while( hand.size() < player::s_max_hand_size )
    {
        hand.push_back( take_card( game_state ) );
    }
    std::ranges::sort( hand, []( auto const& lhs, auto const& rhs ) { return lhs.m_value < rhs.m_value; } );
}

void show_hand( player const& player )
{
    std::cout << "hand: " << player.m_hand << '\n';
}

void show_play_piles( skipbo const& game_state )
{
    for( auto const& play_pile : game_state.m_play_piles )
    {
        if( play_pile.empty() )
        {
            std::cout << "Pile 1: empty\n";
        }
        else
        {
            std::cout << "Pile 1: " << play_pile << '\n';
        }
    }
}

void show_discard_piles( player const& player )
{
    for( auto const& discard_pile : player.m_discards )
    {
    }
}

void take_turn( skipbo& game_state, player& player )
{
    replenish_hand( game_state, player.m_hand );
}

int main()
{
    std::cout << version::GetSemanticVersion() << '\n';
    skipbo game_state;
    shuffle( game_state.m_deck );
    // std::cout << skipbo.m_deck << '\n';
    std::vector< player > players( 2 );
    int piles_dealt{};
    for( auto magic_pile : deal_magic_piles( game_state, static_cast< int >( players.size() ) ) )
    {
        players.at( piles_dealt++ ).m_magic_pile = std::move( magic_pile );
    }

    // Loop bouncing between players

    // std::cout << skipbo.m_deck.size() << '\n';
    // std::cout << magic_piles.at( 0 ).size() << '\n';
    // std::cout << magic_piles.at( 1 ).size() << '\n';
    // std::cout << magic_piles.at( 0 ) << '\n';
    // std::cout << magic_piles.at( 1 ) << '\n';
}