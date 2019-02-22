/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include <frc/WPILib.h>
#include "Robot.h"
#include "subsystems/BallIntakeSub.h"
#include "Commands/CloseHatchPickupCmd.h"
#include "commands/KillEverythingCmd.h"
#include "commands/MilkyScoreGrp.h"
#include "commands/MilkyManipulatorCmd.h"
#include "commands/ClimbCmdGroup.h"
#include "commands/SetElevatorandManipulatorCmd.h"
#include "commands/SetIntakeArmAngleCmd.h"
#include "commands/IntakeBallFromRobotCmd.h"
#include "commands/IntakeBallGrp.h"
#include "commands/MultiButton1Cmd.h"
#include "commands/HatchModeGrp.h"
#include "commands/CargoModeGrp.h"

OI::OI() {
  // Process operator interface input here.
  driverController.reset(new frc::Joystick(DRIVER_CONTROLLER_PORT));
  driverController->SetXChannel(0);
  driverController->SetYChannel(1);
  driverController->SetZChannel(2);
  driverController->SetThrottleChannel(3);

  operatorController.reset(new frc::Joystick(OPERATOR_CONTROLLER_PORT));
  operatorController->SetXChannel(0);
  operatorController->SetYChannel(1);
  operatorController->SetZChannel(2);
  operatorController->SetThrottleChannel(3);

  // Driver controller buttons
  milkyManipulatorBtn.reset(new frc::JoystickButton(driverController.get(),MILKY_MANIPULATOR_BTN));
  milkyManipulatorBtn->WhileHeld( new MilkyScoreGrp());

  driverKillBtn1.reset(new frc::JoystickButton(driverController.get(), DRIVER_KILL_ONE_BTN));
  driverKillBtn1->WhenPressed(new KillEverythingCmd());

  driverKillBtn2.reset(new frc::JoystickButton(driverController.get(), DRIVER_KILL_TWO_BTN));
  driverKillBtn2->WhenPressed(new KillEverythingCmd());

  // Operator controller buttons
  elevatorToCargoShipHeightBtn.reset(new frc::JoystickButton(operatorController.get(), ELEVATOR_TO_CARGO_SHIP_HEIGHT_BTN));
  //elevatorToCargoShipHeightBtn->WhenPressed(new );

  elevatorToLowHeightBtn.reset(new frc::JoystickButton(operatorController.get(), ELEVATOR_TO_LOW_HEIGHT_BTN));
  //elevatorToLowHeightBtn->WhenPressed(new );
  
  elevatorToMediumHeightBtn.reset(new frc::JoystickButton(operatorController.get(), ELEVATOR_TO_MEDIUM_HEIGHT_BTN));
  //elevatorToMediumHeightBtn->WhenPressed(new );

  elevatorToHighHeightBtn.reset(new frc::JoystickButton(operatorController.get(), ELEVATOR_TO_HIGH_HEIGHT_BTN));
  //elevatorToHighHeightBtn->WhenPressed(new );

  hatchModeBtn.reset(new frc::JoystickButton(operatorController.get(), HATCH_MODE_BTN));
  hatchModeBtn->WhenPressed(new HatchModeGrp());

  cargoModeBtn.reset(new frc::JoystickButton(operatorController.get(), CARGO_MODE_BTN));
  cargoModeBtn->WhenPressed(new CargoModeGrp());

  flipManipulatorBtn.reset(new frc::JoystickButton(operatorController.get(), FLIP_MANIPULATOR_BTN));
  //elevatorToHighHeightBtn->WhenPressed(new );

  intakeHatchOrCargoBtn.reset(new frc::JoystickButton(operatorController.get(), INTAKE_HATCH_OR_CARGO_BTN));
  //intakeHatchOrCargoBtn->WhenPressed(new );

  multiCommand1Btn.reset(new frc::JoystickButton(operatorController.get(), MULTI_COMMAND_1_BTN));
  multiCommand1Btn->WhenPressed(new MultiButton1Cmd());

  operatorKillBtn1.reset(new frc::JoystickButton(operatorController.get(), OPERATOR_KILL_ONE_BTN));
  operatorKillBtn1->WhenPressed(new KillEverythingCmd());

  operatorKillBtn2.reset(new frc::JoystickButton(operatorController.get(), OPERATOR_KILL_TWO_BTN));
  operatorKillBtn2->WhenPressed(new KillEverythingCmd());



/*
  // These commands don't yet have a button

  climbModeBtn.reset(new frc::JoystickButton(operatorController.get(), CLIMB_MODE_BTN));
  climbModeBtn->WhileHeld(new ClimbCmdGroup());


  // These commands are likley obsolete

  hatchContractBtn.reset(new frc::JoystickButton(operatorController.get(), HATCH_CONTRACT_BTN));
  hatchContractBtn->WhileHeld(new CloseHatchPickupCmd());

  intakeBallBtn.reset(new frc::JoystickButton(operatorController.get(), INTAKE_BALL_BTN));
  intakeBallBtn->WhenPressed(new IntakeBallGrp());
  
  IntakeUntilLimitBtn.reset(new frc::JoystickButton(operatorController.get(), SET_INTAKE_MOTOR_BTN));
  IntakeUntilLimitBtn->WhenPressed(new IntakeBallFromRobotCmd());

  setManipulatorEncoderZeroBtn.reset(new frc::JoystickButton(operatorController.get(), SET_MANIPULATOR_ENCODER_ZERO_BTN));
  setManipulatorEncoderZeroBtn->WhenPressed(new SetElevatorandManipulatorCmd(0.0, 0.0));
*/

}

std::shared_ptr<frc::Joystick> OI::getDriverController() {
	return driverController;
}

std::shared_ptr<frc::Joystick> OI::getOperatorController() {
  return operatorController;
}

// Use the POV (i.e. D-Pad) as a command modifier
int OI::getOperatorShiftState() {
  int shift = 0;

  // POV position is reported in degrees with 0 deg being up and increasing clockwise
  // Positions between Up/down/left/right are ignored (i.e. 45 deg)
  switch(operatorController->GetPOV()) {
  case POV_INACTIVE:
    shift = 0;
    break;
  case POV_UP:
    shift = 1;
    break; 
  case POV_RIGHT:
    shift = 2;
    break;
  case POV_DOWN:
    shift = 3;
    break;
  case POV_LEFT:
    shift = 4;
    break;
  }

  return shift;
}
