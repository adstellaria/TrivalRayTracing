#ifndef MESH_H
#define MESH_H

#include <vector>
#include "object3d.hpp"
#include "triangle.hpp"
#include "Vector2f.h"
#include "Vector3f.h"
#include "utils.hpp"



class Mesh : public Object3D {

public:
    Mesh(const char *filename, shared_ptr<Material> m);
    Mesh(const std::vector<shared_ptr<Object3D>> &tri, shared_ptr<Material> m);

    struct TriangleIndex {
        TriangleIndex() {
            x[0] = 0; x[1] = 0; x[2] = 0;
        }
        int &operator[](const int i) { return x[i]; }
        int operator[](const int i) const { return x[i]; }
        // By Computer Graphics convention, counterclockwise winding is front face
        int x[3]{};
    };

    std::vector<Vector3f> v;
    std::vector<TriangleIndex> t;
    std::vector<Vector3f> n;
    std::vector<shared_ptr<Object3D>> triangle;
    shared_ptr<Object3D> triangle_bvh;
    bool intersect(const Ray &r, Hit &h, float tmin = 0.0, float tmax = infinity) const override;
    bool bounding_box(double time0, double time1, AABB& output_box) const override;

private:

    // Normal can be used for light estimation
    void computeNormal();
};

#endif
