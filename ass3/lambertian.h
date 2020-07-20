#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H
#include "vec3.h"
#include"material.h"
#include"hitable.h"
class lambertian : public material{
   public:
       lambertain(const vec3& a) : albedo(a) {}
       virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const{
             vec3 target = rec.p + rec.normal + random_in_unit_sphere();
             scattered = ray(rec.p, target-rec.p);
             attenuation = albedo;
             return true;
       }
       vec3 albedo;
};

#endif // LAMBERTIAN_H
