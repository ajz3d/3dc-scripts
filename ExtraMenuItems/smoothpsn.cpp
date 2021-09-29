// ===== smoothpsn.cpp
// ===== Smooth Pose Selection(n)
//
// This source file is part of the 3dc-scripts project.
//
// Copyright (c) 2014 - 2021 Artur J. Żarek
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

const float FMSG_DURATION = 3.0;

void main()
{
	InstallToMenu("Voxels", "Smooth Pose Selection(n)");
	if(IsInTool("VOX_SCULPT_TOOL::SCULPT_TRANSPOSE"))
		smooth();
	else
		ShowFloatingMessage("You must be in Pose tool.", FMSG_DURATION);
}

void smooth()
{
	UI ui;
	const string wcap = "Smooth Pose Selection(n)";
	const string command = "$VoxelSculptTool::SmoothPoseSel";
	const string wid =
		"""
		Each step will be stacked on undo queue.
		How many smoothing steps?
		""";
	const uint16 min = 1;
	const uint16 max = 200;
	int steps = 1;
	AddIntSlider("steps", min, max);
	AddTranslation("steps", "Smoothing steps:");
	if(ModalDialogOkCancel(wid, wcap)){
		if(steps < 0)
			steps = 0;
		for(uint16 i = 0; i < steps; i++){
			ui(command);
			ShowFloatingMessage(i + "/" + steps, FMSG_DURATION);
		}
		ShowFloatingMessage("Done.", FMSG_DURATION);
	}
}
