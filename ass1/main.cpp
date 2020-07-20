#include <iostream>
#include <math.h>
#include <stdlib.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "stb_image.h"
#include "sphere.h"
#include "hitablelist.h"
#include "float.h"
#include "camera.h"
#include "texture.h"
#include "moving_sphere.h"
#include "perlin.h"
#include "material.h"
#include "aabb.h"
//#include "box.h"
#include "constant_medium.h"
#include "rotate.h"
#include "translate.h"
#include "bvh_node.h"


//using namespace std;

struct rgba8 {
    unsigned char r, g, b, a;
    rgba8() { }
    rgba8(unsigned char rr, unsigned char gg, unsigned char bb, unsigned char aa)
    : r(rr),g(gg),b(bb),a(aa) { }
};

vec3 color(const ray& r, hitable *world, int depth){
    hit_record rec;
    if(world->hit(r, 0.001, MAXFLOAT, rec)){
        ray scattered;
        vec3 attenuation;
        vec3 emitted =rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
        if(depth < 50 && rec.mat_ptr->scatter(r,rec, attenuation, scattered)) {
            //return attenuation*color(scattered, world,depth+1);
            return emitted + attenuation*color(scattered, world, depth+1);
        }else{
            //return vec3(0,0,0);
            return emitted;
        }
    }else{
/*
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5* (unit_direction.y() + 1.0);
        return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
      */
        return vec3(0,0,0);
    }
}

void get_sphere_uv(const vec3& p, float& u, float& v){
    float phi = atan2(p.z(), p.x());
    float theta = asin(p.y());
    u =1-(phi +M_PI) /(2*M_PI);
    v = (theta+ M_PI/2) / M_PI;
}


hitable *two_sphere(){
    texture *checker = new checker_texture(new constant_texture(vec3(0.2,0.3, 0.1)), new constant_texture(vec3(0.9,0.9,0.9)));
    int n =50;
    hitable **list = new hitable*[n+1];
    list[0] = new sphere(vec3( 0,-10, 0), 10, new lambertian(checker));
    list[1] = new sphere(vec3( 0, 10, 0), 10, new lambertian(checker));
    return new hitable_list(list,2);
}


