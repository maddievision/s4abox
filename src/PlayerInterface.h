#pragma once

#include <cstdint>
#include <vector>
#include <thread>
#include <memory>

#include "DisplayContainer.h"
#include "Constants.h"
#include "GameConfig.h"
#include "Ringbuffer.h"
#include "LoudnessCalculator.h"
#include "PlayerContext.h"

class PlayerInterface 
{
public:
    PlayerInterface(const PlayerInterface&) = delete;
    PlayerInterface& operator=(const PlayerInterface&) = delete;
    PlayerInterface(size_t initSongPos);
    ~PlayerInterface();

    void LoadSong(size_t songPos);
    void Play();
    void Pause();
    void Stop();
    void SpeedDouble();
    void SpeedHalve();
    bool IsPlaying();
    void UpdateView();
    void ToggleMute(size_t index);
    void Mute(size_t index, bool mute);
    size_t GetMaxTracks() { return mutedTracks.size(); }
    void GetMasterVolLevels(float& left, float& right);
    SongInfo GetSongInfo() const;

private:
    void initContext();
    void threadWorker();

    void setupLoudnessCalcs();

    std::string midiPortName;
    uint32_t speedFactor = 64;
    volatile enum class State : int {
        RESTART, PLAYING, PAUSED, TERMINATED, SHUTDOWN, THREAD_DELETED
    } playerState = State::THREAD_DELETED;
    std::unique_ptr<PlayerContext> ctx;
    Ringbuffer rBuf{STREAM_BUF_SIZE};

    LoudnessCalculator masterLoudness{10.0f};
    std::vector<LoudnessCalculator> trackLoudness;
    std::vector<bool> mutedTracks;

    std::unique_ptr<std::thread> playerThread;
};
