# Game2D

- Windows 7+

===========================

https://ncase.me/sight-and-light/
https://www.redblobgames.com/articles/visibility/

## TODO refactoring

- rename: p_ for pinters g_ for globals (gp_ for global pointer)

https://www.parallelrealities.co.uk/tutorials/shooter/shooter1.php
- linked lists for rendering... have global head pointer for each
- pass Sprite pointer to render functions
- blit?
- struct Bullet { enum Side side_player; }
- with linked lists just iterate and free each... 
- dx, dy ... for movement
- MAYBE have type renderable where magic is done to render with RECT and TEXTURE structs
- library https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake


https://stackoverflow.com/questions/63438157/convert-polygon-to-inverted-polygon-i-e-carve-out-the-negative-polygon-from-vi
		
## TODO
- create helper function to create polygons -> go on to allow user to create their own
- draw text
- hide cursor
- debug/logging function
- enemies smooth disappearing
- phyisics collisions
- add/remove objects dynamically
- sounds? https://www.parallelrealities.co.uk/tutorials/shooter/shooter10.php
- improve sprite drawing performance?