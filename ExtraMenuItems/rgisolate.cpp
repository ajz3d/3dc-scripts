// ===== rgisolate.cpp
// ===== Isolate Visible to UV-Set
//
// This source file is part of the 3dc-scripts project.
//
// Copyright (c) 2016 - 2021 Artur J. Żarek
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
const string ISOLATED_UVSET = "isolated";
const bool AUTO_SCALE = true;

void main()
{
	InstallToMenu("Retopo", "Isolate Visible to UV-Set");
	if(IsInRoom("Retopo"))
		run();
	else
		ShowFloatingMessage(
			"Script accessible from Retopo Room",
			FMSG_DURATION);
}

void run()
{
	UI ui;
	int uvidx = find_uvset(ISOLATED_UVSET);
	if(uvidx == -1){
		if(IsInRoom("Retopo"))
			SubstituteInputText(ISOLATED_UVSET);
		else
			return;
		ui("$add_new_uvset");
		RemoveModalDialogCallbacks();

	}
	move_to_uvset(ISOLATED_UVSET);
}

int find_uvset(string uvsetname)
{
	for(int i = 0; i < GetUVSetsCount(); i++){
		if(GetUVSetName(i) == uvsetname)
			return i;
	}
	return -1;
}

void add_uvset_cb()
{
	UI ui;
	SetEditBoxValue("$UV_set_params::UV_SetName", ISOLATED_UVSET);
	ui("$DialogButton#1");
}

void move_to_uvset(string uvsetname)
{
	UI ui;
	ui("$TopToolSelectAndOperate");
	SelectAllVisibleFaces();
	ui("$move_to_" + ISOLATED_UVSET);
	ui("$select_" + ISOLATED_UVSET);
	if(AUTO_SCALE){
		ui("$TopToolMarkSeams");
		ui("$AutoSc");
	}
}
