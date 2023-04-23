# miniRT

`miniRT` is a simple 3D renderer that can display basic scenes with objects and lights. The project is part of the curriculum for the 42 coding school.

<div style="display: flex; justify-content: space-between;">
 <img style="width: 30%;" src="https://nextcloud.42l.fr/s/GiKXpbJPHcjRD57/download/Screen%20Shot%202023-04-23%20at%2016.19.45.png">
 <img style="width: 30%;" src="https://nextcloud.42l.fr/s/wCkDGwFeHPSTXFo/download/Screen%20Shot%202023-04-23%20at%2016.42.55.png">
 <img style="width: 30%;" src="https://nextcloud.42l.fr/s/2kN5wz4Kn73tgTm/download/Screen%20Shot%202023-04-23%20at%2016.43.26.png">
</div>
<div style="display: flex; justify-content: space-between;">
 <img style="width: 30%;" src="https://nextcloud.42l.fr/s/FSEyDipKxs9r2ES/download/Screen%20Shot%202023-04-23%20at%2016.43.49.png">
 <img style="width: 30%;" src="https://nextcloud.42l.fr/s/HnHg8JQEdHwS7Hp/download/Screen%20Shot%202023-04-23%20at%2016.44.02.png">
 <img style="width: 30%;" src="https://nextcloud.42l.fr/s/oSBytDtrKHteLHk/download/Screen%20Shot%202023-04-23%20at%2016.59.38.png">
</div>

*copyright for the deer 3D model: snippysnappets https://free3d.com/3d-model/low-poly-deer-72513.html*  

This repository contains the source code for `miniRT`, as well as a few sample scenes to get started with. The code is written in C and uses the [MinilibX](https://github.com/42Paris/minilibx-linux) library to handle graphics.

### Supported platforms

The program works on a Linux system, or macOS with the Metal engine.

### How to use

To use `miniRT`, you need to compile the source code and run the executable with a scene file as argument. Here's an example:

```sh
make
./miniRT scenes/1_sphere.rt
```
The scene file should contain a list of objects and lights, each specified by a set of parameters.  
Here is the list of possible entries:

- Window resolution: `R 680 540`. Parameters:
  - x render size
  - y render size

- Ambient lightning: `A 0.2 255,255,255`. Parameters:
  - ambient lighting ratio in range [0.0,1.0]
  - R,G,B colors

- Camera: `C -50.0,0,20 0,0,1 70`. Parameters:
  - x,y,z coordinates of the view point
  - 3d normalized orientation vector OR target point of the view by preceding the coordinates by `at` (without space), both in range [-1,1] for each x,y,z axis
  - horizontal field of view (FOV) in degrees in range [0,180]

- Light: `L -40.0,50.0,0.0 0.6 10,0,255`. Parameters:
  - x,y,z coordinates of the light point
  - the light brightness ratio in range [0.0,1.0]
  - R,G,B colors in range [0-255]

- Sphere: `sp 0.0,0.0,20.6 12.6 10,0,255`. Parameters:
  - x,y,z coordinates of the sphere center
  - the sphere diameter
  - R,G,B colors in range [0-255]

- Plane: `pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225`. Parameters:
  - x,y,z coordinates of a point in the plane
  - 3d normalized normal vector, in range [-1,1] for each x,y,z axis
  - R,G,B colors in range [0-255]

- Triangle: `tr 0,1,4 -2,-1,0 -1,2,3 255,255,0`. Parameters:
  - x,y,z coordinates of the three apices of the triangle
  - R,G,B colors in range [0-255]

- Square: `sq 0,0,1 0,0,1 2.0 255,255,255`. Parameters:
  - x,y,z coordinates of the square center
  - 3d normalized normal vector, in range [-1,1] for each x,y,z axis
  - side size
  - R,G,B colors in range [0-255]

- Cylinder: `cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255`
  - x,y,z coordinates of the center of the cylinder
  - 3d normalized vector of axis of cylinder, in range [-1,1] for each x,y,z axis
  - the cylinder diameter
  - the cylinder height
  - R,G,B colors in range [0,255]

You can add multiple cameras and switch them by using the right and left arrows of your keyboard.

### Save image in bmp format
You can save the rendered image in bmp format instead of opening it in a window, by specifying "--save" as a second argument of the execution.

### How it works

`miniRT` works by tracing rays from the camera through the scene and computing the color of the objects they hit. The renderer uses a simple raytracing algorithm that supports spheres, planes, and light sources.

The renderer first reads the scene file and initializes a camera object that defines the viewpoint and field of view. For each pixel in the image, a ray is traced from the camera through the pixel and into the scene. The ray is tested for intersection with each object in the scene, and the color of the object that is hit is computed using a basic lighting model.

The lighting model takes into account the intensity and color of each light source, as well as the material properties of the object, such as its diffuse and specular reflectance coefficients. Shadows are also computed by testing if the point of intersection with the object is in shadow from the light source.

### Program to convert an .obj file to an .rt file
I coded this small program for convenience (not required by the subject).  
You can find it in the `obj_extract_triangles` directory.  
There is a `readme` file inside.
