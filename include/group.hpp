#ifndef GROUP_H
#define GROUP_H


#include "object3d.hpp"
#include "ray.hpp"
#include "hit.hpp"
#include "aabb.hpp"
#include <vector>


class Group : public Object3D {

public:

    Group() {

    }

    explicit Group (int num_objects) {
        objects.reserve(num_objects);
    }

    ~Group() override {

    }

    int getGroupSize() const {
        return objects.size();
    }

    const std::vector<shared_ptr<Object3D>> &getObjects() const {
        return objects;
    }

    bool intersect(const Ray &r, Hit &h, float tmin = 0.0, float tmax = infinity) const override {
        bool flag=false;
        float closest_t = tmax;
        for(auto it=objects.begin();it!=objects.end();it++){
            if((*it)->intersect(r,h,tmin,closest_t)){
                flag=true;
                closest_t = h.getT();
            }
        }
        return flag;
    }

    void addObject(int index, shared_ptr<Object3D> obj) {
        auto pos=objects.begin();
        while (index){
            index--;
            pos++;
        }
        objects.insert(pos,obj);
    }
    
    void addObject(shared_ptr<Object3D> obj) {
        objects.push_back(obj);
    }

    bool bounding_box(double time0, double time1, AABB& output_box) const override {
        if (objects.empty()) return false;

        AABB temp_box;
        bool first_box = true;

        for (const auto& object : objects) {
            if (!object->bounding_box(time0, time1, temp_box)) return false;
            output_box = first_box ? temp_box : AABB::surrounding_box(output_box, temp_box);
            first_box = false;
        }

        return true;
    }

    double pdf_value(const Vector3f &o, const Vector3f &v) const override {
        auto weight = 1.0/objects.size();
        auto sum = 0.0;

        for (const auto& object : objects)
            sum += weight * object->pdf_value(o, v);

        return sum;
    }

    Vector3f random(const Vector3f &o) const override {
        auto int_size = static_cast<int>(objects.size());
        return objects[random_int(0, int_size-1)]->random(o);
    }

private:
    std::vector<shared_ptr<Object3D>> objects;
};

#endif
	
