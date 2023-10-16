#include "skipbo.h"

#include <random>
#include <ranges>

std::ostream& operator<<( std::ostream& stream, Card const& card )
{
    return stream << ( card.m_value == Card::s_skipbo ? "SkipBo" : std::to_string( card.m_value ) );
}

bool operator==( Card const& lhs, Card const& rhs )
{
    return lhs.m_value == rhs.m_value;
}

Skipbo::Skipbo() :
    m_deck{ [] {
        std::vector< Card > deck( 162, Card{ Card::s_skipbo } );
        int card_count{ 18 };
        std::fill_n( std::next( deck.begin(), card_count ), 12, Card{ 1 } );
        std::fill_n( std::next( deck.begin(), card_count += 12 ), 12, Card{ 2 } );
        std::fill_n( std::next( deck.begin(), card_count += 12 ), 12, Card{ 3 } );
        std::fill_n( std::next( deck.begin(), card_count += 12 ), 12, Card{ 4 } );
        std::fill_n( std::next( deck.begin(), card_count += 12 ), 12, Card{ 5 } );
        std::fill_n( std::next( deck.begin(), card_count += 12 ), 12, Card{ 6 } );
        std::fill_n( std::next( deck.begin(), card_count += 12 ), 12, Card{ 7 } );
        std::fill_n( std::next( deck.begin(), card_count += 12 ), 12, Card{ 8 } );
        std::fill_n( std::next( deck.begin(), card_count += 12 ), 12, Card{ 9 } );
        std::fill_n( std::next( deck.begin(), card_count += 12 ), 12, Card{ 10 } );
        std::fill_n( std::next( deck.begin(), card_count += 12 ), 12, Card{ 11 } );
        std::fill_n( std::next( deck.begin(), card_count += 12 ), 12, Card{ 12 } );
        return deck;
    }() }
{
}

std::ostream& operator<<( std::ostream& stream, Skipbo::Deck const& deck )
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

void shuffle( Skipbo::Deck& deck )
{
    std::random_device rd;
    std::mt19937 gen{ rd() };
    std::ranges::shuffle( deck, gen );
}

Card take_card( Skipbo& game_state )
{
    auto card{ game_state.m_deck.at( 0 ) };
    game_state.m_deck.erase( game_state.m_deck.begin() );

    if( game_state.m_deck.size() < 6 )
    {
        shuffle( game_state.m_trash_pile );
        game_state.m_deck.insert( game_state.m_deck.end(), game_state.m_trash_pile.begin(), game_state.m_trash_pile.end() );
        game_state.m_trash_pile.clear();
    }

    return card;
}

std::vector< Magic_pile > deal_magic_piles( Skipbo& game_state, int const player_count, int const magic_pile_size )
{
    std::vector< Magic_pile > magic_piles( player_count );
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

void replenish_hand( Skipbo& game_state, Player::Hand& hand )
{
    while( hand.size() < Player::s_max_hand_size )
    {
        hand.push_back( take_card( game_state ) );
    }
    std::ranges::sort( hand, []( auto const& lhs, auto const& rhs ) { return lhs.m_value < rhs.m_value; } );
}

void show_hand( Player const& player )
{
    std::cout << "hand: " << player.m_hand << '\n';
}

void show_play_piles( Skipbo const& game_state )
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

void show_discard_piles( Player const& player )
{
    for( auto const& discard_pile : player.m_discards )
    {
    }
}

void take_turn( Skipbo& game_state, Player& player )
{
    replenish_hand( game_state, player.m_hand );
}