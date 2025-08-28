# Copyright 2024 Functori <contact@functori.com>
# Copyright 2024 Trilitech <contact@trili.tech>

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""Module gathering common values used in tests."""

from pathlib import Path
from utils.account import Account, SigScheme, BipPath

TESTS_ROOT_DIR = Path(__file__).parent

DEFAULT_SEED = " ".join(['zebra'] * 24)

MV1_ACCOUNT = Account(
    "m/44'/1969'/0'/0'",
    SigScheme.ED25519,
    "edsk3j9sL3fqqgTa25t74q4wWC1RsgfNSkmKZKVNQhh8ZazZneLzMZ",
    2
)

MV2_ACCOUNT = Account(
    "m/44'/1969'/0'/0'",
    SigScheme.SECP256K1,
    "spsk3LvLaRN69uTDb6E3nkp8p1FkY6HVEoW1StaDZ5kBTkipDZTF3V",
    3
)

MV3_ACCOUNT = Account(
    "m/44'/1969'/0'/0'",
    SigScheme.SECP256R1,
    "p2sk3eAnsDAZNfHTXYtuwajdnxyE3n1swGknAJi5StPBAiCeu5CbhS",
    3
)

BIP32_MV1_ACCOUNT = Account(
    "m/44'/1969'/0'/0'",
    SigScheme.BIP32_ED25519,
    # Private key can't be retrieved because it's securely stored on the device
    "edpkuPErh5Lga9Ui39JPgfCHq2utQjGtKb3ig5NwM8yFnaetY1xD9f",
    2
)

LONG_MV1_ACCOUNT = Account(
    "m/9'/12'/13'/8'/78'",
    SigScheme.ED25519,
    "edsk3eZBgFAf1VtdibfxoCcihxXje9S3th7jdEgVA2kHG82EKYNKNm",
    3
)

DEFAULT_ACCOUNT = MV1_ACCOUNT

DEFAULT_ACCOUNT_2 = MV2_ACCOUNT

MV1_ACCOUNTS = [
    MV1_ACCOUNT,
    LONG_MV1_ACCOUNT,
    BIP32_MV1_ACCOUNT,
]

MV2_ACCOUNTS = [
    MV2_ACCOUNT,
]

MV3_ACCOUNTS = [
    MV3_ACCOUNT,
]

ACCOUNTS = MV1_ACCOUNTS + MV2_ACCOUNTS + MV3_ACCOUNTS

ZEBRA_ACCOUNTS = [
    MV1_ACCOUNT,
    MV2_ACCOUNT,
    MV3_ACCOUNT,
    BIP32_MV1_ACCOUNT,
]

EMPTY_PATH = BipPath.from_string("m")
