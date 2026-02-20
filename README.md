# Cosmic_Barage_UBISOFT_NEXT_2026

Submission for the Ubisoft NEXT 2026 Programming Challenge.

## How to Play

- Move: `WASD`, arrow keys, or controller stick
- Shoot: left mouse button, `Space`, or right trigger
- Pause: `P`
- Unpause: `U`
- Start game: `Enter`
- Quit: `Q`
- Help: `H` (available at any time)

## Gameplay

### Player

The player controls a ship and survives a bullet-hell arena while defeating as many enemies as possible before losing all five lives.

- Lose 1 life when hit by a bullet
- Lose 2 lives when colliding with an enemy
- Gain 1 second of invincibility after taking damage

### Enemies

There are three enemy types:

- **Minion**: moves slowly and fires bullets toward the player’s current position
- **Charger**: charges down the screen and launches rockets to its sides
- **Splatter**: stays near the top of the screen and fires bullets in all directions

### UI

The UI allows the player to:

- Track score and remaining health at the top of the screen
- Restart quickly after game over or return to menu
- Pause and unpause during gameplay
- Open help with `H`

## Technical Overview

- Game objects are organized into dedicated managers responsible for movement, rendering, and cleanup
- Enemy attack intervals use a custom timer system driven by `deltaTime`
- The same timer system is reused to manage multiple gameplay features
- UI rendering is encapsulated in a UI class that switches by game state
- Pause behavior is implemented by returning early from the `Update` function
- Most systems are class-based for easier extension

## Planned Improvements

Features intended but not completed in time:

- Replace broad collision checks with sector-based spatial partitioning for better performance
- Add a boss fight
- Add events that clear all enemies and bullets on screen
- Add a high-score display

## References

### Art

- Enemy, player, and bullet sprites were created in Paint 3D and Photoshop

### Audio & Background Assets (Itch.io, copyright-free)

- [https://scrython.itch.io/cosmic-backg...](https://scrython.itch.io/cosmic-background)
- [https://tallbeard.itch.io/music-loop-...](https://tallbeard.itch.io/music-loop-bundle)
- [https://ci.itch.io/arcade-sound-effec...](https://ci.itch.io/arcade-sound-effects-pack)

