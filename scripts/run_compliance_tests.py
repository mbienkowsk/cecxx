import argparse
import asyncio
import os
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from dataclasses import dataclass
from enum import StrEnum
from pathlib import Path

from termcolor import colored

# Orginal CEC implementation (which serves as a oracle in complaiance tests) leaks memory and it breaks fuzztest test runner.
_DISABLE_ASAN = {"ASAN_OPTIONS": "detect_leaks=0"}

_USAGE = """example:
    python scripts/run_compliance_tests.py\
        --target artifacts/bin/compliance-tests\
        --edition 2013 2014 2017\
        --duration 3\
        --jobs 20
"""

ExitCode = int
Seconds = int


class CecEdition(StrEnum):
    CEC2013 = "2013"
    CEC2014 = "2014"
    CEC2017 = "2017"


@dataclass
class FuzzTest:
    test_group: str
    test_name: str

    @property
    def edition(self) -> CecEdition:
        return CecEdition(re.findall(r"\d+", self.test_group)[0])

    @property
    def dimension(self) -> int:
        return int(re.findall(r"D(\d+)", self.test_name)[0])

    @property
    def name(self) -> str:
        return f"CEC/{self.edition}/DIM/{self.dimension}"

    def __str__(self) -> str:
        return f"{self.test_group}.{self.test_name}"


def open_range(start, end):
    return range(start + 1, end)


def run_test(
    target: Path, test: FuzzTest, duration: Seconds
) -> tuple[FuzzTest, ExitCode]:
    print(f"Running compliance test [{test.name}] for next {duration}s...")
    p = subprocess.run(
        [
            f"{target}",
            "--gtest_filter",
            str(test),
            "--fuzz_for",
            f"{duration}s",
            "--gtest_brief",
            "1",
        ],
        env=os.environ | _DISABLE_ASAN,
        stdout=subprocess.DEVNULL,
        stderr=subprocess.STDOUT,
    )
    return (test, p.returncode)


def parse_fuzztest_list(input: list[str]) -> list[FuzzTest]:
    header_pos = [
        index for index, entry in enumerate(input) if "ComplianceTest" in entry
    ]
    header_pos.append(len(input))
    tests = []
    for start, end in zip(header_pos, header_pos[1:]):
        grp = input[start].removesuffix(".")
        tests.append([FuzzTest(grp, input[i]) for i in open_range(start, end)])
    return [t for ts in tests for t in ts]


async def get_fuzztests(target: Path) -> list[FuzzTest]:
    p = await asyncio.create_subprocess_exec(
        f"{target}", "--gtest_list_tests", stdout=asyncio.subprocess.PIPE
    )
    stdout, _ = await p.communicate()
    return parse_fuzztest_list(stdout.decode().split())


async def run_compliance_tests(args: list[str]) -> None:
    parser = argparse.ArgumentParser(
        prog="CEC compliance test running helper.", epilog=_USAGE
    )
    parser.add_argument(
        "-t",
        "--target",
        default="./build-clang++/test/compliance/cecxx-compliance-tests",
        type=Path,
        help="Path to compliance test executable.",
    )
    parser.add_argument(
        "-e",
        "--edition",
        nargs="+",
        default=[e.value for e in CecEdition],
        help="List of CEC editions for which compliance tests will be run.",
    )
    parser.add_argument(
        "-d",
        "--duration",
        type=int,
        default=1,
        help="Duration of single compliance test in seconds. The longer duration, the more examples will be covered.",
    )
    parser.add_argument(
        "-j",
        "--jobs",
        default=1,
        type=int,
        help="Number of simultaneously executed tests.",
    )
    parsed = parser.parse_args(args)

    tests = await get_fuzztests(parsed.target)
    if not tests:
        print(f"No fuzz tests for target [{parsed.target}].")
    with ThreadPoolExecutor(max_workers=parsed.jobs) as tp_ex:
        loop = asyncio.get_event_loop()
        futures = [
            loop.run_in_executor(tp_ex, run_test, parsed.target, t, parsed.duration)
            for t in tests
            if t.edition in parsed.edition
        ]
        for test, excode in await asyncio.gather(*futures):
            color = "green" if not excode else "red"
            print(
                colored(
                    f"Test [{test.name}] finished with exit code [{excode}].", color
                )
            )


if __name__ == "__main__":
    try:
        asyncio.run(run_compliance_tests(sys.argv[1:]))
    except Exception as err:
        print(f"Failed to run compliance tests. Error: {err}")
        sys.exit(os.EX_SOFTWARE)
    sys.exit(os.EX_OK)
