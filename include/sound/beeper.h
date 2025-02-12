#pragma once
#include <sound/waveout.h>
#include <sound/generators.h>

typedef enum beeper_channels {
    /// @brief Channel for ambient sounds (clock ticking, etc)
    CHANNEL_AMBIANCE = 0,
    /// @brief Channel for notice sounds (settings saved, other events)
    CHANNEL_NOTICE = 1,
    /// @brief Channel for chime sounds (hourly chime, etc)
    CHANNEL_CHIME = 2,

    /// @brief Channel for alarms
    CHANNEL_ALARM = 6,
    /// @brief Max priority channel for system events (FVU etc)
    CHANNEL_SYSTEM = 7
} beeper_channel_t;

static const uint16_t DUTY_SQUARE = 2;

class Beeper: public WaveGenerator {
public:
    Beeper();
    ~Beeper();

    void set_channel_state(beeper_channel_t, bool);
    bool is_channel_enabled(beeper_channel_t);

    size_t fill_buffer(void* buffer, size_t length_) override;
    void start_tone(beeper_channel_t, uint, uint16_t duty = DUTY_SQUARE);
    void stop_tone(beeper_channel_t);

    /// @brief Play a tone for a precise amount of milliseconds
    void beep(beeper_channel_t, uint freq, uint len, uint16_t duty = DUTY_SQUARE);
private:
    ToneGenerator* voice;
    uint8_t channel_status;
    int active_channel;
    int samples;
    int duration_samples;
};