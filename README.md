# Untethered Game Engine
Game engine under the development of Zach Ross. It uses [SFML](http://www.sfml-dev.org) as a graphics and sound engine.
## todo
### Collision Detection
- [X] Implement Seperate Axis Theorem
- [ ] Add circle capabilities for the Seperate Axis Theorem
- [X] Implement Quad Tree

### Physics
- [ ] Create intuitive way to derive class into child classes
- [ ] Implement Laws of Inertia into movement and Collision
- [ ] Implement Gravity options

### GUI
- [X] Add XML Parsing to the engine
- [X] Create node system for GUI Elements
- [X] In-depth text and NodeElement formatting via XML tags
- [X] Add Button Elements
- [ ] Add Input Elements
- [X] Add Text Elements
- [ ] Add RadioButton Elements
 - Used for single answer question
- [ ] Add ProgressBar Elements

### Scene Queue
- [ ] Create custom scripting language for adding events to a Scene
- The end of each event should trigger the next event in the queue

### Misc/Unsorted
- [ ] Game Camera
- [ ] Mac Support
- [ ] Linux Support
- [ ] Switch all animation files to custom file format

## Credit Where It's Due
The following websites are sources I used as references during the development of this game engine. 

### Seperate Axis Theorem
- [dyn4j](http://www.dyn4j.org/2010/01/sat/)
- [envatotuts+](http://gamedevelopment.tutsplus.com/tutorials/collision-detection-using-the-separating-axis-theorem--gamedev-169)

### Quad Tree
- [envatotuts+](http://gamedevelopment.tutsplus.com/tutorials/quick-tip-use-quadtrees-to-detect-likely-collisions-in-2d-space--gamedev-374)
