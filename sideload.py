#!/usr/bin/env python3
"""Send app.apdu directly to a connected Ledger device."""

import sys
from ledgerwallet.transport import enumerate_devices

APDU_FILE = "build/nanos2/bin/app.apdu"

devices = enumerate_devices()
if not devices:
    print("No Ledger device found. Connect your device and unlock it.")
    sys.exit(1)

dev = devices[0]
dev.open()

try:
    with open(APDU_FILE) as f:
        lines = [l.strip() for l in f if l.strip()]

    print(f"Sending {len(lines)} APDUs to {dev}...")
    for i, line in enumerate(lines):
        data = bytes.fromhex(line)
        print(f"  [{i+1}/{len(lines)}] CLA={data[0]:02x} INS={data[1]:02x}", end=" ", flush=True)
        # Longer timeout for APDUs that require user confirmation on device
        resp = dev.exchange(data, timeout=60000)
        sw = int.from_bytes(resp[-2:], "big")
        print(f"SW={sw:#06x}")
        # Stop on error SWs (not 0x9000 success or 0x6985 user pending)
        if sw >> 8 == 0x6D or sw >> 8 == 0x6E:
            print(f"ERROR: instruction not supported (SW={sw:#06x})")
            sys.exit(1)
        if sw not in (0x9000, 0x6985, 0x6200) and sw >> 12 not in (0x9, 0x6):
            print(f"Unexpected SW={sw:#06x}, continuing...")

    print("\nDone! The app should now appear on your device.")
finally:
    dev.close()
