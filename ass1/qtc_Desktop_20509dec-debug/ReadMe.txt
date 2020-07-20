CSC305 ASSIGNMENT1 RAY TRACING
Leanne Feng     V00825004


* More Explanations and screenshots will be at CSC305Assignment1.pdf 

	1. hitable *world = cornell_box();
	It contains a light emitting material, axis-aligned rectangles, translate and rotate effects.
	
	2. hitable *world = cornell_smoke()
	density of volume effect is added
	
To run code in QtCreator: change code in Line 225 in main(): hitable *world  = to :
	3.  hitable *world = two_sphere();
	--in color constructor in main.cpp take out the commented out part and comment the line 40 ,
	43 and 51, which looks like: 
	
	vec3 color(const ray& r, hitable *world, int depth){
    hit_record rec;
    if(world->hit(r, 0.001, MAXFLOAT, rec)){
        ray scattered;
        vec3 attenuation;
        vec3 emitted =rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
        if(depth < 50 && rec.mat_ptr->scatter(r,rec, attenuation, scattered)) {
            return attenuation*color(scattered, world,depth+1);
            //return emitted + attenuation*color(scattered, world, depth+1);
        }else{
            return vec3(0,0,0);
            //return emitted;
        }
    }else{
///*
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5* (unit_direction.y() + 1.0);
        return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
   //   */
        //return vec3(0,0,0);
    }
}

	Change the camera angle: the top angle one is the one needed.
	
hitable *world = two_sphere();
//*
    vec3 lookfrom(13,2,3);
    vec3 lookat(0,0,0);
    float dist_to_focus = 10.0;
    float aperture =0.0;
    camera cam(lookfrom, lookat, vec3(0,1,0), 20 , float(nx)/float(ny), aperture, dist_to_focus,0.0,1.0);
//*/
/*
    vec3 lookfrom(278, 278, -800);
    vec3 lookat(278, 278, 0);
    float dist_to_focus = 10.0;
    float aperture =0.0;
    float vfov = 40.0;

    camera cam(lookfrom, lookat, vec3(0,1,0), vfov , float(nx)/float(ny), aperture, dist_to_focus,0.0,1.0);
*/
    for(int j = ny-1; j >= 0; j--){ 
    
    
	
 
Then, a green and white 2 half spheres picture will show after execute. 
For, next 2 pictures, only need to change hitable *world = constructor() part .

	4.  change to hitable *world = two_perlin_spheres() /
					hitable *world = simple_light()
		
		a perlin noise effect picture will showed up. the basic idea is to make color proportional to something
		like a sine function. and use tubulence to adjust the phase(so it shifts x in sin(x) which makes the striples undulate.

------------------------------NO.5 is the best picture --------------------------------
*	5. change to hitable *world = random_scenes() : 
	
	Then, lots of random sphere picture will show. (The first Screenshot in CSC305Assignment1.PDF