/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/BallIntakeSub.h"
#include <ctre/Phoenix.h>
//Canid4 and Set Intake

BallIntakeSub::BallIntakeSub() : Subsystem("ExampleSubsystem") {}

void BallIntakeSub::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());

  BallIntakeMotor.reset(new ctre::phoenix::motorcontrol::can::VictorSPX(BALL_INTAKE_MOTOR_CAN_ID));
  intakeLimit.reset(new frc::DigitalInput(INTAKE_LIMIT_DIO));
}

// Put methods for controlling this subsystem
// here. Call these from Commands.


void BallIntakeSub::SetIntakeMotor(double speed){
  BallIntakeMotor->Set(ControlMode::PercentOutput, speed);
}

bool BallIntakeSub::isBallIn() {
  intakeLimit.get();
}