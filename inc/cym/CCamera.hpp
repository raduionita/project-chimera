#ifndef __cym_ccamera_hpp__
#define __cym_ccamera_hpp__

#include "cym/cym.hpp"
#include "glm/glm.hpp"
#include "glm/CFrustum.hpp"
#include "glm/CTransform.hpp"

namespace cym {
  class CCamera {
      enum class EProjection { ORTHOGRAPHIC = 1, PERSPECTIVE  = 2, };
    protected:
      bool mDirty {true};
      
      glm::vec3 mPosition        {0.f,0.f,0.f};
      glm::quat mOrientation {1.f,0.f,0.f,0.f}; // used when rotation & getting V matrix
      
    //sys::asc<glm::xform> mTransform; // position,orientation,scale
      
      
      glm::vec3 mForward {-glm::Z}; // v(0,0,-1)
      glm::vec3 mLeft    {-glm::X}; // v(-1,0,0)
      glm::vec3 mUp      { glm::Y}; // v(0,1,0)
      
      glm::real mFOV   {static_cast<glm::real>( 90.000f)}; // 
      glm::real mRatio {static_cast<glm::real>(  1.333f)}; // = 800/600
      glm::real mNear  {static_cast<glm::real>(  0.100f)};
      glm::real mFar   {static_cast<glm::real>(100.000f)};
      
      glm::mat4 mP;
      glm::mat4 mV;
    public:
// @todo: camera from position & distance (draw distance)
      CCamera(const glm::vec3& p, const glm::real d) : mPosition{p} {
        const glm::vec3 t {p * d};
        mForward = glm::normalize(t-p);
        mLeft    = glm::cross(mForward,mUp);
        
        mP       = glm::perspective(mFOV, mRatio, mNear, mFar);
        mV       = glm::lookat(mForward, mPosition+mForward, mUp);
      }
      /* camera from position(eye) & target */
      CCamera(const glm::vec3& p, const glm::vec3& t) : mPosition{p} {
        mForward = glm::normalize(t - p); // direction vector from position -> target
        mLeft    = glm::cross(mForward, mUp);
        
        mP = glm::perspective(mFOV, mRatio, mNear, mFar);
        mV = glm::lookat(mPosition, mPosition+mForward, mUp);
        
        // roll(180.f);
        // translateLocal(p.x,p.y *-1.f, p.z)
        
      }
// @todo: w/ ratio & fov
      CCamera(const glm::vec3& p, const glm::vec3& t, const glm::real fov, const glm::real ratio) : mPosition{p} {
        
      }
    public: // getter/setter(s)
      /* glm::frustum = cym::CCamera::getFrustum() */
      glm::frustum getFrustum() const {
// @todo: cache PV
// @todo: cache frustum
// @todo: use isDirty() to decide to re-calculate PV & frustum 
        // variables
        const glm::vec3 tRight {-mLeft}; // v(1,0,0)
        const glm::real two  {static_cast<glm::real>(2)};
        const glm::real thf {std::tan(glm::radians(mFOV / two))};
        // near w&h
        const glm::real tNearH {two * thf * mNear};
        const glm::real tNearW {tNearH * mRatio};
        // far w&h
        const glm::real tFarH {two * thf * mFar};
        const glm::real tFarW {tFarH * mRatio};
        // center of near & far planes 
        const glm::vec3 tNearC {mPosition + mForward * mNear};
        const glm::vec3 tFarC  {mPosition + mForward * mFar};
        // more variables
        const glm::vec3 tNearU {mUp * (tNearH / two)};
        const glm::vec3 tNearR {tRight * (tNearW / two)};
        const glm::vec3 tFarU  {mUp * (tFarH / two)};
        const glm::vec3 tFarR  {tRight * (tFarW / two)};
        // corners
        return sys::array<glm::vec3,8> {
          // LBN = Cnear - (up * (Hnear / 2)) - (right * (Wnear /2))
          tNearC - tNearU - tNearR, // tNearC - (mUp * (tNearH / two)) - (tRight * (tNearW / two)),
          // RBN = Cnear + (up * (Hnear / 2)) + (right * (Wnear / 2))
          tNearC - tNearU + tNearR, // tNearC - (mUp * (tNearH / two) + (tRight * (tNearW / two))),
          // LTN = Cnear + (up * (Hnear / 2)) - (right * (Wnear / 2))
          tNearC + tNearU - tNearR, // tNearC + (mUp * (tNearH / two) - (tRight * (tNearW / two))),
          // RTN = Cnear + (up * (Hnear / 2)) + (right * (Wnear / 2))
          tNearC + tNearU + tNearR, // tNearC + (mUp * (tNearH / two) + (tRight * (tNearW / two))),
          // LBF = Cfar - (up * (Hfar / 2)) - (right * (Wfar / 2))
          tNearC - tFarU  - tFarR,
          // RBF = Cfar - (up * (Hfar / 2)) + (right * (Wfar / 2))
          tNearC - tFarU  + tFarR,
          // LTF = Cfar + (up * (Hfar / 2)) - (right * (Wfar / 2))
          tNearC + tFarU  - tFarR,
          // RTF = Cfar + (up * (Hfar / 2)) + (right * (Wfar / 2))
          tNearC + tFarU  + tFarR
        };
        // return glm::frustum{mP*mV};
      }
      /* bool = cym::CCamera::isDirty() */
      inline bool isDirty() const { return mDirty; }
      /* get projection & view matrices */
      inline const glm::mat4& getP() const { return mP; }
      inline const glm::mat4& getV() const { return mV; }
      inline       glm::mat4 getPV() const { return mP * mV; }
      /* set ratio // dirty */
      inline void setRatio(const glm::real r) { mRatio = r; mDirty = true; }
      /* set fov // dirty */
      inline void setFOV(const glm::real f) { mFOV = f; mDirty = true; }
    public: // actions
      // @todo: after each action update mV & mP
      /* normalize all internal vectors */
      void normalize();
      /* pitch, yaw, roll rotation */
      void rotate(float pitch, float yaw, float roll);
      void rotate(const glm::vec3& pyr);
      /* x */
      void pitch(float v);
      /* y */
      void yaw(float v);
      /* z */
      void roll(float v);
  };
}

