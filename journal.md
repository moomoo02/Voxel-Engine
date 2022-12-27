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
* Pics: MixedTextures, imguiDemo
