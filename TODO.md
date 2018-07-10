Garbage collection

Gotta have that memory management... even though it'll be inefficient at first, we just have to have it for sanity.

Ref<Refable> for everything.
Reference Counting should take care of most of it, but we'll need a mark&sweeper for the cyclical references.

Refable means you can make a Ref<> for it
    AND
 it means it can have Ref children through which we'll mark and sweep.
 
You can only run Garbage Collection from within a Refable, and it considers THAT Refable as the only root.
So, for now, let's call garbage collection every minute or so, from the Controller in the test app.