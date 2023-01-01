# My Learning OpenGL Journey 
Hello, this is where I'm learning OpenGl.  Since I will be always changing the code around to learn new concepts, I want to keep in memory all the graphics that I produced.  Below is my journey of every graphic I created, sorted from earliest to latest. 
 <table><tr><tr>
            <td valign="bottom">
            <img src="./Memories/FragmentInterpolation.png" width="200"><br>
            FragmentInterpolation.png | Dec 24 2022
            </td>
            <td valign="bottom">
            <img src="./Memories/UpsideDownVertexShader.png" width="200"><br>
            UpsideDownVertexShader.png | Dec 25 2022
            </td>
            <td valign="bottom">
            <img src="./Memories/OffsetTriangle.png" width="200"><br>
            OffsetTriangle.png | Dec 25 2022
            </td>
            <td valign="bottom">
            <img src="./Memories/VertexPositionAsColor.png" width="200"><br>
            VertexPositionAsColor.png | Dec 25 2022
            </td></tr><tr>
            <td valign="bottom">
            <img src="./Memories/BocchiTexture.png" width="200"><br>
            BocchiTexture.png | Dec 26 2022
            </td>
            <td valign="bottom">
            <img src="./Memories/MixedTextures.png" width="200"><br>
            MixedTextures.png | Dec 27 2022
            </td>
            <td valign="bottom">
            <img src="./Memories/ImGuiDemo.png" width="200"><br>
            ImGuiDemo.png | Dec 27 2022
            </td>
            <td valign="bottom">
            <img src="./Memories/BlendedTexturesImGui.gif" width="200"><br>
            BlendedTexturesImGui.gif | Dec 27 2022
            </td></tr><tr>
            <td valign="bottom">
            <img src="./Memories/RotatedScaled.png" width="200"><br>
            RotatedScaled.png | Dec 28 2022
            </td>
            <td valign="bottom">
            <img src="./Memories/BocchiSpin.gif" width="200"><br>
            BocchiSpin.gif | Dec 28 2022
            </td>
            <td valign="bottom">
            <img src="./Memories/CameraCoords.png" width="200"><br>
            CameraCoords.png | Dec 29 2022
            </td>
            <td valign="bottom">
            <img src="./Memories/BocchiCube.gif" width="200"><br>
            BocchiCube.gif | Dec 30 2022
            </td></tr><tr>
            <td valign="bottom">
            <img src="./Memories/BocchiCubes.gif" width="200"><br>
            BocchiCubes.gif | Dec 30 2022
            </td>
            <td valign="bottom">
            <img src="./Memories/BocchiCam.gif" width="200"><br>
            BocchiCam.gif | Dec 31 2022
            </td></tr></table>

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
* Pics: BoochiCam