// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/Drivetrain.h"

class TeleopTankDrive
    : public frc2::CommandHelper<frc2::CommandBase, TeleopTankDrive> {
 public:
  TeleopTankDrive(Drivetrain* subsystem,
                    std::function<double()> leftSpeedSupplier,
                    std::function<double()> rightSpeedSupplier);
  void Execute() override;

 private:
  Drivetrain* m_drive;
  std::function<double()> m_leftSpeedSupplier;
  std::function<double()> m_rightSpeedSupplier;
};
