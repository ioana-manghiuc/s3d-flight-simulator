# s3d-flight-simulator
Airplane flight simulation in OpenGL. \
This project loads 3D object models saved in the _.gltf_ format (complete with _.bin_ & _textures_). \
Libraries used to implement this project: **GLEW**, **GLFW**, **GLM**, **irrKlang**, **json**, and **stb**.

### **_FEATURES_**
- _camera movement_: using keyboard input, the camera can move _forward_ (W), _back_ (S), _left_ (A), _right_ (D), _up_ (Space), and _down_ (Ctrl). These movements can be sped up by pressing the key **Shift**.
- _airplane movement_: using the aforementioned keys (except S), the plane moves when attached to the camera (to attach or detach, press _Z_)
- _collision detection_: when the plane is attached to the camera and it collides with an object in the scene (terrain, buildings), its movements are locked. Then, an animation & sound play, and after five seconds the plane is repositioned on the airstrip, from where it can be flown again.
- _skybox_, in which our scene is placed
- _alternation between day and night_: by pressing the key P, the light will dim. By pressing the key L, the scene will brighten. After a certain threshold is reached while pressing the P key, the skybox will change to a night scenery.
