#include "vec3.h"
#include "mat4.h"
#include "vec4.h"
#include "debug.h"

int main() {

    Mat4 T = Mat4::translation(Vec3(1, 2, 3));
    Mat4 R = Mat4::rotation_z(3.14159265f / 2.0f);

    Vec4 p(0, 0, 0, 1);   // point
    Vec4 d(0, 0, 1, 0);   // direction

    print(Mat4::identity() * T);        // == T
    print(T * p);             // (1, 2, 3, 1)
    print(T * d);             // (0, 0, 1, 0) — unchanged
    print(R * Vec4(1,0,0,1)); // ~(0, 1, 0, 1)
    print(T * R * p);         // differs from R * T * p
    print(R * Mat4::rotation_z(-3.14159265f / 2.0f));  // identity
        
    return 0;
}