/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoRightRocketCloseHatchPart2Grp.h"
#include "commands/SetElevatorToHeightCmd.h"
#include "commands/CargoModeGrp.h"
#include "commands/FlipManipulatorGrp.h"
#include "commands/HatchModeGrp.h" 
#include "commands/SilkyMotionCmd.h"
#include "commands/VisionHatchPickupGrp.h"
#include "commands/SetManipulatorAngleCmd.h"
#include "commands/LowVisionScoreGrp.h"
#include "commands/SetManipulatorIntakePowerCmd.h"
#include "commands/HatchGripperContractCmd.h"
#include "commands/ManipulatorInCmd.h"

AutoRightRocketCloseHatchPart2Grp::AutoRightRocketCloseHatchPart2Grp() {
  AddSequential(new SetManipulatorIntakePowerCmd(1.0));
  AddSequential(new frc::WaitCommand(0.15));
  AddSequential(new HatchGripperContractCmd());
  AddSequential(new ManipulatorInCmd(0.3));
  AddParallel(new SetManipulatorAngleCmd(-90.0));
  AddSequential(new SilkyMotionCmd(std::vector<double> {-1500, -2200, -1000}, std::vector<double> {60, 0, 30}));
  AddSequential(new VisionHatchPickupGrp());
  AddParallel(new SetManipulatorAngleCmd(50.0));
  AddSequential(new SilkyMotionCmd(std::vector<double> {1500, 1000}, std::vector<double> {-20, 48}));
  AddSequential(new LowVisionScoreGrp());
}