hitable *cornell_smoke(){
    hitable **list = new hitable*[8];
    int i = 0;
    material *red = new lambertian(new constant_texture(vec3(0.65,0.05,0.05)));
    material *white = new lambertian(new constant_texture(vec3(0.73,0.73,0.73)));
    material *green = new lambertian(new constant_texture(vec3(0.12,0.45,0.15)));
    material *light = new diffuse_light(new constant_texture(vec3(7,7,7)));
    list[i++] = new flip_normals(new yz_rect(0,555,0,555,555,green));
    list[i++] = new yz_rect(0,555,0,555,0,red);
    list[i++] = new xz_rect(113,443,127,432,554,light);
    list[i++] = new flip_normals(new xz_rect(0,555,0,555,555,white));
    list[i++] = new xz_rect(0,555,0,555,0,white);
    list[i++] = new flip_normals(new xy_rect(0,555,0,555,555,white));
    hitable *b1 = new translate(new rotate_y(new box(vec3(0,0,0),vec3(165,165,165),white),-18),vec3(130,0,65));
    hitable *b2 = new translate(new rotate_y(new box(vec3(0,0,0),vec3(165,330,165),white),15),vec3(265,0,295));
    list[i++] = new constant_medium(b1,0.01,new constant_texture(vec3(1.0,1.0,1.0)));
    list[i++] = new constant_medium(b2,0.01,new constant_texture(vec3(0.0,0.0,0.0)));
    return new hitable_list(list,i);
}
/*
hitable *final(){
    int nb = 20;
    hitable **list = new hitable*[30];
    hitable **boxlist = new hitable*[10000];
    hitable **boxlist2 = new hitable*[10000];
    material *white = new lambertian(new constant_texture(vec3(0.73,0.73,0.73)));
    material *ground = new lambertian(new constant_texture(vec3(0.48,0.83,0.53)));
    int b =0;
    for(int i = 0; i<nb; i++){
        for(int j =0; j< nb; j++){
            float w = 100;
            float x0 = -1000 + i*w;
            float z0 = -1000 + j*w;
            float y0 = 0;
            float x1 = x0 + w;
            float y1 = 100*(drand48()+0.01);
            float z1 = z0 + w;
            boxlist[b++] = new box(vec3(x0,y0,z0), vec3(x1,y1,z1), ground);
        }
    }
    int l = 0;
    //list[l++] = new bvh_node(boxlist, b, 0, 1);
    material *light = new diffuse_light( new constant_texture(vec3(7,7,7)) );
    list[l++] = new xz_rect(123, 423, 147, 412, 554, light);
    vec3 center(400, 400, 200);
    //list[l++] = new moving_sphere(center, center+vec3(30, 0, 0), 0, 1, 50, new lambertian(new constant_texture(vec3(0.7, 0.3, 0.1))));
    list[l++] = new sphere(vec3(260, 150, 45), 50, new dielectric(1.5));
    list[l++] = new sphere(vec3(0, 150, 145), 50, new metal(vec3(0.8, 0.8, 0.9), 10.0));
    hitable *boundary = new sphere(vec3(360, 150, 145), 70, new dielectric(1.5));
    list[l++] = boundary;
    list[l++] = new constant_medium(boundary, 0.2, new constant_texture(vec3(0.2, 0.4, 0.9)));
    boundary = new sphere(vec3(0, 0, 0), 5000, new dielectric(1.5));
    list[l++] = new constant_medium(boundary, 0.0001,new constant_texture(vec3(1.0, 1.0, 1.0)));

    int nx, ny, nn;
    unsigned char *tex_data = stbi_load("earthmap.jpg", &nx, &ny, &nn, 0);
    material *emat = new lambertian(new image_texture(tex_data, nx ,ny));
    list[l++] = new sphere(vec3(400, 200, 400), 100, emat);
    texture *pertext = new noise_texture(0.1);
    list[l++] = new sphere(vec3(220,280, 300),80, new lambertian( pertext ));
    int ns = 1000;
    for (int j = 0; j <ns; j++){
        boxlist2[j] = new sphere(vec3(165*drand48(), 165*drand48(), 165*drand48()),10, white);
    }
    //list[l++] = new translate(new rotate_y(new bvh_node(boxlist2,ns, 0.0, 1.0),15),vec3(-100, 270, 395));
    return new hitable_list(list,l);
}

*/
hitable *simple_light(){
    texture *pertext = new noise_texture(4);
    hitable **list = new hitable*[4];
    list[0] = new sphere(vec3( 0,-1000,0), 1000, new lambertian(pertext));
    list[1] = new sphere(vec3( 0, 2 ,0), 2, new lambertian(pertext));
    list[2] = new sphere(vec3( 0, 7 ,0), 2, new diffuse_light(new constant_texture(vec3(4,4,4))));
    list[3] = new xy_rect(3,5,1,3,-2,new diffuse_light(new constant_texture(vec3(4,4,4))));
    return new hitable_list(list,4);
}

hitable *two_perlin_spheres(){
    texture *pertext = new noise_texture(0.1);
    hitable **list = new hitable*[2];
    list[0] = new sphere(vec3( 0,-1000,0), 1000, new lambertian(pertext));
    list[1] = new sphere(vec3( 0, 2 ,0), 2, new lambertian(pertext));
    return new hitable_list(list,2);
}

hitable *cornell_box(){
    hitable **list = new hitable*[8];
    int i = 0;
    material *red =new lambertian(new constant_texture(vec3(0.65, 0.05, 0.05)));
    material *white =new lambertian(new constant_texture(vec3(0.73, 0.73, 0.73)));
    material *green =new lambertian(new constant_texture(vec3(0.12, 0.45, 0.15)));
    material *light =new diffuse_light(new constant_texture(vec3(15, 15, 15 )));
    list[i++] = new flip_normals(new yz_rect(0,555,0,555,555,green));
    list[i++] = new yz_rect(0, 555, 0, 555, 555, green);
    //list[i++] = new yz_rect(0, 555, 0, 555, 0, red);
    list[i++] = new xz_rect(213, 343, 227, 332, 554,light);
    list[i++] = new flip_normals(new xz_rect(0,555,0,555,555,white));
    list[i++] = new xz_rect(0, 555, 0, 555, 0, white);
    //list[i++] = new xy_rect(0, 555, 0, 555, 555, white);
    list[i++] = new flip_normals(new xy_rect(0,555,0,555,555,white));
    list[i++] = new box(vec3(130,0,65),vec3(296,165,230),white);
    list[i++] = new box(vec3(265,0,295),vec3(430,330,460),white);

    list[i++] = new translate(new rotate_y(new box(vec3(0,0,0),vec3(165,165,165),white),-18),vec3(130,0,65));
    list[i++] = new translate(new rotate_y(new box(vec3(0,0,0),vec3(165,330,165),white),-18),vec3(265,0,295));

    return new hitable_list(list,i);
}

