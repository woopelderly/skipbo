#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <vector>

struct Card
{
    static int constexpr s_skipbo{};
    std::uint8_t m_value{};
};

[[maybe_unused]] std::ostream& operator<<( std::ostream& stream, Card const& card );

[[nodiscard]] bool operator==( Card const& lhs, Card const& rhs );

[[nodiscard]] bool operator<( Card const& lhs, Card const& rhs );

static std::size_t constexpr s_expected_skipbo_deck_size{ 162 };
struct Skipbo
{
    Skipbo();

    using Deck = std::vector< Card >;
    Deck m_deck;

    using Play_pile = std::vector< Card >;
    std::array< Play_pile, 4 > m_play_piles;

    using Trash_pile = std::vector< Card >;
    Trash_pile m_trash_pile;
};

[[maybe_unused]] std::ostream& operator<<( std::ostream& stream, Skipbo::Deck const& deck );

void shuffle( Skipbo::Deck& deck );

[[nodiscard]] Card take_card( Skipbo& game_state );

using Magic_pile = std::vector< Card >;
[[nodiscard]] std::vector< Magic_pile > deal_magic_piles( Skipbo& game_state, std::uint8_t player_count = 2U, std::uint8_t magic_pile_size = 10U );

struct Player
{
    static int constexpr s_max_hand_size{ 5 };
    using Hand = std::vector< Card >;
    Hand m_hand;
    Magic_pile m_magic_pile;
    using Discard  = std::vector< Card >;
    using Discards = std::array< Discard, 4 >;
    Discards m_discards;
};

void replenish_hand( Skipbo& game_state, Player::Hand& hand );

void show_hand( Player const& player );

void show_play_piles( Skipbo const& game_state );

void show_discard_piles( Player const& player );

void take_turn( Skipbo& game_state, Player& player );