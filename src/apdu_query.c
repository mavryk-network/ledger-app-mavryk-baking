/* Tezos Ledger application - Query APDU instruction handling

   Copyright 2024 TriliTech <contact@trili.tech>
   Copyright 2024 Functori <contact@functori.com>
   Copyright 2023 Ledger
   Copyright 2022 Nomadic Labs <contact@nomadic-labs.com>
   Copyright 2019 Obsidian Systems

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*/

#include "apdu_query.h"

#include "apdu.h"
#include "baking_auth.h"
#include "bip32.h"
#include "globals.h"
#include "memory.h"
#include "os_cx.h"
#include "to_string.h"
#include "ui.h"
#include "write.h"

#include <string.h>

int handle_query_all_hwm(void) {
    uint8_t resp[5u * sizeof(uint32_t)] = {0};
    size_t offset = 0;

    write_u32_be(resp, offset, g_hwm.hwm.main.highest_level);
    offset += sizeof(uint32_t);

    write_u32_be(resp, offset, g_hwm.hwm.main.highest_round);
    offset += sizeof(uint32_t);

    write_u32_be(resp, offset, g_hwm.hwm.test.highest_level);
    offset += sizeof(uint32_t);

    write_u32_be(resp, offset, g_hwm.hwm.test.highest_round);
    offset += sizeof(uint32_t);

    write_u32_be(resp, offset, g_hwm.main_chain_id.v);
    offset += sizeof(uint32_t);

    return io_send_response_pointer(resp, offset, SW_OK);
}

int handle_query_main_hwm(void) {
    uint8_t resp[2u * sizeof(uint32_t)] = {0};
    size_t offset = 0;

    write_u32_be(resp, offset, g_hwm.hwm.main.highest_level);
    offset += sizeof(uint32_t);

    write_u32_be(resp, offset, g_hwm.hwm.main.highest_round);
    offset += sizeof(uint32_t);

    return io_send_response_pointer(resp, offset, SW_OK);
}

int handle_query_auth_key(void) {
    tz_exc exc = SW_OK;
    uint8_t resp[1u + (MAX_BIP32_PATH * sizeof(uint32_t))] = {0};
    size_t offset = 0;

    uint8_t const length = g_hwm.baking_key.bip32_path.length;
    TZ_ASSERT(length <= NUM_ELEMENTS(g_hwm.baking_key.bip32_path.components), EXC_WRONG_LENGTH);

    resp[offset] = length;
    offset++;

    for (uint8_t i = 0; i < length; ++i) {
        write_u32_be(resp, offset, g_hwm.baking_key.bip32_path.components[i]);
        offset += sizeof(uint32_t);
    }

    return io_send_response_pointer(resp, offset, SW_OK);
end:
    return io_send_apdu_err(exc);
}

int handle_query_auth_key_with_curve(void) {
    tz_exc exc = SW_OK;
    uint8_t resp[2u + (MAX_BIP32_PATH * sizeof(uint32_t))] = {0};
    size_t offset = 0;

    uint8_t const length = g_hwm.baking_key.bip32_path.length;
    TZ_ASSERT(length <= NUM_ELEMENTS(g_hwm.baking_key.bip32_path.components), EXC_WRONG_LENGTH);

    int derivation_type = unparse_derivation_type(g_hwm.baking_key.derivation_type);
    TZ_ASSERT(derivation_type >= 0, EXC_REFERENCED_DATA_NOT_FOUND);

    resp[offset] = derivation_type;
    offset++;

    resp[offset] = length;
    offset++;

    for (uint8_t i = 0; i < length; ++i) {
        write_u32_be(resp, offset, g_hwm.baking_key.bip32_path.components[i]);
        offset += sizeof(uint32_t);
    }

    return io_send_response_pointer(resp, offset, SW_OK);
end:
    return io_send_apdu_err(exc);
}
