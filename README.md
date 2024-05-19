# s3d-flight-simulator
Airplane flight simulation in OpenGL. \
This project loads 3D object models saved in the _.gltf_ format (complete with _.bin_ & _textures_). \
Libraries used to implement this project: **GLEW**, **GLFW**, **GLM**, **irrKlang**, **json**, and **stb**.

### **_FEATURES_**
- _camera movement_: using keyboard input, the camera can move _forward_ (W), _back_ (S), _left_ (A), _right_ (D), _up_ (Space), and _down_ (Ctrl). These movements can be sped up by pressing the key **Shift**.
- _airplane movement_: using the aforementioned keys, the plane moves when attached to the camera (to attach or detach, press _Z_). By pressing the key **W** it will accelerate more and more. It's not necessary to keep the W key pressed, the plane will continue flying, and it can be slowed down by pressing **S**.
- _collision detection_: when the plane is attached to the camera and it collides with an object in the scene (terrain, buildings), its movements are locked. Then, an animation & sounds play, and after a few seconds the plane disappears and can repositioned on the airstrip by pressing _Z_.
- _skybox_, in which our scene is placed
- _alternation between day and night_: by pressing the key P, the light will dim. By pressing the key L, the scene will brighten. After a certain threshold is reached while pressing the P key, the skybox will change to a night scenery.
