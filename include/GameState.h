#pragma once
// Overall game flow state.
// Menu     - title screen, waiting for the player to press Enter
// Ready    - brief "READY!" pause shown right before control is handed
//            to the player, just like the arcade original
// Playing  - normal gameplay
// GameOver - player ran out of lives
// Win      - all pellets cleared
enum class GameState
{
    Menu,
    Ready,
    Playing,
    GameOver,
    Win
};
