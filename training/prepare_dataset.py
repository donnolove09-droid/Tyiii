#!/usr/bin/env python3
"""Prepare one consented voice recording into mono 40 kHz WAV chunks.

Requires ffmpeg on PATH. This does not train a model.
"""
import argparse
import pathlib
import shutil
import subprocess
import tempfile


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--input", required=True)
    ap.add_argument("--output", required=True)
    ap.add_argument("--prefix", required=True)
    ap.add_argument("--chunk-seconds", type=int, default=10)
    args = ap.parse_args()

    if not shutil.which("ffmpeg"):
        raise SystemExit("ffmpeg was not found. Install FFmpeg first.")
    src = pathlib.Path(args.input)
    out = pathlib.Path(args.output)
    if not src.is_file():
        raise SystemExit(f"Input file not found: {src}")
    out.mkdir(parents=True, exist_ok=True)

    with tempfile.TemporaryDirectory() as td:
        normalized = pathlib.Path(td) / "normalized.wav"
        subprocess.run([
            "ffmpeg", "-y", "-i", str(src), "-vn", "-ac", "1",
            "-ar", "40000", "-af", "loudnorm", str(normalized)
        ], check=True)
        subprocess.run([
            "ffmpeg", "-y", "-i", str(normalized), "-f", "segment",
            "-segment_time", str(args.chunk_seconds), "-c", "pcm_s16le",
            str(out / f"{args.prefix}_%04d.wav")
        ], check=True)

    print(f"Prepared dataset at: {out}")
    print("Listen to every segment and delete silence, clipping, noise, or other speakers.")


if __name__ == "__main__":
    main()
