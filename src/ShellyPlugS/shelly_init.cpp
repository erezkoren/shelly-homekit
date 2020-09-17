/*
 * Copyright (c) 2020 Deomid "rojer" Ryabkov
 * All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "shelly_main.hpp"

namespace shelly {

void CreatePeripherals(std::vector<std::unique_ptr<Input>> *inputs,
                       std::vector<std::unique_ptr<Output>> *outputs,
                       std::vector<std::unique_ptr<PowerMeter>> *pms) {
  outputs->emplace_back(new OutputPin(1, 15, 1));
  auto *in = new InputPin(1, 13, 1, MGOS_GPIO_PULL_NONE, true);
  in->AddHandler(std::bind(&HandleInputResetSequence, in, 15, _1, _2));
  inputs->emplace_back(in);
  (void) pms;
}

void CreateComponents(std::vector<std::unique_ptr<Component>> *comps,
                      hap::Accessory *acc, hap::ServiceLabelService *sls,
                      HAPAccessoryServerRef *svr) {
  CreateHAPSwitch(1, mgos_sys_config_get_sw1(), mgos_sys_config_get_ssw1(),
                  comps, acc, sls, svr);
}

}  // namespace shelly