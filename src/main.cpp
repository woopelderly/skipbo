#include "skipbo.h"
#include "version.h"

int main()
{
    std::cout << version::GetSemanticVersion() << '\n';
    Skipbo game_state;
    shuffle( game_state.m_deck );
    // std::cout << skipbo.m_deck << '\n';
    std::vector< Player > players( 2 );
    int piles_dealt{};
    for( auto Magic_pile : deal_magic_piles( game_state, static_cast< int >( players.size() ) ) )
    {
        players.at( piles_dealt++ ).m_magic_pile = std::move( Magic_pile );
    }

    // Loop bouncing between players

    // std::cout << skipbo.m_deck.size() << '\n';
    // std::cout << magic_piles.at( 0 ).size() << '\n';
    // std::cout << magic_piles.at( 1 ).size() << '\n';
    // std::cout << magic_piles.at( 0 ) << '\n';
    // std::cout << magic_piles.at( 1 ) << '\n';
}