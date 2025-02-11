one_transducer_distance does that it says on the tin. Distance sensor for one transducer. 

two_transducer_triangulation takes two distances from sensors at a known separation facing in the same direction and outputs a Y value (perpendicular distance from centre line connecting the two sensors) and X value (horizonal separation from centre of line connecting the two sensors). May update at some point to work for sensors angled in toward each other, as this actually increases the area in which their sensing fields overlap within a given range. Might work anyway as it's just taking two distances. 

half_angle_splay_three_transducers assumes three transducers slightly splayed outward, creating 5 distinct regions (see the diagram). it classifies which region an object is in and reports the distance to it. Doesn't make any assumptions about the splay angle.
