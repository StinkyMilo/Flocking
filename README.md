(Video link)[https://youtu.be/flyhFdcvduE]

I unfortunately didn't have time to make this as pretty as I might've liked, but the three basic rules and the tweak are implemented!
I think the single thing that fixed most of my problems was multiplying velocity by DeltaTime in the agent tick function, which slowed down the boids
to a point where I could understand what was going on much better. 
The tweak I implemented was limiting the velocity, which is done within the Agent tick function. The velocity limit can be set in the editor.

If by chance you run into the same issue I did where there is no model associated with the boids, it means I didn't compile correctly upon quitting. 
You can fix it by opening the blueprint gamemode class, compiling within Unreal, then setting the two blueprint variables: the mesh and the speed limit.
(I am fairly confident that won't happen, but here are the instructions to fix it just in case.)