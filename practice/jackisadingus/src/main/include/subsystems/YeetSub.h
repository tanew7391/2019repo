/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <rev/CANSparkMax.h>
#include <rev/CANSparkMaxLowLevel.h>

class YeetSub : public frc::Subsystem {
 private:
 std::shared_ptr <rev::CANSparkMax> leftMotor1;
 std::shared_ptr <rev::CANSparkMax> rightMotor1;

  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

 public:
  YeetSub();
  void InitDefaultCommand() override;
  void drive(double rPower, double lPower);
};
