/* Mavryk Ledger application - Reset APDU instruction handling

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
#include "apdu_reset.h"

#include "apdu.h"
#include "baking_auth.h"
#include "globals.h"
#include "ui_reset.h"

#define G global.apdu.u.baking

/**
 * @brief Resets main and test level
 *
 *        Rounds are also reset to 0
 *
 * @return true
 */
static bool ok(void) {
    g_hwm.hwm.main.highest_level = G.reset_level;
    g_hwm.hwm.main.highest_round = 0;
    g_hwm.hwm.main.had_attestation = false;
    g_hwm.hwm.test.highest_level = G.reset_level;
    g_hwm.hwm.test.highest_round = 0;
    g_hwm.hwm.test.had_attestation = false;

    UPDATE_NVRAM;

    // Send back the response, do not restart the event loop
    io_send_sw(SW_OK);
    return true;
}

/**
 * Cdata:
 *   + (4 bytes) uint32: reset level
 */
int handle_reset(buffer_t* cdata) {
    mv_exc exc = SW_OK;

    MV_ASSERT_NOT_NULL(cdata);

    MV_ASSERT(buffer_read_u32(cdata, &G.reset_level, BE) && is_valid_level(G.reset_level),
              EXC_WRONG_VALUES);

    MV_ASSERT(cdata->size == cdata->offset, EXC_WRONG_LENGTH);

    return prompt_reset(ok, reject);

end:
    return io_send_apdu_err(exc);
}
