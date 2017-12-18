// ===== multi_res_plus.cpp
// ===== Multiple Res+
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
	const string windowTitle = "Increase voxel resolution";
	const string windowText = """Select amount of steps that you want to increase
	the resolution of your current layer.
	Each step multiplies the triangle count by ~4.

	WARNING! Be very careful when using high values
	as it may result in program or the whole system
	becoming unresponsive.""";
	const string windowSurfaceTitle = "Error!";
	const string windowSurfaceText = "Make sure your currently selected voxtree "
	"layer is in voxels mode.";

	const int minSteps = 1;
	const int maxSteps = 5;
	int steps = 1;

	if(IsSurface())
		ModalDialog(windowSurfaceText, windowSurfaceTitle);
	else{
		AddIntSlider("steps", minSteps, maxSteps);

		bool isCancelPressed = !ModalDialogOkCancel(windowText, windowTitle);

		if(!isCancelPressed){
			for(int i = 0; i < steps; i++){
				SetModalDialogCallback("warningCallback");
				ShowFloatingMessage("Step " + formatInt(i, "l"), 99.0, false);
				cmd("$[Page4]Res+");
			}
		}
		ShowFloatingMessage("Done.", 5.0, false);
	}
    RemoveModalDialogCallbacks();
}


void warningCallback(){
	cmd("$DialogButton#1");
}
