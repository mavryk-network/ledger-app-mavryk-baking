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

"""Pytest configuration file."""

import pytest

from ledgered.devices import Device
from ragger.backend import BackendInterface
from ragger.conftest import configuration
from ragger.navigator import Navigator
from utils.client import MavrykClient
from utils.navigator import MavrykNavigator
from common import DEFAULT_SEED

configuration.OPTIONAL.CUSTOM_SEED = DEFAULT_SEED

# Pull all features from the base ragger conftest using the overridden configuration
pytest_plugins = ("ragger.conftest.base_conftest", )

@pytest.fixture(scope="function")
def client(backend: BackendInterface) -> MavrykClient:
    """Get a mavryk client."""
    return MavrykClient(backend)

@pytest.fixture(scope="function")
def mavryk_navigator(
        backend: BackendInterface,
        device: Device,
        client: MavrykClient,
        navigator: Navigator,
        golden_run: bool,
        test_name: str) -> MavrykNavigator:
    """Get a mavryk navigator."""
    return MavrykNavigator(backend, device, client, navigator, golden_run, test_name)
