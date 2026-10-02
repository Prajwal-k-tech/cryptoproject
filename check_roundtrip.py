"""Run the CLI round-trip regression checks with C++ sanitizers."""
import random
import subprocess
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent


def main():
    rng = random.Random(20261002)
    alphabet = [value for value in range(256) if value != 10]
    cases = [b"", b"hello", b"with spaces", "Pokémon".encode(), bytes(alphabet)]
    cases.extend(bytes(rng.choice(alphabet) for _ in range(n)) for n in range(601))
    cases.append(b"A" * 10000)
    with tempfile.TemporaryDirectory(prefix="encoding-check-") as directory:
        outputs = []
        for source, name in [("encrypt.cpp", "encode"), ("decrypt.cpp", "decode")]:
            executable = str(Path(directory) / name)
            subprocess.run([
                "g++", "-std=c++17", "-fsanitize=undefined,bounds",
                "-fno-sanitize-recover=all", str(ROOT / source), "-o", executable,
            ], check=True)
            outputs.append(executable)
        encode, decode = outputs
        for data in cases:
            encoded = subprocess.run([encode], input=data + b"\n", capture_output=True, check=True)
            decoded = subprocess.run([decode], input=encoded.stdout + b"\n", capture_output=True, check=True)
            assert decoded.stdout == data, f"Round trip failed for length {len(data)}"
        for data in [b"g", b"gg", b"zzzzzz"]:
            result = subprocess.run([decode], input=data + b"\n", capture_output=True)
            assert result.returncode != 0 and result.stderr, "Malformed input was accepted"
    print(f"{len(cases)} round trips passed; malformed input rejected; sanitizers clean")


if __name__ == "__main__":
    main()
