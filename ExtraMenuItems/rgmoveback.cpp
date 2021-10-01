// ===== rgmoveback.cpp
// ===== Move retopo group back to default UV set.
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

const string ISOLATED_UVSET = "isolated";
const string DEFAULT_UVSET = "Default";
const float FMSG_DURATION = 3.0;

void main()
{
	InstallToMenu("Retopo", "Move Back from Isolated UV-Set");
	if(IsInRoom("Retopo")){
		run();
	}else{
		ShowFloatingMessage(
			"Script accessible from Retopo Room.",
			FMSG_DURATION);
	}
}

void run()
{
	UI ui;
	if(find_uvset(DEFAULT_UVSET) == -1){
		SubstituteInputText(DEFAULT_UVSET);
		ui("$add_new_uvset");
	}
	ui("$select_" + ISOLATED_UVSET);
	SelectAllVisibleFaces();
	ui("$TopToolMarkSeams");
	ui("$move_to_" + DEFAULT_UVSET);
	ui("$select_" + DEFAULT_UVSET);
}

int find_uvset(string uvsetname)
{
	for(int i = 0; i < GetUVSetsCount(); i++){
		if(GetUVSetName(i) == uvsetname)
			return i;
	}
	return -1;
}
