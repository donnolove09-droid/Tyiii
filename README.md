# ASN VOICE AI — training + iOS integration starter

This repository includes an **AI voice-conversion training plan and model integration boundary**. It does not contain trained voice weights. The three supplied recordings are short reference samples, not a trained neural model.

## Voice slots
- `male_1` — Eren reference
- `male_2` — second male reference
- `female_1` — female reference

## What is included
- Dataset preparation helper (`training/prepare_dataset.py`) to convert consented recordings to clean mono WAV segments.
- Per-voice training manifest and a documented RVC training path.
- Model directory contract for one model per voice.
- iOS model-loader interface contract; it refuses to claim inference if a compatible Core ML model is absent.
- GitHub Actions compiles the native iOS ARM64 library shell.

## What is not included
- No `.pth`, `.index`, `.mlmodel`, or `.mlmodelc` weights are included.
- No trained neural model has been produced from the short samples.
- The native dylib build is not a game injection and does not provide a system-wide virtual microphone.
- RVC PyTorch checkpoints are not directly loadable by Core ML. Export/conversion and numerical validation are separate engineering tasks.

## Data required
For each target voice, record the consenting speaker alone, with no music/game audio, stable microphone distance, and varied natural sentences. Do not mix speakers in one voice dataset. Aim for at least 5–10 minutes per speaker for an initial experiment; 10–50 minutes is a more robust target according to the [RVC FAQ](https://github.com/RVC-Project/Retrieval-based-Voice-Conversion-WebUI/wiki/FAQ).

Suggested folder layout:
```text
training/datasets/
  male_1/*.wav
  male_2/*.wav
  female_1/*.wav
```
Do not commit private voice recordings to this public repository. Use a trusted private training environment.

## Prepare recordings
Install FFmpeg and run:
```bash
python3 training/prepare_dataset.py --input /path/to/recording.mp3 --output training/datasets/male_1 --prefix male_1
```
Repeat for each voice. The script writes 40 kHz mono WAV chunks of up to 10 seconds and does not upload anything.

## Train
Use the official [RVC WebUI](https://github.com/RVC-Project/Retrieval-based-Voice-Conversion-WebUI) in a separate GPU-capable environment. Train three separate voice models, one per dataset. Standard GitHub-hosted runners do not provide a guaranteed CUDA GPU. Keep checkpoints private if the speakers request that.

## iOS integration
Apple's AVAudioEngine is the supported app-owned real-time audio graph. Core ML can run converted models on Apple hardware, but an RVC PyTorch model needs deliberate conversion/reimplementation and validation before it can be loaded by Core ML.

The `Models/README.md` defines the expected artifact names. Until a compatible model exists, the iOS adapter returns `ASN_VOICE_MODEL_NOT_INSTALLED`.

## Compatibility boundary
This library only processes PCM buffers passed to it by an application that intentionally integrates the API. It cannot inject itself into Liên Quân Mobile, Free Fire, or Free Fire MAX, and ESign only signs/installs compatible IPA packages. Each app needs an authorized integration point and separate testing.