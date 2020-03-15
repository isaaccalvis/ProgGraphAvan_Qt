Project1 - Qt
Made by: Isaac Calvís

# List of features provided by this application:
## In-Scene options
- Create 2D Game Objects
- Delete Game Objects
- Modify Game Objects
	- Name
	- Translation (X,Y,Z) --> Translation Z is the priority order to print !!
	- Rotation
	- Scale (X,Y)
	- Shape
	- Stroke Thickness
	- Stroke Style
	- Stroke Color
	- Fill Color

## Save/Load Scenes
- Save scenes
	You have a disk icon at the toolbar, if you click you will save the scene with the name you'll insert on the Message Box, it will generate
	a Json file with your scene
- Load scenes
	You have a folder icon at the toolbar, if you click you will load a scene with the name you'll insert on the Message Box.

## Undo/Redo
The bucket size of Undo/Redo options is 5, so you can only go back or front through the last 5 modifications (bucket can be increased just changin
the bucket size number inside the engine), I selected 5 to easily make tests.
- Undo
	You have a Undo icon at the toolbar, to go back in your modifications.
- Redo
	You have a Redo icon at the toolbar, to go front in the modifications you did Undo

## Docking
From the View topbar section, you can active/deactive all inside docks, also you can move them or take out of the central window.

# List of Qt features used in this application:
## Main Window
- Set Style to Fusion
- Set Style Sheet to background color light Gray
- At Quit App: MessageBox to ask if you really want to Quit
- Create and add to respective docks Hierarchy, Inspector, Scene
- Connect toolbar and topbar actions to their functions
	- MainWindow	->	Scene		(Load/Save Scene)
	- MainWindow	->	Scene		(Undo/Redo --> Managed from UndoRedoSystem class, inside Scene)
- Different connections between widgets
	- Hierarchy	->	Scene		(Create/Delete/Change Game Objects)
	- Scene		->	Inspector	(Modified Game Object)
	- Inspector	->	Scene		(Update Game Objects)
	- Inspector	->	Hierarchy	(Game Object changed name)
	- Scene		->	Hierarchy	(Generate empty object, GameObject changed name)
	- Inspector	->	Scene		(GameObjectModified -- UndoRedoSystem)
## Game Objects
- Use own Transform & Sprite class (not from Qt)
## Hierarchy
- Slots for each UI Widget
## Inspector
- Slots for each UI Widget
## Scene Widget
- PaintEvent function
- Connections with UndoRedoSystem (not from Qt)
- At Load/Save Scene: MessageBox with input label to ask for name, in case of non name or not file found (at Load) another MessageBox advertising that.
## Resources files
- Use some icons from basic database icons (Close,Load,Save,Undo,Redo)
## Actions or Qt class
- I've used Qt class as QString, QColor ...