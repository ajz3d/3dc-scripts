// ===== retopo_group_move_back.cpp
// ===== Move retopo group back to default UV set.
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

void main(){
    cmd("$select_" + isolatedUVSetName);

    if(IsInRoom("Retopo")){
        SelectAllVisibleFaces();
    }
    /* Unfortunately it is not possible to determine what is the name of the currently selected  */
    cmd("$move_to_default");
    cmd("$select_default");
    cmd("$[Page2]Mark Seams");
    cmd("$[Page2]Auto Scale");
    Step(1);
}
