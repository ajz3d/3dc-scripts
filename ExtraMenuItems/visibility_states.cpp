// ===== visibility_states.cpp
// ===== Manage VoxTree visibility states
//
// This source file is part of the 3dc-scripts project.
// https://github.com/ajz3d/3dc-scripts/
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

/*
## ---------------------------------------------------------------------------
## Script Name                :        ajz_visibilityGroups.txt
## Version                        :        1.00
## Created                        :        May 25 2014
## Last Modification    :        May 28 2014
## Author                         :        Artur J. Zarek
## Contact                        :        ajz3dee@gmail.com
## ---------------------------------------------------------------------------
## DESCRIPTION: The script will store/restore visibility and ghosting states
## of volumes in the VoxTree.
## ---------------------------------------------------------------------------
*/
// [USER-CUSTOMISABLE VARIABLES]
// Shows a popup window whenever saved VoxTree is different from the current one.
const bool showMissingVolumesDialog = false; // Default: false
// [END OF USER-CUSTOMISABLE VARIABLES]

string ajz_vgrps_filePath;
array<string> ajz_vgrps_layer;
array<bool> ajz_vgrps_visible;
array<bool> ajz_vgrps_ghosted;

void main(){
    const string windowCaption = "VoxTree Visibility Groups";
    const string windowId = "";
    const string clipboardOperations = "Clipboard:";
    const string fileOperations = "File:";

    AddTextField(clipboardOperations, 0);
    AddTextField("", 0);
    Columns(2);
    AddButton("storeGroup");
    AddTranslation("storeGroup", "Copy");
    AddButton("restoreGroup");
    AddTranslation("restoreGroup", "Paste");
    AddTextField("", 0);
    AddDelimiter();
    AddTextField("", 0);
    AddTextField(fileOperations, 0);
    AddTextField("", 0);
    Columns(2);
    AddButton("saveGroup");
    AddTranslation("saveGroup", "Save");
    AddButton("loadGroup");
    AddTranslation("loadGroup", "Load");
    ModalDialog(windowId, windowCaption);
}

array<string> getEmptyArray(array<string> arr){
    while(arr.length() > 0)
        arr.removeLast();
    return arr;
}

array<bool> getEmptyArray(array<bool> arr){
    while(arr.length() > 0)
        arr.removeLast();
    return arr;
}

void storeGroup(){
    //    Clear arrays first
    ajz_vgrps_layer = getEmptyArray(ajz_vgrps_layer);
    ajz_vgrps_visible = getEmptyArray(ajz_vgrps_visible);
    ajz_vgrps_ghosted = getEmptyArray(ajz_vgrps_ghosted);
    // Remember currently selected volume
    string curVolume = GetCurVolume();
    // Begin storing to global variables
    SelectFirstVolume(false);
    ajz_vgrps_layer.insertLast(GetCurVolume());
    ajz_vgrps_visible.insertLast(GetVolumeVisibility());
    ajz_vgrps_ghosted.insertLast(GetVolumeGhosting());
    while(SelectNextVolume(false)){
        ShowFloatingMessage("Processing " + GetCurVolume() + "...", 3.0, true);
        ajz_vgrps_layer.insertLast(GetCurVolume());
        ajz_vgrps_visible.insertLast(GetVolumeVisibility());
        ajz_vgrps_ghosted.insertLast(GetVolumeGhosting());
    }
    SetCurVolume(curVolume);
    ShowFloatingMessage("Done.", 3.0, true);
}

