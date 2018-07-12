
Future Performance Todo:

    - Garbage Collection:
    
        Garbage collection is currently the most basic mark & sweep algorithm. There's a couple things
        that could be done to improve this:
        
            - Switch to a Python-type Reference Cycle detector.
            
                This algorithm looked a bit complicated to implement. Definitely need many unit tests
                to ensure it was implemented correctly.
                
            - Implement Mark & Sweep & Compact (copy).
            
                This would require playing around with where the Memory is located. As you walk the tree,
                you can compact the memory space.
                
            - Generational GC
            
                Objects which have survived 1 or more Collection phases are checked separately, and less
                often
                
    - Rendering:
    
        Currently Sova walks the whole tree of Viewports -> Camera -> target containers -> their children.
        It loads up 1 Mesh and 1 Texture for each sprite.
        
        - Load 4 Meshes & Textures at a time
        
            The Oryol DrawState object can load 4 at a time, and then draw them all at once
            
        - Load all of the same Textures at a time?
        
        - Sprites should be able to specify a depth, draw them all in order
        
    - Game Cycle
    
        - Don't update game cycle every frame, have a fixed FPS.
        
        - Containers can specify how often their update function is called.
            
                