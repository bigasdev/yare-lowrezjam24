# Hello World!
 First concerns found in the roguelike project.

## Concerns
Right now its somewhat hard to manage the entities, its easy enough to spawn and create them so that is great, but they are hard to manage and keep track.
What we need to do:

- First, it should have a difference from *Projectiles*, *Items*, *Mobs*, *Destructables*, *Doors*, *Hero*. Since all my games will somehow use these concepts
- Second, there should be a manager that can be easily attached to the scene where would take care of the groups for draw and update methods, like a _Jail_ 
- Third, we need to fix some attributes and add some more to all of the entities:

 - [x] Affect manager, so we can manage states and effects for the entity
 - [] Rank, this will be used to determine the rarity and/or the power of the entity 
 ~[] Better tag/group system to determine if something is good or evil.states~
 - [x] is_colliding(Entity en) a function to detect if its colliding with some entity (this might need extra work so be careful)

 - Some specific ones:
    - [x] move_to(Entity en) for the mobs 

## Todo

- [ ] Create the destructable entity that will drop the potions 
- [ ] Create the float item function 
- [ ] Create the state function for the animations
### Polish Todo
- [ ] Test the black screen filter with light on aseprite 
- [ ] Test a global shadow function (?)
- [ ] Create the camera zoom variables with the set zoom 
- [ ] Create the position shift using the camera zoom 
