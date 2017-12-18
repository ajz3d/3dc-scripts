// ===== export_to_separate_files.cpp
// ===== Export VoxTree layers to separate files.
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

const string fileExtensions = "*.obj;*.lwo;*.fbx;*.stl;*.ply;*.dae;*.wrl";
string targetPath;
string fileExtension;
float reductionPercentage = 0.;

void main(){
    // InstallToMenu("File.Export","To Separate Files");
    const string windowCaption = "Export Sculpt Objects to Separate Files";
    const string windowId = "";
    const string uiStrict = "Ignore Children of Hidden Parents";
    const string uiDecimate = "Reduction percentage:";
    const string msgDone = "Done.";
    const string msgProcessing = "Processing ";
    const string msgIgnoring = "Ignoring ";
    const string msgDestDir = "Select destination directory. File name is ignored, extension determines file format.";
    const string msgCancelled = "Export canceled.";
    const float messageDuration = 3.0;
    const float messageDurationLong = 99.0;
    bool strict = true;

    if(!IsInRoom("Sculpt"))
        ToRoom("Sculpt");

    AddCheckBox("strict");
    AddTranslation("strict", uiStrict);
    AddFloatSlider("reductionPercentage", 0., 99.9);
    AddTranslation("reductionPercentage", uiDecimate);
    if(!ModalDialogOkCancel(windowId, windowCaption))
        return;

    ShowFloatingMessage(msgDestDir, messageDurationLong, false);

    setPathAndExtension();

    if(FileDialogCancelPressed()){
        ShowFloatingMessage(msgCancelled, messageDuration, false);
        return;
    }

    SelectFirstVolume(strict);
    SetModalDialogCallback("decimationCallback");
    do{
        if(!CurVolumeIsEmpty() && GetVolumeVisibility()){
            ShowFloatingMessage(msgProcessing + GetCurVolume(), messageDurationLong, false);
            SetFileForFileDialogs(targetPath + GetCurVolume() + fileExtension);
            cmd("$ExportObject");
        } else{
            ShowFloatingMessage(msgIgnoring + GetCurVolume(), messageDurationLong, false);
        }
    } while(SelectNextVolume(strict));

    SetFileForFileDialogs("");
    RemoveModalDialogCallbacks();
    ShowFloatingMessage(msgDone, messageDuration, false);
}

void setPathAndExtension(){
    SaveDialog(fileExtensions, targetPath);
    fileExtension = "." + GetFileExtension(targetPath);
    targetPath = GetFilePath(targetPath);
}

void decimationCallback(){
  SetSliderValue("$DecimationParams::ReductionPercent", reductionPercentage);
  cmd("$DialogButton#1");
}
