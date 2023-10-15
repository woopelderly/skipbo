#pragma once

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

struct Card
{
    static int constexpr s_skipbo{};
    std::uint8_t m_value{};
};

std::ostream& operator<<( std::ostream& stream, Card card );

struct Skipbo
{
    Skipbo();

    using deck = std::vector< Card >;
    deck m_deck;

    using play_pile = std::vector< Card >;
    std::array< play_pile, 4 > m_play_piles;

    using trash_pile = std::vector< Card >;
    trash_pile m_trash_pile;
};

[[nodiscard]] std::ostream& operator<<( std::ostream& stream, Skipbo::deck const& deck );

void shuffle( Skipbo::deck& deck );

[[nodiscard]] Card take_card( Skipbo& game_state );

using magic_pile = std::vector< Card >;
[[nodiscard]] std::vector< magic_pile > deal_magic_piles( Skipbo& game_state, int player_count = 2, int magic_pile_size = 10 );

struct Player
{
    static int constexpr s_max_hand_size{ 5 };
    using hand = std::vector< Card >;
    hand m_hand;
    magic_pile m_magic_pile;
    using discard  = std::vector< Card >;
    using discards = std::array< discard, 4 >;
    discards m_discards;
};

void replenish_hand( Skipbo& game_state, Player::hand& hand );

void show_hand( Player const& player );

void show_play_piles( Skipbo const& game_state );

void show_discard_piles( Player const& player );

void take_turn( Skipbo& game_state, Player& player );