void restoreGroup(){
    string errorLog;
    string curVolume = GetCurVolume();
    if(ajz_vgrps_layer.length() > 0 and ajz_vgrps_visible.length() > 0 and ajz_vgrps_ghosted.length() > 0){
        for(uint16 i = 0; i < ajz_vgrps_layer.length(); i++){
            if(SetCurVolume(ajz_vgrps_layer[i])){
                ShowFloatingMessage("Processing " + GetCurVolume() + "...", 3.0, true);
                SetVolumeVisibility(ajz_vgrps_visible[i]);
                SetVolumeGhosting(ajz_vgrps_ghosted[i]);
            }else{
                errorLog+=ajz_vgrps_layer[i]+"\n";
            }
        }
        if(errorLog.length() > 0){
            if(showMissingVolumesDialog){
                displayMissingVolumesDialog();
            }
            print("\nMISSING VOLUMES:\n");
            print("\n" + errorLog);
        }
        SetCurVolume(curVolume);
        if(errorLog.length() > 0)
            ShowFloatingMessage("Warning: Current VoxTree is different from the saved one.", 3.0, true);
        else
            ShowFloatingMessage("Done.", 3.0, true);
    }else{
        ShowFloatingMessage("Nothing to restore.", 5.0, true);
    }
}

void saveGroup(){
    if(SaveDialog("visGroups", ajz_vgrps_filePath)){
        string curVolume = GetCurVolume();
        file f;
        f.open(ajz_vgrps_filePath, "w");
        SelectFirstVolume(false);
        ShowFloatingMessage("Processing " + GetCurVolume() + "...", 3.0, true);
        f.writeString(GetCurVolume() + "\n");
        f.writeString(GetVolumeVisibility() + "\n");
        f.writeString(GetVolumeGhosting() + "\n");
        while(SelectNextVolume(false)){
            ShowFloatingMessage("Processing " + GetCurVolume() + "...", 3.0, true);
            f.writeString(GetCurVolume() + "\n");
            f.writeString(GetVolumeVisibility() + "\n");
            f.writeString(GetVolumeGhosting() + "\n");
        }
        f.close();
        SetCurVolume(curVolume);
        ShowFloatingMessage("Done.", 2.0, true);
    }
}

bool stringToBoolean(string s){
    if(s == "true")
        return true;
    else    // We are all adults here.
        return false;
}

void loadGroup(){
    string errorLog;
    if(OpenDialog("visGroups", ajz_vgrps_filePath)){
        string curVolume = GetCurVolume();
        array<string> layer;
        array<bool> visible;
        array<bool> ghosted;

        file f;
        string feed;
        f.open(ajz_vgrps_filePath, "r");
        uint16 entries = 0;
        // Loop: read lines from file
        while(!f.isEndOfFile()){
            ShowFloatingMessage("Reading file...", 3.0, true);
            string temp;
            temp = f.readLine(); //#
            if(temp.length() > 0){    // To prevent crashing.
                temp.resize(temp.length() - 1); // Strips the line from EOL sign.
                layer.insertLast(temp);
                temp = f.readLine(); //#
                temp.resize(temp.length() - 1);
                visible.insertLast(stringToBoolean(temp));
                temp = f.readLine(); //#
                temp.resize(temp.length() - 1);
                ghosted.insertLast(stringToBoolean(temp));
            }
        }
        // Restore state
        if((layer.length() == visible.length() and visible.length() == ghosted.length()) and layer.length() > 0){
            for(uint16 i=0; i<layer.length(); i++){
                if(SetCurVolume(layer[i])){
                    ShowFloatingMessage("Processing " + GetCurVolume() + "...", 3.0, true);
                    SetVolumeVisibility(visible[i]);
                    SetVolumeGhosting(ghosted[i]);
                }else{
                    errorLog+=layer[i] + "\n";
                }
            }
            if(errorLog.length() > 0){
                if(showMissingVolumesDialog){
                    displayMissingVolumesDialog();
                }
                print("\nMISSING VOLUMES:\n");
                print("\n" + errorLog);
            }
        }
        if(errorLog.length() > 0)
            ShowFloatingMessage("Warning: Current VoxTree is different from the saved one.", 3.0, true);
        else
            ShowFloatingMessage("Done.", 3.0, true);
        SetCurVolume(curVolume);
    }
}
void displayMissingVolumesDialog(){
    const string ID = """
Some volumes were missing.
There are two possible reasons:
    1. You deleted or renamed them.
    2. You tried to load a saved state from a different scene.

Check the execution log for full log of missing volumes.
    """;
    const string CAPTION = "Warning!";
    ModalDialog(ID, CAPTION);
}
