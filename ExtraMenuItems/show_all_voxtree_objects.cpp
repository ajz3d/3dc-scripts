// ===== show_all_voxtree_objects.cpp
// ===== Show all VoxTree objects
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
    string currentVolume = GetCurVolume();
    SelectFirstVolume(false);
    do{
        ShowFloatingMessage("Revealing " + GetCurVolume(), 99., false);
        if(!GetVolumeVisibility())
            SetVolumeVisibility(true);
    } while(SelectNextVolume(false));
    SetCurVolume(currentVolume);
    ShowFloatingMessage("Done.", 3., false);
}