// calculate frustum corners
// float nearHeight = 2 * tan(mFOV / 2) * mNear;
// float nearWidth =  nearHeight * mRatio;
// 
// float farHeight = 2 * tan(mFOV / 2) * mFar;
// float farWidth = farHeight * mRatio;
// 
// glm::vec3 fc = mPos + mFront * mFar;
// glm::vec3 nc = mPos + mFront * mNear;
// 
// mFrustum.frustumCorners[0] = fc + (mUp * farHeight / 2.0f) - (mRight * farWidth / 2.0f);
// mFrustum.frustumCorners[1] = fc + (mUp * farHeight / 2.0f) + (mRight * farWidth / 2.0f);
// mFrustum.frustumCorners[2] = fc - (mUp * farHeight / 2.0f) - (mRight * farWidth / 2.0f);
// mFrustum.frustumCorners[3] = fc - (mUp * farHeight / 2.0f) + (mRight * farWidth / 2.0f);
// 
// mFrustum.frustumCorners[4] = nc + (mUp * nearHeight / 2.0f) - (mRight * nearWidth / 2.0f);
// mFrustum.frustumCorners[5] = nc + (mUp * nearHeight / 2.0f) + (mRight * nearWidth / 2.0f);
// mFrustum.frustumCorners[6] = nc - (mUp * nearHeight / 2.0f) - (mRight * nearWidth / 2.0f);
// mFrustum.frustumCorners[7] = nc - (mUp * nearHeight / 2.0f) + (mRight * nearWidth / 2.0f);
// 
// glm::vec4 test(1.0f, 1.0f, 1.0f,1.0f);
// glm::vec4 test2(-1.0f, -1.0f, -1.0f, 1.0f);
// glm::mat4 testingMatrix = glm::inverse(mProjectionMatrix * getViewMatrix());
// 
// test = testingMatrix*test;
// test2 = testingMatrix*test2;
// 
// test2.x /= test2.w;
// test2.y /= test2.w;
// test2.z /= test2.w;
// 
// test.x /= test.w;
// test.y /= test.w;
// test.z /= test.w;



// stackexchange
// This is a more general solution
// To start you will need some data.
// 
// The Camera's position represented by P (this is a point)
// 
// The normalized viewing vector represented by v
// 
// The Camera's up vector represented by up
// 
// The Camera's right vector represented by w (this is the cross product of v X up)
// 
// The near distance represented by nDis
// 
// The far distance represented by fDis
// 
// The field of view represented by fov (this usually in radians)
// 
// The aspect ratio represented by ar (this is the width of the screen divided by the height)
// 
// First we will get the width and height of the near plane
// 
// Hnear = 2 * tan(fov / 2) * nDis
// 
// Wnear = Hnear * ar
// 
// Then we do the same for the far plane
// 
// Hfar = 2 * tan(fov / 2) * fDis
// 
// Wfar = Hfar * ar
// 
// Now we get the center of the planes
// 
// Cnear = P + v * nDis
// 
// Cfar = P + v * fDis
// 
// And now we get our points
// 
// Near Top Left = Cnear + (up * (Hnear / 2)) - (w * (Wnear / 2))
// 
// Near Top Right = Cnear + (up * (Hnear / 2)) + (w * (Wnear / 2))
// 
// Near Bottom Left = Cnear - (up * (Hnear / 2)) - (w * (Wnear /2))
// 
// Near Bottom Right = Cnear + (up * (Hnear / 2)) + (w * (Wnear / 2))
// 
// Far Top Left = Cfar + (up * (Hfar / 2)) - (w * Wfar / 2))
// 
// Far Top Right = Cfar + (up * (Hfar / 2)) + (w * Wfar / 2))
// 
// Far Bottom Left = Cfar - (up * (Hfar / 2)) - (w * Wfar / 2))
// 
// Far Bottom Right = Cfar - (up * (Hfar / 2)) + (w * Wfar / 2))
// 
// Common assumptions that might be useful:
// 
// Most games have their field of view set at 110 degrees as this is close to the human field of view
// The camera is most often set at the origin (0,0,0)
// The view vector is usually along the negative Z axis (0,0,-1)
// The up vector is usually along the Y axis (0,1,0)
// The right vector is usually along the X axis (1,0,0)


#endif //__cym_ccamera_hpp__
