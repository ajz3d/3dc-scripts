// ===== blushfr.cpp
// ===== Blur/Sharpen Frozen Area(n)
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
	InstallToMenu("Freeze", "Blur/Sharpen Frozen Area");
	if(IsSurface())
		gui();
	else
		ShowFloatingMessage("You must be in surface mode.", FMSG_DURATION);
}

void gui()
{
	UI ui;
	const string wcap = "Blur/Sharpen Frozen Area";
	const string wid =
		"Negative values will sharpen the frozen area.\n";
		"How many steps?";
	const int16 min = -100;
	// TODO: Try uint16 for max.
	const int16 max = 100;
	int s = 1;
	AddIntSlider("s", min, max);
	AddTranslation("s", "Steps:");
	if(ModalDialogOkCancel(wid, wcap)){
		if(s != 0)
			blush(s, ui);
	}
}

void blush(int s, UI ui)
{
	bool n = false;
	if(s < 0){
		n = true;
		s = abs(s);
	}
	for(uint16 i = 1; i <= s; i++){
		pmsg(i, s);
		if(n)
			ui("$MENU_SHARPEN_FREEZE");
		else
			ui("$MENU_BLUR_FREEZE");
	}
	ShowFloatingMessage("Done.", FMSG_DURATION);
}

void pmsg(uint16 i, int s)
{
	ShowFloatingMessage(i + "/" + s, FMSG_DURATION);
}
