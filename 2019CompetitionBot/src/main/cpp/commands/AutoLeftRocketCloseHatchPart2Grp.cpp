/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoLeftRocketCloseHatchPart2Grp.h"
#include "commands/SetElevatorToHeightCmd.h"
#include "commands/CargoModeGrp.h"
#include "commands/FlipManipulatorGrp.h"
#include "commands/HatchModeGrp.h"
#include "commands/SilkyMotionCmd.h"


AutoLeftRocketCloseHatchPart2Grp::AutoLeftRocketCloseHatchPart2Grp() {

  AddSequential(new CargoModeGrp());
  AddParallel(new SilkyMotionCmd(std::vector<double> {-500,-4200}, std::vector<double> {33,-5}));
  AddSequential(new frc::WaitCommand(0.5));
  AddSequential(new FlipManipulatorGrp());
  AddParallel(new HatchModeGrp());
  AddSequential(new SetElevatorToHeightCmd(ELEVATOR_LOW_HATCH_HEIGHT_MM + 100.0));
  
}