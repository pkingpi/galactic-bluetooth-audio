#pragma once
#include <functional>
#include "display.hpp"
#include "lib/fixed_fft.hpp"
#include "lib/rgb.hpp"

class Effect {
    public:
        Display &display;
        FIX_FFT &fft;
        Effect(Display& display, FIX_FFT& fft) : 
            display(display), 
            fft(fft) {};
        virtual void init(uint32_t sample_frequency);
        virtual void update(int16_t *buffer16, size_t sample_count);
};

class RainbowFFT : public Effect {
    private:
        // Number of FFT bins to skip on the left, the low frequencies tend to be pretty boring visually
        static constexpr unsigned int FFT_SKIP_BINS = 1;
        static constexpr unsigned int BUFFERS_PER_FFT_SAMPLE = 2;
        static constexpr unsigned int SAMPLES_PER_AUDIO_BUFFER = SAMPLE_COUNT / BUFFERS_PER_FFT_SAMPLE;
        static constexpr int HISTORY_LEN = 21; // About 0.25s
        uint history_idx;
        uint8_t eq_history[Display::WIDTH][HISTORY_LEN];

        RGB palette_peak[Display::WIDTH];
        RGB palette_main[Display::WIDTH];

        float max_sample_from_fft;
        int lower_threshold;
#ifdef SCALE_LOGARITHMIC
        fix15 multiple;
#elif defined(SCALE_SQRT)
        fix15 subtract_step;
#elif defined(SCALE_LINEAR)
        fix15 subtract;
#else
#error "Choose a scale mode"
#endif

    public:
        RainbowFFT(Display& display, FIX_FFT& fft) : Effect(display, fft) {}
        void update(int16_t *buffer16, size_t sample_count) override;
        void init(uint32_t sample_frequency) override;
};

class ClassicFFT : public Effect {
    private:
        // Number of FFT bins to skip on the left, the low frequencies tend to be pretty boring visually
        static constexpr unsigned int FFT_SKIP_BINS = 1;
        static constexpr unsigned int BUFFERS_PER_FFT_SAMPLE = 2;
        static constexpr unsigned int SAMPLES_PER_AUDIO_BUFFER = SAMPLE_COUNT / BUFFERS_PER_FFT_SAMPLE;
        static constexpr int HISTORY_LEN = 21; // About 0.25s
        uint history_idx;
        uint8_t eq_history[Display::WIDTH][HISTORY_LEN];

        RGB palette[Display::HEIGHT];

        float max_sample_from_fft;
        int lower_threshold;
#ifdef SCALE_LOGARITHMIC
        fix15 multiple;
#elif defined(SCALE_SQRT)
        fix15 subtract_step;
#elif defined(SCALE_LINEAR)
        fix15 subtract;
#else
#error "Choose a scale mode"
#endif

    public:
        ClassicFFT(Display& display, FIX_FFT &fft) : Effect(display, fft) {}
        void update(int16_t *buffer16, size_t sample_count) override;
        void init(uint32_t sample_frequency) override;
};

class ClassicFFT2 : public Effect {
    private:
        // Number of FFT bins to skip on the left, the low frequencies tend to be pretty boring visually
        static constexpr unsigned int FFT_SKIP_BINS = 1;
        static constexpr unsigned int BUFFERS_PER_FFT_SAMPLE = 2;
        static constexpr unsigned int SAMPLES_PER_AUDIO_BUFFER = SAMPLE_COUNT / BUFFERS_PER_FFT_SAMPLE;
        static constexpr int HISTORY_LEN = 21; // About 0.25s
        uint history_idx;
        uint8_t eq_history[Display::WIDTH][HISTORY_LEN];

        RGB palette[Display::HEIGHT];

        float max_sample_from_fft;
        int lower_threshold;
#ifdef SCALE_LOGARITHMIC
        fix15 multiple;
#elif defined(SCALE_SQRT)
        fix15 subtract_step;
#elif defined(SCALE_LINEAR)
        fix15 subtract;
#else
#error "Choose a scale mode"
#endif

    public:
        ClassicFFT2(Display& display, FIX_FFT &fft) : Effect(display, fft) {}
        void update(int16_t *buffer16, size_t sample_count) override;
        void init(uint32_t sample_frequency) override;
};
