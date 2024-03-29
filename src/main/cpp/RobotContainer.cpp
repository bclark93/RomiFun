// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/PrintCommand.h>
#include <frc2/command/button/Button.h>

#include "commands/TeleopArcadeDrive.h"
#include "commands/TeleopTankDrive.h"

RobotContainer::RobotContainer() {
  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  // Also set default commands here
  //m_drive.SetDefaultCommand(TeleopArcadeDrive(
  //    &m_drive, [this] { return -m_controller.GetRawAxis(1)*kXaxisMultiplier; },
  //    [this] { return m_controller.GetRawAxis(4)*kZaxisMultiplier; }));
  m_drive.SetDefaultCommand(TeleopTankDrive(
      &m_drive, [this] { return -m_controller.GetRawAxis(1); },
      [this] { return -m_controller.GetRawAxis(5); }));

  // Setup controller buttons
  m_controllerButtonA.WhenPressed(TurnDegrees(0.5, 180_deg, &m_drive));
  //m_controllerButtonX.WhenPressed(TurnDegrees(-0.5, 90_deg, &m_drive));
  //m_controllerButtonB.WhenPressed(TurnDegrees(0.5, 90_deg, &m_drive));
  m_controllerButtonLB.WhenPressed(TurnDegrees(-0.5, 90_deg, &m_drive));
  m_controllerButtonRB.WhenPressed(TurnDegrees(0.5, 90_deg, &m_drive));
  // WIP: Turn on Yellow LED when Y Button is pressed
  //m_controllerButtonY.WhenPressed(m_onboardIO.SetYellowLed(true))
  //    .WhenReleased(m_onboardIO.SetYellowLed(false));
  // WIP: Toggle zAxis multiplier when pressed
  //m_controllerButtonRS.ToggleWhenPressed(ToggleRotationSpeed());
  
  // Example of how to use the onboard IO
  m_onboardButtonA.WhenPressed(frc2::PrintCommand("Button A Pressed"))
      .WhenReleased(frc2::PrintCommand("Button A Released"));

  // Setup SmartDashboard options.
  m_chooser.SetDefaultOption("Auto Routine Distance", &m_autoDistance);
  m_chooser.AddOption("Auto Routine Time", &m_autoTime);
  frc::SmartDashboard::PutData("Auto Selector", &m_chooser);
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  return m_chooser.GetSelected();
}
