HW 8 README: 

I am using both my extensions, seeing this is the last homework. I have emailed 
Dr. Badler about this and he gave me permission to use two extensions on this hw
without any penalty. 


You can click on a face and it will select that face. You can actually change 
the colors of that face once selected. 
A ray will show up when you click on the screen, but a gray box will outline the
selected face. 

If you move a vertex around, it will actually recalculate the planarity, and split
the face if the move makes it nonplanar. 


Extra Credit: 
Mouse Hovering of faces: The face that is hovered over will have a red outline

Mouse Hovering of Vertices: The vertex that is hovered over will be represented 
	as a red outline triangle in the corner of the quad/triangle with the vertex.
	This'll appear on the actual face. My algorithm only checks the hovered
	face to see if the mouse is over the "triangle" vertex portion. 

Picking Vertices: The vertex that is clicked will be represented as a gray outline 
	triangle in the corner of the quad/triangle with the vertex.
	This'll appear on the actual face. My algorithm only checks the selected
	face to see if the "triangle" vertex portion was clicked.
	This will actually pick the vertex and you can changed x,y,z and the 
	outline will change with it. 

Note on interaction between hovering and clicking: 
	The red outline shoud be on top of the gray outline if you clicked and are
	currently hovering over the same face or vertex. This isn't a bug. 
	
