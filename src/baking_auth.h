/* Mavryk Ledger application - Baking authorizing primitives

   Copyright 2024 TriliTech <contact@trili.tech>
   Copyright 2024 Functori <contact@functori.com>
   Copyright 2022 Nomadic Labs <contact@nomadic-labs.com>
   Copyright 2021 Ledger
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

#pragma once

#include "apdu.h"
#include "operations.h"
#include "types.h"

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Authorizes a key
 *
 * @param derivation_type: curve of the key
 * @param bip32_path: bip32 path of the key
 * @return mv_exc: exception, SW_OK if none
 */
mv_exc authorize_baking(derivation_type_t const derivation_type,
                        bip32_path_t const *const bip32_path);

/**
 * @brief Guards baking info and key pass required checks
 *
 * @param baking_info: baking info to check
 * @param key: key to check
 * @return mv_exc: exception, SW_OK if none
 */
mv_exc guard_baking_authorized(parsed_baking_data_t const *const baking_info,
                               bip32_path_with_curve_t const *const key);

/**
 * @brief Checks if a level is valid
 *
 * @param level: level
 * @return bool: if the level is valid
 */
bool is_valid_level(level_t level);

/**
 * @brief Stores baking info into the NVRAM
 *
 * @param in: baking info
 * @return mv_exc: exception, SW_OK if none
 */
mv_exc write_high_water_mark(parsed_baking_data_t const *const in);

/**
 * @brief Parse a block
 *
 * @param buf: input buffer containing the block
 * @param out: baking data output
 * @return bool: returns false if it is invalid
 */
bool parse_block(buffer_t *buf, parsed_baking_data_t *const out);

/**
 * @brief Parse a consensus operation
 *
 * @param buf: input buffer containing the consensus operation
 * @param out: baking data output
 * @param is_attestation: whether its an attestation or pre-attestation.
 * @return bool: returns false if it is invalid
 */
bool parse_consensus_operation(buffer_t *buf, parsed_baking_data_t *const out, bool is_attestation);
