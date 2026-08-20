#pragma once
#include <cassert>
#include <cmath>
#include <algorithm>
#include "mat4.h"
#include "constants.h"
#include "vec3.h"

struct CameraBasis {
    Vec3 right;
    Vec3 up; 
    Vec3 forward;
};

struct Camera {
    
    Vec3 position{0.0f, 0.0f, 0.0f};
    Camera(Vec3 position) : position(position) {};
    Camera() : position(Vec3()) {};

    float fovy = kPi / 3.0f; 
    float near_pl = 0.1f;
    float far_pl = 100.0f;
    
    CameraBasis basis() const {
        const float sy = std::sin(yaw_);
        const float cy = std::cos(yaw_);
        const float sp = std::sin(pitch_);
        const float cp = std::cos(pitch_);

        return CameraBasis{
            Vec3 {cy,       0.0f, -sy      }, // right
            Vec3 {sy * sp,  cp,   cy * sp  }, // up
            Vec3 {-sy * cp, sp,   -cy * cp } // forward
        };
    }

    Vec3 right()   const { return basis().right;   }
    Vec3 up()      const { return basis().up;      }
    Vec3 forward() const { return basis().forward; }
    
    Mat4 view() const {
        return Mat4::look_at(position, position + forward(), kWorldUp);
    }
    
    Mat4 projection(float aspect) const {
        return Mat4::perspective(fovy, aspect, near_pl, far_pl);
    }

    void rotate(float dyaw, float dpitch) {
        assert(std::isfinite(dyaw) && std::isfinite(dpitch) && "non-finite rotation delta");
        yaw_ = std::remainder(yaw_ + dyaw, kTwoPi);
        if (yaw_ == -kPi) {
            yaw_ += kTwoPi;
        } // Force bounds (-pi, +pi]

        pitch_ = std::clamp(pitch_ + dpitch, -kMaxPitch, kMaxPitch);
    }

    void move(const Vec3& d) {
        assert(std::isfinite(d.x) && std::isfinite(d.y) && std::isfinite(d.z) && "non-finite move delta");
        const CameraBasis b = basis(); 
        position = position + b.right * d.x + kWorldUp * d.y + b.forward * d.z; // +z is forward
    }

    float yaw() const {
        return yaw_;
    }

    float pitch() const {
        return pitch_;
    }

    private:
        static constexpr float kMaxPitch = radians(88.0f);
        float yaw_   = 0.0f;
        float pitch_ = 0.0f;

};