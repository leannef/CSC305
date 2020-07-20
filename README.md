# CSC305-Introduction-to-Computer-Graphics

## Assignment1: 
### A ray tracer assignment using C++. 
For details please see ass1/CSC305Assignment1.pdf 
#### Standard Features:
    * Output an image
    * Make your own vec3 class
    * Render a background
    * Render a sphere
    * Render a plane (eg. floor under the sphere)
    * Render multiple spheres
    * Implement anti-aliasing
    * Diffuse material
    * Positional camera
 #### Advanced Features:
    * Metal material
    * Dielectric material
    * Defocus blur
    * Rectangles and Rectangular Lights
    * Instances
  
## Assignment2: 
  The task is to render a scene using GPU rendering techniques.The supplied code uses OpenGL.
### Standard Features: 
    * In the vertex shader, transform vertices to clip space using the ModelViewProjection matrix.
    * See the scene.vert shader. (After doing this, you should see the silhouettes of the objects.)
    * In the pixel shader. implement Phong shading for a point light placed at the camera’s position.
    * Use the object’s diffuse map texture for the diffuse color.
    * The diffuse map is already hooked up the scene.frag shader.
    * Implement a hierarchy of transformations (a “scene graph”) to place objects relative to others.
    * Extend “struct Transform” in scene.h to have a “ParentID”
    * From then, each Transform is considered relative to its parent: Transforms[ParentID].
    * ParentID == -1 represents a root node.
    * At each frame, compute the absolute transform of each transform (traverse its parents.)
    * Use the absolute transform instead of the relative transform in your rendering.
    * Show that this works by rendering an object that orbits around another.
    * Implement a directional shadow map (from the sun.)
    * Create a separate FBO and depth texture to render a shadow map.
    * Make sure the depth comparison mode is set on the texture. (see glTexParameter docs)
    * Render the scene into the shadow map in a depth-only pass.
    * Bind the shadow map as a texture to your scene fragment shader.
    * Sample the shadow map with sampler2DShadow using the output of the light matrix.
    * Incorporate the shadowing into your lighting computation
    * There are good shadow map tutorials on the web. Check them out.
 ### Advanced Features:
    * Render the Sponza scene (see http://www.crytek.com/cryengine/cryengine3/downloads)
    * Implement its diffuse maps, specular maps, bump maps, and alpha masks.
    * Implement a skybox.
    * Create a cubemap texture where the 6 faces correspond to the skybox faces.
    * You can grab a cubemap from the web.
    * Add a skybox rendering pass after rendering the scene.
    * Make sure to use depth testing to avoid rendering the skybox where it isn’t necessary.

## Assignment3: 
Improve the ray tracer from assignment 1 by doing bonus features such as 
  * Motion Blur
  * Applying a red color texture mapping
  * Solid texture
  * Perlin Noise
  * Volumes
