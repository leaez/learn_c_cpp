/*
 * Copyright (c) 2020 Intel Corporation
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

/**
 * @file fb_power.hpp
 *
 * Maintainer: Yu Yan <yu.yan@intel.com>
 *
 */

#pragma once

#include <RTmotion/fb/fb_base.hpp>

namespace RTmotion
{
/**
 * @brief Function block base for single axis motion
 */
class FbPower : public FunctionBlock
{
public:
  FbPower();
  virtual ~FbPower() = default;

  // Functions for addressing inputs
  void setExecute(BOOL execute);
  void setEnablePositive(BOOL enable_positive);
  void setEnableNegative(BOOL enable_negative);

  BOOL isEnabled();
  BOOL getPowerStatus();
  BOOL getPowerStatusValid();
  BOOL isError();
  MC_ERROR_CODE getErrorID();

  // Functions for execution
  virtual void runCycle() override;

protected:
  /// Inputs
  VAR_INPUT BOOL enable_;
  VAR_INPUT BOOL enable_positive_;
  VAR_INPUT BOOL enable_negative_;
};
}  // namespace RTmotion
