// ===== respn.cpp
// ===== Res+(n)
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
	InstallToMenu("Voxels", "Res+(n)");
	if(!IsSurface())
		respn();
	else
		ShowFloatingMessage("Layer is a surface.", FMSG_DURATION);
}

void respn()
{
	UI ui;
	const string wcap = "Increase voxel resolution";
	const string txt =
		"Select amount of steps that you want to increase the "
		"resolution of your current layer.\n"
		"Each step multiplies the triangle count roughly by 4. "
		"Be careful when using high values as "
		"it may result in the program, or your whole operating system, "
		"to become unresponsive.";
	const int min = 1;
	const int max = 5;
	int steps = 1;
	AddIntSlider("steps", min, max);
	bool isCancelPressed = !ModalDialogOkCancel(txt, wcap);
	if(!isCancelPressed){
		for(int i = 0; i < steps; i++){
			ShowFloatingMessage(
				"Step " + formatInt(i + 1, "l"),
				FMSG_DURATION);
			ui("$IncreaseResolution");
		}
	}else{
		ShowFloatingMessage("Aborted.", FMSG_DURATION);
	}
}
