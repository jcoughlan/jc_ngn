----------------------------------------
Modelviewer for Doom3 Engine MD5MESH models (animated by a MD5ANIM), 
ASE, LWO and OBJ models
by tom-@gmx.de (if you want to contact me, read the last section of this
readme)

Version 0.93

readme.txt, 2006-01-09



"License" & legal stuff:
========================
You may freely copy this program as long as this readme file is included.

This program is free so you may NOT charge anybody for it.  If you sell this
program for money, I´m gonna tell your mom. If you paid money for this program,
please contact me and tell me who ripped you off (and somebody will get a
spanking from his mom).

Before distributing this program (on CD/DVD/whatever means of distribution, 
including "the internet"), contact me.

This program was tested quite a few times , and it´s not doing any dangerous 
stuff, but I am not responsible for any damage that may result from the use 
of this program.



System Requirements:
====================
This will run on any Win32 system with OpenGL support. But it won´t look good
if you don´t have a graphics board that supports at least 2 texture units and
GL_ARB/EXT_TEXTURE_ENV_DOT3 extension. Read the debuglog.txt file that the
program generates, there you will find the OpenGL extensions supported by your
system, and the number of texture units.



What's in the package?:
=======================
This package should include:
the program exe itself
readme.txt (the file containing this text)
scene.txt (list of models and lightsources to display)

in the data folder are some files so you´ve got something to look at:
data/floor32b.obj
data/terrain.mtl
data/terrain_d.tga
data/terrain_local.tga



The scene.txt file:
===================
The program reads the "scene.txt" file. This file specifies the lightsources
and the MD5MESHES/MD5ANIMS and ASE/LWO/OBJ models that the program should display,
and where to display them. Check out the scene.txt file and you´ll see how it
works, it´s pretty clear I hope.
You can specify a path that leads to the Doom3 "base" folder, and the program 
will try to use that path to locate files, if it cannot find the file in the 
usual way.



How to use:
===========
For a list of keys used for interaction, press F1 while the program is running.

If a GUI element has the keyboard input focus, some of the keys are intercepted
and you can't use them to control the camera, etc. Click on the render section 
of the window to give it the input focus.

The little floating dots are the lightsources. They have the same color as the
diffuse lighting color of their corresponding light (which is white by default).

For stereoscopic view, you don´t need to use some flickering shutter-glasses,
but you have to be able to control your two eyes independently of each other,
much like a chamaeleon. ;D
No, seriously, it´s not that hard, but if you´ve never done it, you may want to
exercise on small angles first (make the window smaller and it gets easier).
By the way, in parallel mode the left half of the window is the left eye´s view,
the right one is the right eye´s. So you have to RELAX your eyes and focus some
point BEYOND the display. In crosseyed mode you have to look at the left half
with your right eye and vice versa.



Geometry & UV-Mapping Analyzer Mode:
====================================
There is a display mode in the viewer ('Q' cycles through the modes) where you
can analyze the geometry and UV-Mapping (texture-coordinates) of the model. The
triangles are displayed either in red or green color, depending on the winding
of their corresponding triangles on the UV-Map. That usually indicates areas on
the model that have mirrored UV´s, and the border is the "symmetry seam"
(usually, but not necessarily).

The second information that you get from this mode is the vertices that are
marked with white dots. They show you vertices that have multiple
UV-coordinates, which results in seams on the UV-Map. It´s an art to do
UV-Mapping with as little seams as possible. The issue with these seams is
that with tangent-space-bumpmapping, the seams CAN result in visible "edges",
breaking the smooth appearance of neighbouring triangles.
If your model shows these seams or areas of different UV winding (red/green) in
places where you didn´t expect them, then you might want to check your model´s
UV-mapping.

The edges of the model that are marked with yellow lines are the lines where
the model is "open", resulting in "non-manifold" geometry. It´s no big deal
that models have these holes, but maybe your model has holes where you didn´t
expect it, so you might want to take a closer look.

The orange-colored dots are double vertices. These vertices are also output in
the logfile, with exact mesh- and vertexnumbers. Double vertices are not just
vertices that have the same coordinates in the initial pose of the character,
but they have to have the same number of weights, and these weights must have
the same bone, weightfactor and bonespace-coordinates. Double vertices can
usually be discarded.



Known issues:
=============
- Specular highlight is distorted on badly tesselated meshes, this would
  require a fragment program to look visually correct (read John Carmac´s .plan
  file from 2003-01-29 for a detailed explanation)
- Specular highlight is not really pointy on cards with only 2 texture units
  that don´t have NVidia Register Combiners.
- ASE support: only triangulated meshes are processed correctly, animation data
  in the ASE is ignored, as well as any other additional data that can be
  stored in an ASE file
- LWO support: faces with more than 3 vertices are cut, only the first layer of
  the file content is read (Doom3's LWO files follow these restrictions anyway)
- OBJ support: only triangulated meshes are processed correctly, only one mtl
  file per object is recognized (that mtl file can contain multiple materials)
- Doom3 md5mesh specific issues:
  - "skins" are ignored (the place where Doom3 stores the information of the
    appearance configuration, for example different helmets for instances of
    the security character)
  - materials from mtr-files are ignored (the place where Doom3 stores
    information about how to render stuff, and where the textures are mapped to
    monsters. The viewer simply tries to read *, *_d and *_df files as diffuse
    textures, *_h, *_b, *_bmp and *_add files as heightmaps, *_local as
    localmaps, and *_s and *_sp as specular maps (I hope I didn´t forget any).



Thanks and Acknowledgements:
============================
The folks at www.doom3world.org for being a nice community with knowledgeable
people.

id software for this great game



Contact Me:
===========
For any comments, please contact me.

I´m very interested in your bugreports, but read the "Known Issues" and "System
Requirements" sections above before you decide that you´ve found a bug. :)
For bugreports, please send me the debuglog.txt file that is generated by the
program.

tom-@gmx.de
der_ton on the doom3world forum: www.doom3world.org
