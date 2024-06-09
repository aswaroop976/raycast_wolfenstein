
# Table of Contents

1.  [Ray cast implementation similar to the game Wolfenstein 3D](#orgd9ca7b5)
2.  [Running the code](#orgcbb7167)
    1.  [Untextured](#org0124cf9)
    2.  [Textured](#org18ee815)
3.  [How it works](#org96369e9)



<a id="orgd9ca7b5"></a>

# Ray cast implementation similar to the game Wolfenstein 3D


<a id="orgcbb7167"></a>

# Running the code


<a id="org0124cf9"></a>

## Untextured

-   navigate to the untextured directory and run &ldquo;make&rdquo;
-   next run &ldquo;./raycast&rdquo;. To navigate map use arrow keys
-   use &ldquo;ctrl +&rdquo; or &ldquo;ctrl -&rdquo; to change FOV(zoom in and out)
-   you can also try fisheye mode by running &ldquo;./raycast fisheye&rdquo;


<a id="org18ee815"></a>

## Textured

-   still a work in progress


<a id="org96369e9"></a>

# How it works

-   Inspired by: <https://lodev.org/cgtutor/raycasting.html> (most of the math was from the article here)
-   My implementation is done entirely in C from scratch using only the SDL library


