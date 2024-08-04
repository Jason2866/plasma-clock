#pragma once
#include <stdint.h>
#include <string.h>

typedef enum sprite_fmt {
    /// A horizontally laid out sprite
    /// @details I.e. a 14x2 sprite will consist of 4 bytes. 0th one will contain the leftmost 6 pixels of the top row aligned towards LSB, 
    ///          1st one will contain the rightmost 8 pixels, 2nd one will contain the leftmost 6px of the bottom row, and so forth.
    SPRFMT_HORIZONTAL,
    /// A vertically laid out sprite
    /// @details I.e. a 14x2 sprite will consist of 4 bytes. 0th one will contain the 8 pixels of the leftmost column with top left being MSB,
    ///          1st one will contain the next 6 pixels of the lefrmost column aligned towards MSB, 2nd one will contain the top 8px of the second column and so on.
    SPRFMT_NATIVE
} sprite_fmt_t;

/// @brief A piece of graphics with a size and optional mask
typedef struct sprite {
    uint8_t width, height;
    const uint8_t* data;
    const uint8_t* mask;
    sprite_fmt_t format;
} sprite_t;

/// @brief An animated sprite. 
/// @see sprite_t
typedef struct ani_sprite {
    uint8_t width, height;
    /// @brief Number of frames in the animation
    uint8_t frames;
    /// @brief How many display frames should each animation frame be displayed for
    uint8_t screen_frames_per_frame;
    /// @brief How many display frames should the first frame be shown before the animation loops
    uint8_t holdoff_frames;
    const uint8_t* data;
    sprite_fmt_t format;
} ani_sprite_t;

/// @brief A context of a playing animated sprite
typedef struct ani_sprite_state {
    /// @brief Currently playing sprite
    const ani_sprite_t* ani_sprite;
    /// @brief Display frames passed since the last animation frame was shown
    uint8_t framecount;
    /// @brief Index of the current animation frame
    uint8_t playhead;
    /// @brief Display frames remaining until the animation will restart
    int holdoff_counter;
} ani_sprite_state_t;

typedef uint8_t* fanta_buffer_t;

/// @brief Initialize a playback context for an animated sprite
extern ani_sprite_state_t ani_sprite_prepare(const ani_sprite*);
/// @brief Get the current animation frame to be drawn for an animated sprite
extern sprite_t ani_sprite_frame(ani_sprite_state_t*);

/// Allocate memory in the fast space, for graphics use specifically
void* gralloc(const size_t);