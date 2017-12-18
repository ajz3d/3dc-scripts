# 3D Coat Scripts
This is a set of workflow-enhancing 3D Coat scripts that not only can save some of your production time on tasks that are tedious or repetitive to perform, but also offers some workflow-specific enhancements.

## Installation
### MS Windows
1. Clone or download the repository to your storage device.
2. Unpack the contents of ```.\ExtraMenuItems``` directory from the archive to ```%USERPROFILE%\Documents\3D-CoatV48\Scripts\ExtraMenuItems\``` path (of course, replace ```3D-CoatV48``` with your current 3DC configuration directory name). Create this path if it doesn't exist.

## Scripts
### Export to Separate Files
Did you ever wonder why you can export the whole VoxTree to a single file, but not each sculpt object to its own? You don't have to worry about it any more because this script will do it for you. When you launch it, it will ask you about two things.
1. Some general settings:
    - ignore children of hidden parents (default = true) - pretty self-explanatory. If ```true```, all children of a hidden parent, regardless of the fact that they are visible or not, will not be exported. If ```false```, the parent may be hidden, but the script will also check for *visible* flag of each of its children. Any "visible" child will be exported.
    - reduction percentage (Default = 0.0) - determine the decimation factor of each exported object. Keep at zero to preserve your objects as they are.
2. The path to which all files will be written to. The filename is not important so you can type in whatever you want in that text field as it will be replaced by object names. What matters is the path to directory. You can select all of the geometry file formats that 3D Coat supports.

The script is accessible through *File➝Export➝To Separate Files*.

### Hide/Show All Retopo Groups
Those two scripts work in the *Retopo* room and they do exactly what their names imply: hide and show all retopo groups.
The caveat is that the implementation of ```SetRetopoLayerVisibility()``` function in 3D Coat is somewhat buggy because it affects the visibility state of retopo objects in the *Retopo Objects* list, but it doesn't affect them in the viewport. In order to enforce the viewport update after running either one of those scripts, you will need to manually click the eye icon of any retopo objects. Still it's way faster than having to click through gazillion of retopo groups in order to hide them. ```ALT+click``` doesn't help in some circumstances...

The script is accessible through *Retopo➝Hide all* and *Retopo➝Show all*.

### Isolate to/Move Back from UV-Set
Two scripts that might be very useful when unwrapping a model for texturing. If your asset consists of multiple retopo groups, managing and inspecting its UVs can be problematic because the puny human perception makes catching wrongly unwrapped islands a very time consuming and error-prone process when those islands are located in a forest of wrapped garbage.

Isolating to UV-Set will move all visible retopo groups to a UV-set called *isolatedUVSet*. UVs will be automatically auto-scaled within that set in sake of better visibility. Unwrap the mesh and launch the *Move back from isolation* script.

*Move back from isolation* will move all geometry from *isolatedUVSet* back to UV set called the *default* and *Auto Scale* this whole set. Initially I wanted to store the origin UV set of each isolated geometry in some variable, but it turned out that it is impossible to determine via scripting to which UV set a visible retopo groups belongs to. So this is a limitation of this script for now: a UV set called *default* **must** be present in the retopo room. Otherwise the move operation will fail and the geometry will stay in the *isolatedUVSet*.

In my workflow I first put everything in a single UV set. I used to have a script for that but now you can use *Unify UV* tool to perform this action. Then I delete all unused UV sets and keep just the one called the *default* (if the name is different, I rename it to *default*). Then I'm going through all of the retopo groups by hiding everything but the group I want to unwrap. I invoke the *Isolate to UV set* script and unwrap the active group. After I'm done, I bring it back to *default* UV set by launching *Move back from isolation*. Repeat for all retopo groups.

After that I proceed with stacking UVs or distributing them throughout many UV sets.

Scripts can be accessed through *Retopo➝Isolate to UV-set* and *Retopo➝Move back from isolation*.

### Multiple Res+
Depending on the current voxel volume density of a VoxTree object, *Res+* operation can take a while to complete. If you need to perform several steps of it, but don't want to wait for the current Res+ operation to complete, then this script is for you. Be cautious though when choosing the number of Res+ steps as each will increase the number of triangles in your voxel model ca. 4 times. This means that with higher number of steps (usually more than four), you can run out of memory pretty quickly.

The script is accessible through *Geometry➝Multiple Res+*.

### Multi-Smooth Pose/Freeze Selection
Sculpt room's *Freeze* tool is great for masking areas that you don't want to affect when sculpting and with *Pose* tool's selection you can easily indicate what parts of your sculpture 3D Coat is to be affected during posing. What both of those tools don't offer is some means of automation when it comes to smoothing the selected area of the surface. This script will do just that. You'll only need to specify the number of smoothing steps that you'd like to perform. Remember that high density sculptures require much more steps than low resolution ones.

The script is accessible through *Geometry➝Multi-smooth pose/freeze*

### Show All VoxTree Objects
It does what it says it does - it sets all VoxTree objects to a visible state.

The script is accessible through *Geometry➝Show all*.

### VoxTree Merge Down
Similar to Photoshop's merge down command, but with some differences. It will merge the next VoxTree object to a currently selected one. The new object will retain the name of the latter. **Caution!** All proxied VoxTree objects will be restored to their original, non-proxy state, before the merge operation is performed.

The script is accessible through *Geometry➝Merge down*.

### VoxTree Visibility States
If you, like me, like to keep several versions and backups of your sculptures in the VoxTree hierarchy, and then at some point get lost in what should stay hidden and what should be made visible, try this script. It allows to store visibility states of all VoxTree objects temporarily (over a current 3D Coat session) or save them to file in order to restore them after you get some well deserved sleep.

The script is accessible through *View➝Load/Save VoxTree visibility states*
