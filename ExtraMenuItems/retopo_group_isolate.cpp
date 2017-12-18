// ===== retopo_group_isolate.cpp
// ===== Isolate visible retopo groups.
//
// This source file is part of the 3dc-scripts project.
//
// Copyright (c) 2016 - 2017 Artur J. Żarek
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


string isolatedUVSetName = "isolatedUVSet";
string originalUVSetName = "";
bool useAutoScaleAfterIsolating = true;


int findUVSet(string uvSetName){
/*  Looks for a specific UV-set name.
    Returns its index if it finds the UV-set, or -1 if it doesn't. */

    for(int index = 0; index < GetUVSetsCount(); index++){
        if(GetUVSetName(index) == uvSetName)
            return index;
    }
    return -1;
}


void moveRetopoGroupToUVSet(string uvSetName){
/*  Moves contents of the active retopo group to a specified UV-set.
    Then, it selects the UV-set and performs an UV auto-scale operation. */
    //SelectAllVisibleFaces();
    if(IsInRoom("Retopo")){
        SelectAllVisibleFaces();
        Step(1);
    }
    cmd("$move_to_" + uvSetName);
    cmd("$select_" + uvSetName);
    if(IsInRoom("Retopo"))
        if(useAutoScaleAfterIsolating){
            cmd("$[Page2]Mark Seams");
            cmd("$[Page2]Auto Scale");
        }
    else
        if(useAutoScaleAfterIsolating)
            cmd("$[Page3]Auto Scale");
    Step(1);
}


void addUVSetDialogCallback(){
    SetEditBoxValue("$UV_set_params::UV_SetName", isolatedUVSetName);
    cmd("$DialogButton#1");
}


void main(){
    // Find isolatedUVSetName
    int uvSetIndex = findUVSet(isolatedUVSetName);
    // If not found - create it:
    if(uvSetIndex == -1){
        if(IsInRoom("UV"))
            SetModalDialogCallback("addUVSetDialogCallback");
        else if(IsInRoom("Retopo"))
            SubstituteInputText(isolatedUVSetName);
        else
            return;
        cmd("$add_new_uvset");
        if(IsInRoom("UV"))
            RemoveModalDialogCallbacks();
    }
    moveRetopoGroupToUVSet(isolatedUVSetName);
}
