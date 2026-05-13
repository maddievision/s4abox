#include <iostream>
#include <cstring>
#include <cstdio>
#include <clocale>

#include "SoundData.h"
#include "Debug.h"
#include "Xcept.h"
#include "ConfigManager.h"
#include "OS.h"
#include "Rom.h"
#include "PlayerInterface.h"

static void usage();
static void help();

int main(int argc, char *argv[]) 
{
    if (!Debug::open(nullptr)) {
        std::cout << "Debug Init failed" << std::endl;
        return EXIT_FAILURE;
    }
    if (argc < 2 || argc > 4) {
        usage();
        return EXIT_FAILURE;
    }

    if (!strcmp("--help", argv[1])) {
        help();
        return EXIT_SUCCESS;
    }

    size_t songTablePos = UNKNOWN_TABLE;
    if (argc >= 3) {
        songTablePos = strtoul(argv[2], nullptr, 16);
    }


    try {
        setlocale(LC_ALL, "");
        std::cout << "Loading ROM..." << std::endl;

        Rom::CreateInstance(argv[1]);
        std::cout << "Loading Config..." << std::endl;
        ConfigManager::Instance().Load();
        ConfigManager::Instance().SetGameCode(Rom::Instance().GetROMCode());
        std::cout << "Reading Songtable" << std::endl;
        SongTable songTable(songTablePos);
        std::cout << "Initialization complete!" << std::endl;
        Rom& rom = Rom::Instance();
    
        PlayerInterface mplay(
                rom.ReadAgbPtrToPos(songTable.GetSongTablePos()));
        mplay.LoadSong(songTable.GetPosOfSong(810));
        mplay.Play();
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    // if (Pa_Terminate() != paNoError)
    //     std::cerr << "Error while terminating portaudio" << std::endl;
    Debug::close();
    return 0;
}

static void usage()
{
    std::cout << "Usage: ./agbplay <ROM.gba> [song table position (hex)] [midi "
                 "port number]"
              << std::endl;
}


static void help()
{
    usage();
    std::cout << "\nControls:\n"
        "  - Arrow Keys or HJKL: Navigate through the program\n"
        "  - Tab: Change between Playlist and Songlist\n"
        "  - A: Add the selected song to the playlist\n"
        "  - D: Delete the selected song from the playlist\n"
        "  - T: Toggle whether the song should be output to a file (see R and E)\n"
        "  - G: Drag the song through the playlist for ordering\n"
        "  - I: Force Song Restart\n"
        "    - In Live MIDI mode this will simply turn off all notes without resetting controllers.\n"
        "  - O: Song Play/Pause\n"
        "  - P: Force Song Stop\n"
        "  - +=: Double the playback speed\n"
        "  - -: Halve the playback speed\n"
        "  - Enter: Toggle Track Muting\n"
        "  - M: Mute selected Track\n"
        "  - S: Solo selected Track\n"
        "  - U: Unmute all Tracks\n"
        "  - N: Rename the selected song in the playlisy\n"
        "  - E: Export selected songs to individual track files (to \"workdirectory/wav\")\n"
        "  - R: Export selected songs to files (non-split)\n"
        "  - B: Benchmark, Run the export program but don't write to file\n"
        "  - Q or Ctrl-D: Exit Program\n" << std::flush;
}
