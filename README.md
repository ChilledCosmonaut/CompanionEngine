# Environment

## Requirements

To successfully compile the game and engine following requirements must be meet:

- Clion v2022.1.3
- Conan Plugin for CLion (only available on 2022.1.3)
- Visual Studio 2019 Compiler
- Python 3.10+

## Set up

Setting up the environment of the project is quite easy. After cloning the repository let Clion open the code foolder as a project (else issues arise). Then you need to create a correct conan profile. The one I used can be found inside the docs folder (Simply copy the file to the `.conan\profiles` inside your user directory). Now if you haven't install the Conan plug in for Clion go ahead and install it. (If you want to set up conan without it, please visit the website for a [detailed explanation](https://docs.conan.io/en/latest/getting_started.html). Conan itself can be set up with only a few commands most of the time). Then simply match your profile with your build configuration via the small slider symbol inside the plug in window. After matching the profile click on install button also inside the conan window. Now pretty much everything (except the python environment, if it's not already standardly set up) is up and running. Now simply click the compile and the project should be build properly. A more detailed guide vread the following [blog post](https://blog.jetbrains.com/clion/2019/05/getting-started-with-the-conan-clion-plugin/).

### Note:
Be also sure to use the x86_amd64 compiler target in Clion, else physX does not want to compile.

---

# Create a Game

To create a new game simply create a new instance of the `Game` class with it's parameters. Then to actually start simply call the `run()` function on your instance to start executing the game.

Note: It might be wise to provide an initial scene before calling run to reduce the probability that only a simple blueish screen is shown.

## Scene

To order the contents processed simple scene structures are used they may simple be creted by inheriting from the abstract scene parent class. To change from one scene to another simply call the `ChangeActiveSceneTo(scene)` function from the game calss with the new scene.

## One to rule them all (Singleton)

All core systems are created with the singleton pattern in mind. This means that as long as the interface of a core system is directly accessible by the user, the system may also be accessed via a Get function.

---


# Entities, Components and Systems

Because the Companion Engine is data oriented, actual data and logic is saved in two seperate files. The data is stored in the so called `Components` and the logic is saved inside the `System` files. Each `System` gets the needed `Components` dynamically in either the `StartUp()`, `Upate()` or `Shutdown()` function (The purpose and behaviour of these functions is similar to other known engines like Unity or Unreal). While these two handle the game logic and state a third type is needed for the systems to identify exactly which components belong to one `entity` and should be processed together. These are the so called entities.

## The Registry

The Registry is the "allmighty" storage for all entities and components. Being the unified storage, all entities and components must be accessed via the registry.  
In general there are two ways to retrieve a Component. Either by getting a iterator overall entities that possess the requested types. Or by directly retrieving the component from a entity (Warning! This may throw an exception).  
The respective function calls are:
- `registry.view<ReqeustedComponents>(ExcludedComponents)` which returns a iterator over entities
- `registry.view<ReqeustedComponent>(entity)` which retrieves the component from a specified entity

**Note:** For a more in depth explanation read the following [documentation of the entt library](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system). 

## How to create new scripts?

So now that you know how the all the types interact with each other creating new scipts becomes varily easy. First of all, you do not need to create a new entity class by hand. This is taken care of by the engine. Simply call `CreateEntity()` on the currently active scene (Reference to the current scene can be acquired via the game class) to get a brand new entity. Note that all entities are initially created with a `Transform` component. ***This component should under no circumstance be removed!***  
Now the topic of creating `Componets` and `Systems` is not quite as easy. In general all classes and structs that are move and copy constructible may be `Components`. So contrary to the statement from earlier, regarding the data orientation, this means that `Components` may also posess logic which is not intended and recommended!  
To create a new `System` you simply need to let a class of choice publicly inherit from the abstract base `System` class. The create new subsystem class now must be passed to the game via the `SetUpSystem(game)` function.

## System Life Cycle (SetUp, Update, Shutdown)

As mention before, `Systems` have a `StartUp()`, `Upate()` and `Shutdown()` function. Contrary to what the function names suggest these functions are only semi responsible for the `System` itself but more concerned about handling the data of `Components`. Because each `System` itself handles a certain kind of logic for a specialized group of `Components`, so the functions should also handle the logic regarding this aspect.

## Flags? Like... pirate flags?

In a weird kind of way... Yes! All flags in the physical world have some kind of inherit meaning, just as the flags in the engine. To benefit from performance increases by reducing loops, flags help to determine the state of an entity without even knowing the entity yet. Let's envision the following examples. A component as a special set up behaviour that communicates to a third party API, like physics. If you now access this component in an update cycle before the initial set up, weird things might happen. Another example would be that we have 10.000 units on a battlefield but only ten of them moved in the last frame. Updating all units might impact our performance more than necessary. Flags help us to reduce these kinds of issues. As we already discussed before hand we can request an iterator over all entities with a certain set of components. Including flags which are essentially only empty components. So looking back at our examples we can determine if certain entites are still waiting to be set up or need to be updated without actually accessing these in any direct way.  
The engine already provides some logic for setting flags. If you add a Component via the `AddComponent<Component>(entity)` function, an update flag for the component will be set.  
In detail there are the following flags already provided:
- `Setup<Component>`
- `Update<Component>` 
- `Destroy<Component>` 
- `DestroyEntity`  

For more detail please visit the specific doc page.

---

# Important core systems

## Transform/Scene Graph
A quite simple core system, yet one of the most important. The related component is the `Transform`. A `Transform` saves all data regarding the entities position in 3D space. Because the 3D maths can be tricky a `TransformationUtil` class is provided.

## Graphics System
The graphics system as of now has three parts: `Text`, `UI` and `Models`. For a more detailed explanation visit the respective doc files.

## Physics System
The physics system currently supports only rigid statics, like planes, and rigid body primitives, like boxes, spheres etc.  
The physics system is completely based upon the Nvidia PhysX engine which is also available to the user. Therefore it might be helpful to visit [their respective documentation](https://gameworksdocs.nvidia.com/PhysX/4.1/documentation/physxguide/Index.html).

## Audio System 
Based on the soLoud sound library, the engine supports both background audio as well as 3D positional audio.

## Input System
The input system provides a **very** small but nice abstraction for handling input. And input group may be declared by inheriting the input group class. To add it to the input polling list simply pass the input group into `AddInputGroup(inputGroup)`from the input manager which is accesible via singleton. This small abstraction minimizes the impact of input polling.

## File System
The file system manages all asset data and acceses it appropriately. By utilizing LRU caches and some code generation, the file manager minimizes runtime load and error. All assests are handled via this system and identified via an unique struct generate from the asset names. This provides a compile time safety for assets.





