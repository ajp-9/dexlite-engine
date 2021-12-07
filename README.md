# Dexlite-Engine
This engine is a little hobby of mine. It is designed to run fast, but not necessarily have ultra fancy graphics--since getting really good graphics coupled with really good performance could take ages.

## How to Build:
#### Windows:

Using Visual Studio 2019 & Premake, it should be very easy to run the batch file (.bat) in the scripts folder to run the premake5 builder.  
After that you should be able to open the solution and compile without issue.  

#### MacOS:
Not fully supported yet.

#### Linux:
Not supported yet.

## Documentation:
The link to the wiki is here: https://github.com/ajp-9/dexlite-engine/wiki  
There isn't much in it currently but after I get this engine to a stable and decent state I will begin to work on the wiki

## Future Plans:
- [x] Basic application.
- [x] Integrating a simple logging library (spdlog).
- [x] Layer system.
- [x] Basic 3D Rendering.
- [x] ImGUI integration.
- [x] Input system.
- [x] Integrating EnTT with scenes & components.
- [x] A basic material system.
- [x] Model loading.
- [ ] A simple heirarchy & transform inheritance system to the ECS.
- [ ] Updating the camera system.
- [ ] Basic lighting system.
- [ ] Scene heirarchy.
- [ ] Engine configuration interface.
- [ ] Making an editor.
- [ ] Integrating a physics engine.
- [ ] More advanced lighting, ex: shadows.
- [ ] Basic animation.
- [ ] Audio system.
- [ ] A GUI built ontop of ImGUI.
- [ ] Mac & Linux support.
- [ ] Adding Documentation.
- [ ] Possibly adding a scripting api.
- [ ] Release build ready.

## Contribution 
If you find a bug, or just something that needs to be fixed, please do make an issue or a pull request.  
For now though keep in mind that this engine is going through a LOT of work and what you see one day will probably not be the same a few days or week later. 

## External Libraries:

- GLFW (https://github.com/goxjs/glfw)
- glad (https://github.com/Dav1dde/glad)
- GLM (https://github.com/g-truc/glm)
- stb_image (https://github.com/nothings/stb)
- json (https://github.com/nlohmann/json)
- tinygltf (https://github.com/syoyo/tinygltf)
- EnTT (https://github.com/skypjack/entt)
- spdlog (https://github.com/gabime/spdlog)

## License:
This project uses the MIT license.  
If you decide to use this engine with any of your projects or games please do link back to here.
