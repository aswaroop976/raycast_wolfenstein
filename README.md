
# Table of Contents

1.  [Ray cast implementation similar to the game Wolfenstein 3D](#orgc2ac5ed)
2.  [Running the code](#orgbabf328)
    1.  [Untextured](#org00f4011)
    2.  [Textured](#org19f971e)
3.  [How it works](#org4cdf642)



<a id="orgc2ac5ed"></a>

# Ray cast implementation similar to the game Wolfenstein 3D


<a id="orgbabf328"></a>

# Running the code


<a id="org00f4011"></a>

## Untextured

-   navigate to the untextured directory and run &ldquo;make&rdquo;
-   next run &ldquo;./raycast&rdquo;. To navigate map use arrow keys
-   use &ldquo;ctrl +&rdquo; or &ldquo;ctrl -&rdquo; to change FOV(zoom in and out)
-   you can also try fisheye mode by running &ldquo;./raycast fisheye&rdquo;


<a id="org19f971e"></a>

## Textured

-   still a work in progress


<a id="org4cdf642"></a>

# How it works

-   Inspired by: <https://lodev.org/cgtutor/raycasting.html> (most of the math was from the article here)
-   My implementation is done entirely in C from scratch using only the SDL library
-   The basic idea here is that the map is a 2D square grid, with each square being either 0 (no wall), or a value greater than 0 (a wall with a certain color)
-   The player effectively shoots out a bunch of rays in his FOV(field of vision), tracking how far each ray goes until it hits a wall. Then using that distance, we render a a vertical line, the size of which depends on the distance the ray traveled. Specifically the size of the vertical line is proportional to the inverse of the distance traveled(ie the closer the wall the larger the line drawn). After drawing all the lines we can render a view of the walls.