hitable *random_scene(){
    int n = 500;
    texture *checker = new checker_texture(new constant_texture(vec3(0.2, 0.3, 0.1)), new constant_texture(vec3(0.9, 0.9, 0.9)));
    hitable **list = new hitable*[n+1];

    list[0] = new sphere(vec3( 0, -1000, 0), 1000, new lambertian(checker));
    int i = 1;
    for(int a= -10; a < 10; a++){
        for(int b =-10; b < 10; b++){
            float choose_mat = drand48();
            vec3 center(a+0.9*drand48(), 0.2, b+0.9*drand48());
            if((center-vec3(4,0.2,0)).length() > 0.9){
                if(choose_mat < 0.8){
                    //list[i++] = new moving_sphere(center,center+vec3(0,0.5*drand48(),0), 0.0,1.0,0.2,new lambertian(vec3(drand48()*drand48(), drand48()*drand48(),drand48()*drand48())));
                    list[i++] = new moving_sphere(center,center+vec3(0,0.5*drand48(),0),0.0,1.0,0.2,new lambertian(new constant_texture(vec3(drand48()*drand48(), drand48()*drand48(), drand48()*drand48()))));
                }else if(choose_mat < 0.95){
                    list[i++] = new sphere(center, 0.2,
                           new metal(vec3(0.5*(1+drand48()), 0.5*(1+drand48()), 0.5*(1+drand48())), 0.5*drand48()));
                }else{
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }
    list[i++] = new sphere(vec3(0,1,0), 1.0 , new dielectric(1.5));
    list[i++] = new sphere(vec3(-4,1,0), 1.0 , new lambertian(new constant_texture(vec3(0.4,0.2,0.1))));
    list[i++] = new sphere(vec3(4,1,0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

    return new hitable_list(list, i);
}




int main()
{
    int nx = 200;
    int ny = 100;
    int ns = 100;
    rgba8* pixels = new rgba8[nx * ny];

    hitable *world = cornell_box();
/*
    vec3 lookfrom(13,2,3);
    vec3 lookat(0,0,0);
    float dist_to_focus = 10.0;
    float aperture =0.0;
    camera cam(lookfrom, lookat, vec3(0,1,0), 20 , float(nx)/float(ny), aperture, dist_to_focus,0.0,1.0);
*/
// /*
    vec3 lookfrom(278, 278, -800);
    vec3 lookat(278, 278, 0);
    float dist_to_focus = 10.0;
    float aperture =0.0;
    float vfov = 40.0;

    camera cam(lookfrom, lookat, vec3(0,1,0), vfov , float(nx)/float(ny), aperture, dist_to_focus,0.0,1.0);
// */
    for(int j = ny-1; j >= 0; j--){
        for(int i = 0; i < nx; i++){
            vec3 col(0, 0, 0);
            for( int s =0; s< ns;s++){
                float u = float(i +drand48() ) / float (nx);
                float v = float(j +drand48() ) / float (ny);
                ray r =cam.get_ray(u,v);
                vec3 p =r.point_at_parameter(2.0);
                col += color(r, world, 0);
            }
            col /= float(ns);
            col = vec3 (sqrt(col[0]), sqrt(col[1]),sqrt(col[2]));
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            //std::cout << ir <<" "<< ig << " " << ib<<"\n";
            pixels[(ny -1 -j)* nx + i] = rgba8(ir, ig, ib, 255);
        }
    }
    stbi_write_png("hello.png", nx, ny, 4, pixels, nx * 4);

    system("open hello.png");
    delete[] pixels;
}
