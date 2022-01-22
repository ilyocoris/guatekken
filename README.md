# PROVISIONAL_NAME

We want to build a 2d browser fighting game featuring unique 3D printed controllers for each character. The controllers will be powered by Arduino and connected by WiFi (or BLE) to the game. By using the vast amount of sensors available, each controller will play out in different and unique ways, pushing the asymmetry that makes fighting games so deep and brilliant to a maximum. 

For example, we can play with heartbeat sensors, wrapped around the player's wrist to control a passive element on the user. Distance sensors to have a new way to handle movement on one axis. IR to connect a split-in-two controller in various ways. The possibilities are endless.

With the apparition of 3D printing, making controllers with different shapes to accomodate these new ways to input information into the game is easier than ever. 



# Concept for Character using Òpla Kit as Controller

To quickstart development, we have designed a character around the Òpla Kit. This will allow us to get the first controller out of the box, to be able to start testing and playing while we design some more advanced (and 3D printed) controllers.

We have dubbed this initial character Òpla Kid, until we flesh out more their backstory as we further develop the game. 

![alt text](concept/opla_kid.png)

They are looking flashy!! We want to go for a simple skill set, to have a "basic" character that still utilizes already a unique controller. 

In the next image we find an overview of the abilities. The basic kit allows the Òpla Kid to move, jump, kick and jab. The special ability takes advantage of the humidity sensor of the shield, as whenever the player expels their breath on the sensor, the humidity will go up, triggering a cloud in-game that will allow the character to move undetected. This ability has no cooldown, its only limitation is the breath of the user itself, creating an almost cybernetic player-character relationship through the unusual controller. 

> Exploring this connection, built on more-than-a-joystick unique controllers, is our vision for the game. 

![alt text](concept/opla_kid_controller.png)

Finally, we pretend to use the screen for an ultimate, that, when triggered for an still to design condition, will show some patterns pointing towards some of the 5 buttons. If the user manages to press the correct buttons for the patterns, that will appear in a quick succession, the ultimate will be successful, dealing critical damage.

# VideoGame Architecture

As of the making of this exposition, we have not yet decided on an architecture for the vydeogame itself. We will first test different communication protocols between the controllers and the game (BLE or WiFi). 

# The ~~Team~~ Friends to Do It

Miquel - Architect. Art & Concept.

Bernat - Head of Manufacturing at 3D printing Startup.

Domènec - Thinker and Game Designer.

Dídac - ML Engineer. Programming.

Aina - Programming & electronics.

Gustavo - Programming & electronics.

