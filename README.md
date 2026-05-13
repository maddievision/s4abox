## s4abox

Desktop implementation of [__sappy4all_](https://codeberg.org/roses/sappy4all)
(s4a) for realtime audio use (in standalone monitoring programs,
VST/AU plugins, etc.)

This is based off of [__agbplay-midi__](https://github.com/wildfire-kithara/agbplay-midi),
a fork of [__agbplay__](https://github.com/ipatix/agbplay) that adds a
Live MIDI mode for playing the synth directly with MIDI input.

> __agbplay__ is a music player with Terminal interface for GBA ROMs that use
> the most common (mp2k/m4a) sound engine format. The code itself is written in
> C++.

## Heavily WIP

This is not functional or anywhere near ready to use yet. It is also dependent
on the progress of s4a, and will be developed alongside it. s4a itself is
very much WIP, having features where designs are still yet to be determined
(i.e., some may follow MP2k standards, but some may use a new design, and there
will be entirely new features as well).

Some off the cuff TODOs:
- Restructure SoundMixer to be more realtime safe, wait free, etc., so we can
  process the output buffer directly from it and reduce some latency.
- Ability to have sound banks, instruments, samples, sequences, etc. read
  and stored in memory.
- Read from standard MIDI files.
- Interpret CCs the same way as s4a, including how velocity/volume/expression
  are calculated
- Wrap into a JUCE project for plugin embedding.
