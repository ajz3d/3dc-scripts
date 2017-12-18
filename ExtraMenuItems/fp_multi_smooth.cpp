// ===== fp_multismooth.cpp
// ===== MultiSmooth Freeze/Pose Selection
//
// This source file is part of the 3dc-scripts project.
//
// Copyright (c) 2014 - 2017 Artur J. Żarek
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

void main(){
	const string windowCaptionPrefix = "Multi-smooth ";
	const array<string> tool = {
		"pose ",
		"freeze "
	};
	const array<string> command = {
		"$VoxelSculptTool::SmoothPoseSel",
		"$MENU_BLUR_FREEZE"
	};
	const string windowCaptionSuffix = "selection.";
	const string windowId =
	"""
	How many smoothing steps?
	WARNING! Each step will be stacked on undo queue.
	""";
	const uint16 min = 1;
	const uint16 max = 250;
	uint16 steps = 1;
	uint16 type = 0;

	if(IsInTool("VOX_SCULPT_TOOL::SCULPT_TRANSPOSE"))
		type = 0;
	else if(IsInTool("VOX_SCULPT_TOOL::SCULP_SFREEZE"))
		type = 1;
	else
		type = 10;
	print ("type = " + type + "\n");
	if (type == 0 || type == 1){
		AddIntSlider("steps", min, max);
		AddTranslation("steps", "Smoothing steps:");
		if(ModalDialogOkCancel(windowId, windowCaptionPrefix + tool[type] + windowCaptionSuffix)){
			for(uint16 i = 0; i < steps; i++){
				cmd(command[type]);
				ShowFloatingMessage(i + "/" + steps, 1.0, false);
			}

			ShowFloatingMessage("Done.", 3.0, false);
		}
		print(GetCurrentToolID());
	}else
		ShowFloatingMessage("You must be in Pose or Freeze tool.", 3.0, false);
}
