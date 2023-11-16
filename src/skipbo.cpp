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

bool operator<( Card const& lhs, Card const& rhs )
{
    return lhs.m_value < rhs.m_value;
}

Skipbo::Skipbo() :
    m_deck{ [] {
        std::vector< Card > deck( s_expected_skipbo_deck_size, Card{ Card::s_skipbo } );
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

std::vector< Magic_pile > deal_magic_piles( Skipbo& game_state, std::uint8_t const player_count, std::uint8_t const magic_pile_size )
{
    if( auto const cards_required{ ( player_count * 5 ) + ( player_count * magic_pile_size ) }; cards_required > s_expected_skipbo_deck_size )
    {
        throw std::runtime_error( "Cannot deal more than 162 cards. players: " +
                                  std::to_string( player_count ) + ", magic pile size: " + std::to_string( magic_pile_size ) +
                                  ", cards for players' hands: " + std::to_string( player_count * 5 ) +
                                  ", total cards required: " + std::to_string( cards_required ) );
    }

    std::vector< Magic_pile > magic_piles( player_count );
    for( auto& pile : magic_piles )
    {
        pile.reserve( magic_pile_size );
    }

    std::uint8_t cards_dealt{};
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
    //@TODO need to to cinder stuff here.
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
    //@TODO need to to cinder stuff here.
}

void show_discard_piles( Player const& player )
{
    for( auto const& discard_pile : player.m_discards )
    {
    }
    //@TODO need to to cinder stuff here.
}

void take_turn( Skipbo& game_state, Player& player )
{
    replenish_hand( game_state, player.m_hand );

    // for a turn
    // replenish hand
    // show hand
    // show magic pile
    // show discard piles
    // show play piles

    // Person somehow takes a card from their hand and adds to play pile or not

    // Replenish had if it goes empty and haven't discarded

    // End turn by taking a card from hand and add to discard
}