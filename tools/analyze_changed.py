#!/usr/bin/env python3
"""Run the Clang Static Analyzer on changed source files only.

Reads build/compile_commands.json so each file is analyzed with its real compile flags.
Usage: tools/analyze_changed.py <build-dir> <file> [<file> ...]
Prints analyzer warnings as text. Always exits 0 (advisory).
"""
import json
import os
import shlex
import subprocess
import sys

CHECKERS = "core,cplusplus,unix,deadcode,security"


def main() -> int:
    if len(sys.argv) < 3:
        print("no changed files to analyze")
        return 0
    build_dir, files = sys.argv[1], sys.argv[2:]
    with open(os.path.join(build_dir, "compile_commands.json")) as f:
        db = {os.path.realpath(e["file"]): e for e in json.load(f)}

    found = 0
    for rel in files:
        entry = db.get(os.path.realpath(rel))
        if not entry:
            print(f"[skip] {rel}: not in compile_commands.json")
            continue
        args = entry.get("arguments") or shlex.split(entry["command"])
        # keep include paths, defines and the language standard; drop output/compile-only flags
        keep, skip_next = [], False
        for a in args[1:]:
            if skip_next:
                skip_next = False
                continue
            if a in ("-o", "-c"):
                skip_next = a == "-o"
                continue
            if a.startswith(("-I", "-D", "-std", "-isystem")) or a == "-isystem":
                keep.append(a)
        cmd = ["clang++", "--analyze", "-Xclang", "-analyzer-output=text",
               "-Xclang", f"-analyzer-checker={CHECKERS}", *keep, entry["file"], "-o", os.devnull]
        out = subprocess.run(cmd, cwd=entry["directory"], capture_output=True, text=True)
        text = (out.stdout + out.stderr).strip()
        if text:
            found += text.count("warning:")
            print(text)
    print(f"\nClang Static Analyzer: {found} warning(s) in {len(files)} changed file(s)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
