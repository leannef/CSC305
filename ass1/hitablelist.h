#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"
//#include "box.h"


class hitable_list: public hitable{
        public:
		hitable_list() {}
		hitable_list(hitable **l, int n) {list =l; list_size =n;}
		virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
        virtual bool bounding_box(float t0, float t1,aabb& box) const ;
		hitable **list;
        int list_size;
};

bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	hit_record temp_rec;
        bool hit_anything = false;
	double closest_so_far = t_max;
        for(int i=0; i < list_size; i++){
		if(list[i]->hit(r,t_min, closest_so_far, temp_rec)) {
			hit_anything =true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}


bool hitable_list::bounding_box(float t0, float t1, aabb& box)const{
    if(list_size<1)return false;
    aabb temp_box;
    bool first_true = list[0]->bounding_box(t0,t1,temp_box);
    if(!first_true)
        return false;
    else
        box = temp_box;
    for(int i=1;i<list_size;i++){
        if(list[0]->bounding_box(t0,t1,temp_box)){
            box=surrounding_box(box,temp_box);
        }
        else
            return false;
    }
    return true;
}

class box: public hitable{
public:
    box() {}
    box(const vec3& p0, const vec3& p1, material *ptr);
    virtual bool hit(const ray& r, float t0, float t1, hit_record& rec) const;
    virtual bool bounding_box(float t0, float t1, aabb& box) const{
        box = aabb(pmin, pmax);
        return true;
    }
    vec3 pmin, pmax;
    hitable *list_ptr;
};

box::box(const vec3& p0, const vec3& p1, material *ptr){
    pmin = p0;
    pmax = p1;
    hitable **list = new hitable * [6];
    list[0] = new xy_rect(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), ptr);
    list[1] = new flip_normals(new xy_rect(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), ptr));
    list[2] = new xz_rect(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), ptr);
    list[3] = new flip_normals(new xz_rect(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), ptr));
    list[4] = new yz_rect(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), ptr);
    list[5] = new flip_normals(new yz_rect(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), ptr));
    list_ptr = new hitable_list(list, 6);
}

bool box::hit(const ray& r, float t0, float t1, hit_record& rec) const{
    return list_ptr->hit(r, t0, t1, rec);
}

#endif
