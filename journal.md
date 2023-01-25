
# Journal

## Dec 23
Created a function to parse shader text files into a shader source:
* Used ifstream object and getline to read file line by line.
* Used an enum class to map shader type to an integer.
* Added relevant lines using stringstream object.
* Reduced nested code from 2 to 1 using extraction and inversion.
* Pics: FragmentInterpolation

## Dec 24
Played around with Shaders
* Green triangles faded in and out using uniforms to draw colors based on sin of time.
* Rainbow triangle made through fragment interpolation, supplying only 3 colors to vertex.
* Pics: FragmentInterpolation

## Dec 25
* Built class for managing Shaders more efficiently
* Played around with shaders to get the pics
* Pics: Offset, UpsideDown, VertexPosition

## Dec 26
* Built class for managing/loading in Textures
* Loaded in Texture through fragment shader and stb_image for loading.
* Pics: BocchiTexture

## Dec 27
* Accounted for texture units in order to have multiple textures
* Incorporated imgui to blend textures with slider
* Pics: MixedTextures, imguiDemo, blendedTexturesImGui

## Dec 28
* Added GLM library for math
* Transform image using rotation and scaling.
* Pics: RotatedScaled, BocchiSpin

## Dec 29
* Learned the cameria coordinate pipeline
  * Local Space -> Model Matrix -> World Space -> View Matrix -> View Space -> Projection Matrix -> Clip Space -> Viewport Transformation -> Screen Space
* Pics: CameraCoord
  
## Dec 30
* Converted 2d plane to 3d cube.
* Played around with altering fov and transformation matrices.
* Pics: BocchiCube, BocchiCubes

## Dec 31
* Implemented working camera with translation and rotation
* Pics: BoochiCam, ElGatoZoom

## Jan 2
* Added Vertex Array Class to handle vertex buffers
* Finished draw function in Renderer Class

## Jan 9
* Finally was able to render a voxel sphere.  It took me a long time to find out the bug, which was my render class was only rendering 36 vertices, or just 1 cube.  Increasing this parameter rendered the sphere.  Another problem came up- the sphere is not a full sphere.  Some cubes are missing, and im unsure why.  UGHHHHHH
* Pics: voxelSphereCube

## Jan 10
* Modified vertex format to be a property of VAO
* Added new light source shader and light source VAO.
* Made bindVBO const to avoid the 2 hour bug i had.
* Pics: lightSource

## Jan 11
* Added ambient and diffuse lighting
* Added libnoise library
* First terrain generation using perlin noise!
* Pics: DiffuseLighting, LandscapeChunk

## Jan 12
* Read about SOLID design principles
* SRP - Single Responsibility Principle
  * "A class should only have one reason to change"
* OCP – Open/Closed Principle
  * "classes should be open for extension, closed for modification"
* LSP – Liskov Substitution Principle
  * "Subtypes must be substitutable for their base types without altering the correctness of the program"
* ISP – Interface Segregation Principle
  * "Clients should not be forced to depend on interfaces that they do not use."
* DIP – Dependency Inversion Principle
  * "Abstractions should not depend on details. Details should depend on abstractions."
* Source: http://www.vishalchovatiya.com/single-responsibility-principle-in-cpp-solid-as-a-rock/
* Optimized chunk by not renderering hidden blocks.  This reduced average blocks/chunk from 1000 to 250 for 16x16x16blocks, about 400% more optimized.
* Pics: RandomizedChunk

## Jan 14
* Fixed chunk not loading correctly (hiddenblocks func) (scaling first then translating)
* Added sand
* LETS GOO I FIXED THE TERRAIN GEN.  I had to 
  1. change setDstImage to 32 by 32 so each heightmap only has 32 possible values instead of 256*256.
  2. change getValue() parameters to only range [0,31] because anything over is out of bounds.
  3. Render z axis starting from top since the way my cube is oritented with (0,0,0) being the left, bottom, away from screen corner.
* Pics: Sand, FirstWorld

## Jan 15
* Wrote quick blog post on how to generate voxel terrain using Perlin noise
  * https://vincenguyen.super.site/blog/blog-posts-1/how-to-generate-voxel-terrain-using-perlin-noise
* Going to learn fluid dynamics to add water.

## Jan 16
* Looked into Cellular Automata, Game of Life, fluid simulation
* pics: SimpleWater
  
## Jan 17
* Added water renderer and water shader class.
* Encountered a bug where VBO id was not founded.  I realized I failed to set the corresponding VAO correctly.

## Jan 18
* Finished testing out frame buffer object
  * Realized that I needed to reset the buffers within frame buffer object.
* Struggled with getting the refraction texture to work.  Turns out, both reflection and refraction fbos were equal to 1 because my function, createFrameBuffer() did not have a return...
* Learned how to use clipping planes in vertex shaders.  Specify a clipping plane with (normal.x, normal.y, normal.z, dist from origin)
* Pics: FrameBuffer, ReflectRefract

## Jan 19
* Combined both textures onto the water.  IT LOOKS SO BADD
* Used projective mapping (converted texture coords from clipspace to normalized device coords so the textures line up)
  * Sources: https://antongerdelan.net/opengl/raycasting.html#:~:text=Overview,is%20usually%20called%20ray%20casting.  The 3d transformation pipeline graphic helped me alot.
* Applied water dudv mapping + distortions/offsets to get animated water.
* Added Fresnel Effect where:
  * Looking from above water surface gives more refraction.
  * Looking eye level to water surface gives more reflection.
* Used normal mapping texture to distort the water surface normals, then applied specular lighting.
* Pics: UglyWater, AverageWater, PrettyWater, FresnelEffect, SpecularLighting

## Jan 20
* Struggled so long on getting depth texture to work... ended up giving up since smooth edges is not really needed for a voxel terrain.
* Localized watertile to each chunk for easier world generation.  The lag is a little stronger tho, might need to work on loading/unloading chunks based on view position and render distance.
* Going to start writing a blog post about the intuition behind rendering scenic water now!
* Pics: Peace

## Jan 21
* Looking into contributing to open source game engines.  Looks very intimidating D:

## Jan 22
* First pull request got merged on Godot game engine!!
  * Just the docs change tho but still proud!

## Jan 23
* Finished my blog post on rendering water, read here:
  * https://vincenguyen.super.site/blog/blog-posts-1/how-to-render-pretty-water

## Jan 24
* Trying to figure out how to make my game loop or main.cpp smaller.
  * Looked into the command design pattern and took notes:
    * https://rapid-anchovy-e57.notion.site/Command-Design-Pattern-308aaca223804d199c03bbc4dd778f6c
    * Maybe I can use command design for camera movement?  I think its fine hardwired because i cant think of when I would need to change from wasd.  Maybe I can use command on renderering commands?  One for water and another for chunk?  I dont think I'll need an undo right now.  I'll look into Flyweight tommorrow.

## Jan 25
* Read about flyweight.  I realized i've kinda been using it for my block representation.  Also, I think flyweight design pattern will be really useful when i need to render a ton of instances like trees and grass.  I took notes on this here:
  * https://rapid-anchovy-e57.notion.site/Flyweight-Design-Pattern-d716f766382748b19e96677ac268dc2b
* I want to add multiplayer support so I looked into networking.  I found this really good source and read up until chapter 5 when we actually start coding with sockets.  I've heard lots of difficult things about networking, so I hope this will go well.  Tommorrow, I'll look at observer design pattern and probably have some actual code for sockets.  Persona 5 royal just arrived today.
  * https://beej.us/guide/bgnet/html/#system-calls-or-bust
