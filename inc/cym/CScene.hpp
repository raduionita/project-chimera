#ifndef __cym_cscene_hpp__
#define __cym_cscene_hpp__

#include "sys/TPointer.hpp"
#include "sys/TBlock.hpp"
#include "sys/CException.hpp"
#include "cym/cym.hpp"
#include "cym/CResource.hpp"
#include "cym/CGeometry.hpp"
#include "cym/CLight.hpp"
#include "glm/glm.hpp"
#include "glm/CFrustum.hpp"
#include "glm/CAABB.hpp"
#include "glm/CQuaternion.hpp"
#include "glm/CMatrix.hpp"
#include "glm/CTransform.hpp"

#include <array>

namespace cym {
  class CScene;
  class CNode; 
  class CCell; 
  class COctree; 
  class CQuery;
  class CResult; 
  
  class CSceneLoader; template<typename T> class TSceneLoader;
  
  class CSceneManager;
  
  class CComponent;
  
  // component(s) ////////////////////////////////////////////////////////////////////////////////////////////////////

// @todo: node component, like pshysics info, meta data, game data, ai, controller...  
  class CComponent {

  };
  
  // nodes ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  enum ENode { NONE = -1, BASIC = 0, SCENE = 1, JOINT, ENTITY/*=3*/, LIGHT, CAMERA/*=5*/, FORCE, DRAWABLE, MODEL/*=8*/ = DRAWABLE + 1, EMITTER = DRAWABLE + 2 };
  
  class CNode {
      friend class CScene;
      friend class CCell;
      friend class COctree;
      friend class CQuery;
      friend class CResult;
      typedef sys::string node_name;
      typedef sys::string name_t;
      typedef uint id_t;
    private:
// @todo: make std::atomic<int>
      static id_t                            sID;
    protected:
      id_t                                   mID {sID++};
// @todo: code for mDirty = false // when everything got updated
      bool                                   mDirty {true}; // = something changed
      sys::string                              mName;
      glm::aabb                              mAABB;
      // transform
      glm::xform                             mTransform;
        glm::vec3& mPosition;
        glm::quat& mOrientation; 
        glm::vec3& mScale;
      std::map<name_t, sys::spo<CNode>>      mNodes;
/* @todo: rename to parent // parent: if null => root node */
      sys::wpo<CNode>                        mRoot;
      // cell linked to this node
      sys::wpo<CCell>                        mCell;
    public:
      CNode(const sys::string& tName, const glm::aabb& = 0, const glm::xform& = 0);
      virtual ~CNode();
    public:
      inline sys::spo<CNode> operator [](const name_t& tName) const { auto it {mNodes.find(tName)}; return it == mNodes.end() ? nullptr : it->second; } 
    public:
      friend std::ostream& operator <<(std::ostream&, const CNode&);
      friend const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel&, const CNode&);
    public:
      /* test type of node */
      virtual inline bool isBasic()     const { return false; }
      virtual inline bool isJoint()     const { return false; }
      virtual inline bool isEntity()    const { return false; }
      virtual inline bool isLight()     const { return false; }
      virtual inline bool isCamera()    const { return false; }
      virtual inline bool isForce()     const { return false; }
      virtual inline bool isDrawable()  const { return false; }
      virtual inline bool isModel()     const { return false; } // drawable
      virtual inline bool isEmitter()   const { return false; } // drawable
      /* for TNode<ENode> conversion */
      virtual inline ENode getType() const { throw sys::exception("NOT IMPLEMENTED",__FILE__,__LINE__); }
      /* this node's name */
      inline const sys::string& getName() const { return mName; }
      /* is dirty */
      inline bool isDirty() const { return !isRoot() && (mRoot->isDirty() || mDirty); }
      /* rootless/baseless? */
      inline bool isRoot() const { return mRoot == nullptr; }
      /* return 1st level child nodes */
      inline const decltype(mNodes)& getNodes() const { return mNodes; }
      /* get absolute AABB */
      inline       glm::aabb  getAABB()         const { return  getAbsoluteAABB(); }
      inline       glm::aabb  getAbsoluteAABB() const { return  getTransform() * mAABB; }
      inline const glm::aabb& getRelativeAABB() const { return mAABB; }
      /* get node's absolute transform */
      inline glm::xform        getTransform()         const { return getAbsoluteTransform(); }
      inline glm::xform        getAbsoluteTransform() const { return (isRoot()) ? (getRelativeTransform()) : (mRoot->getAbsoluteTransform() * getRelativeTransform()) ; }
      inline const glm::xform& getRelativeTransform() const { return mTransform; }
      /* get model matrix for this node */
      inline const glm::mat4 getMatrix()         const { return getAbsoluteMatrix(); }
      inline const glm::mat4 getAbsoluteMatrix() const { return (isRoot()) ? (getRelativeMatrix()) : (mRoot->getAbsoluteMatrix() * getRelativeMatrix()); }
      inline const glm::mat4 getRelativeMatrix() const { return mTransform.toMatrix(); }
      /* get node's absolute position  */
      inline       glm::vec3  getPosition()         const { return getAbsolutePosition(); }
      inline       glm::vec3  getAbsolutePosition() const { return (isRoot()) ? (getRelativePosition()) : (mRoot->getAbsolutePosition() + getRelativePosition()); }
      inline const glm::vec3& getRelativePosition() const { return mTransform.position; }
      /* get node's absolute orientation  */
      inline       glm::quat  getOrientation()         const { return getAbsoluteOrientation(); }
      inline       glm::quat  getAbsoluteOrientation() const { return (isRoot()) ? (getRelativeOrientation()) : (mRoot->getAbsoluteOrientation() * getRelativeOrientation()) ; }
      inline const glm::quat& getRelativeOrientation() const { return mTransform.orientation; }
      /* get node's absolute scale  */
      inline       glm::vec3  getScale()         const { return getAbsoluteScale(); }
      inline       glm::vec3  getAbsoluteScale() const { return (isRoot()) ? (getRelativeScale()) : (mRoot->getAbsoluteScale() * getRelativeScale()) ; }
      inline const glm::vec3& getRelativeScale() const { return mTransform.scale; }
      /* returns the root/parent of this node */
      inline const decltype(mRoot)& getRoot() const { return mRoot; }
      /* return cell containing this node */
      inline decltype(mCell) getCell() const { return mCell; }
      inline bool            hasCell() const { return mCell != nullptr; }
      /* set (local) position */
      virtual inline void setPosition(const glm::vec3& p) { mPosition = p; mDirty = true; }
      /* set (local) orientation */
      virtual inline void setOrientation(const glm::quat& Q) { mOrientation = glm::normalize(Q); mDirty = true; }
      /* set (local) orientation using eular angles (pitch, yaw, roll) */
              inline void setOrientation(const glm::vec3& pyr) { setOrientation(glm::quat{pyr}); }
      /* set (local) scale */
      virtual inline void setScale(const glm::vec3& s) { mScale = s; mDirty = true; }
      /* set (local) scale (uniform,scalar) */
              inline void setScale(const glm::real s) { setScale(glm::vec3{s}); }
    public: // as parent 
      /* attach tNode to this, add to mNodes and extend this.mAABB */
      void            push(sys::spo<CNode> tNode);
      /* pop CNode by name, and return it */
      sys::spo<CNode> pull(const sys::string& tName);
    public: // as child
      /** detach from current parent => rootless node */
      void yield();
      /** cling this to a parent (tParent::push(this)) */
      void cling(sys::spo<CNode> tParent);
      /** from one parent (this.mRoot) to another parent (tParent) */
      void shift(sys::spo<CNode> tParent);
      /** extend this.mAABB (and all its ancestors) by tAABB  */
      void extend(const glm::aabb& tAABB);
      /** rebuild this.mAABB (and all its ancestors) using children's mAABBs  */
      bool shrink();
    public: // transform actions
      /* pitch, yaw, roll rotation */
      void rotate(const glm::real pitch, const glm::real yaw, const glm::real roll);
      void rotate(const glm::vec3& pyr);
      /* orbit (revolve) round a point on an axis (default:Y) */
      inline void orbit(const glm::vec3& v, const glm::real deg, const glm::vec3& axis = glm::Y) {
        // // translate the object to the center
        // const glm::mat4 T  {glm::translate(v)};
        // // make the rotation
        // const glm::mat4 R  {glm::rotate(deg, axis)};
        // // translate the object back to its original location
        // const glm::mat4 Ti {glm::translate(-v)}; // = glm::inverse(T)
        // // transform
        // mPosition = (T * R * Ti) * mPosition;
        //
        // return;
        
        const glm::mat4 R {glm::rotate(deg,axis)};
        const glm::vec4 r {R * glm::vec4{mPosition - v, 1.f}};
        mPosition = glm::vec3(r) + v;
        
// @todo: orientation needs to be updated too
      }
      /* rotate x */
      virtual inline void pitch(const glm::real deg) {
        // x axis
        mOrientation = glm::normalize(glm::quat{deg, glm::X} * mOrientation);
        // dirty
        mDirty = true;
      }
      /* rotate y */
      virtual inline void yaw(const glm::real deg) {
        // quat Y 
        mOrientation = glm::normalize(glm::quat{deg, glm::Y} * mOrientation);
        // dirty
        mDirty = true;
      }
      /* rotate z */
      virtual inline void roll(const glm::real deg) {
        // quat
        mOrientation = glm::normalize(glm::quat{deg, -glm::Z} * mOrientation);
        // dirty
        mDirty = true;
      }
      /* move by vector */
      inline void move(const glm::vec3& v) { mPosition += v; mDirty = true; }
      /* scale uniform */
      inline void scale(const glm::real tScale) { mScale *= tScale; mDirty = true; }
      /* scale non-uniform */
      inline void scale(const glm::vec3& tScale) { mScale *= tScale; mDirty = true; }
    public: // event handles
// @todo: mDirty = true => recalculates aabb & cell
    //virtual inline void onDirty();
  };
  
  template<const ENode T> class TNode : public CNode {
    public:
      virtual inline ENode getType() const override { return T; }
  };
  
  template<> class TNode<ENode::BASIC> : public CNode {
    public:
      using CNode::CNode;
    public:
      virtual inline bool isBasic() const override final { return true; }
      virtual inline ENode getType() const override { return ENode::BASIC; }
  }; typedef TNode<ENode::BASIC> NBasic;
  
  template<> class TNode<ENode::JOINT> : public TNode<ENode::BASIC> {
    protected:
    //sys::wpo<CJoint> mJoint; // link to real joint  
    public:
      using TNode<ENode::BASIC>::TNode;
    public:
      virtual inline bool isJoint() const override final { return true; }
      virtual inline ENode getType() const override { return ENode::JOINT; }
  }; typedef TNode<ENode::JOINT> NJoint;
  
  template<> class TNode<ENode::ENTITY> : public TNode<ENode::BASIC> {
    public:
      using TNode<ENode::BASIC>::TNode;
    public:
      virtual inline bool isEntity() const override final { return true; }
      virtual inline ENode getType() const override { return ENode::ENTITY; }
  }; typedef TNode<ENode::ENTITY> NEntity;
  
  template<> class TNode<ENode::LIGHT> : public TNode<ENode::BASIC> {
    public:
      enum EModel { POINT, OMNI = POINT, DIRECT, SPOT, AREA };
    protected:
      // sys::spo<ILight> mLight;
        // type = POINT/OMNI, DIRECT, SPOT, AREA
          // type = POINT
            // position == glm::vec3 (POINT,SPOT)
            // k0,k1,k2 = float      (POINT,SPOT)
            // direction = glm::vec3 (DIRECT,SPOT)
            // cutoff = float        (SPOT)
        // color = glm::vec3
        // ambient intesity = float
        // diffuse intensity = float
    public:
      virtual inline bool  isLight() const override final { return true; }
      virtual inline ENode getType() const override final { return ENode::LIGHT; }
      
      // ogl geometry (for debugcall)
      //       // basically, 3-line-star-ish "geometry" 
      //       float vertices[] = {
      //         -0.25f, 0.0f,   0.0f, 
      //          0.25f, 0.0f,   0.0f, 
      //           0.0f,-0.25f,  0.0f, 
      //           0.0f, 0.25f,  0.0f, 
      //           0.0f,  0.0f,-0.25f, 
      //           0.0f,  0.0f, 0.25f };
      //          
      //       glGenBuffers(1, &mVBO);
      //       glBindBuffer(GL_ARRAY_BUFFER, mVBO);
      //       glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
      //       
      //       glGenVertexArrays(1, &mVAO);
      //       glBindVertexArray(mVAO);
      //       glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)((0) * sizeof(GLfloat)));
      //       glEnableVertexAttribArray(0);
      
      // on debugcall
      //       glBindVertexArray(mVAO);
      //       glBindBuffer(GL_ARRAY_BUFFER, mVBO);
      //       
      //       glEnable(GL_POLYGON_OFFSET_LINE);
      //       glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      //       glLineWidth(2.0f);
      //       
      //       bool bDepthTest = glIsEnabled(GL_DEPTH_TEST);
      //       bool bStencilTest = glIsEnabled(GL_STENCIL_TEST);
      //       if(bDepthTest)
      //         glDisable(GL_DEPTH_TEST);
      //       if(bStencilTest)  
      //         glDisable(GL_STENCIL_TEST);
      //         
      //       glDrawArrays(GL_LINES, 0, 6);
      //       
      //       if(bDepthTest)
      //         glEnable(GL_DEPTH_TEST);
      //       if(bStencilTest)  
      //         glEnable(GL_STENCIL_TEST);
      // 
      //       glBindVertexArray(0);
      //       
      //       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      //       glDisable(GL_POLYGON_OFFSET_LINE);
  }; typedef TNode<ENode::LIGHT> NLight;
  
  template<> class TNode<ENode::CAMERA> : public TNode<ENode::BASIC> {
  /**
   * @see https://www.3dgep.com/understanding-the-view-matrix/#Look_At_Camera
   * @see https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/camera.h
   */
    public:
      // camera types: scene/game, editor(virtual,cannot be accessed outside editor), debug(can see what other cameras have in their view frustum, cannot be accessed outside editor)
      enum EScope { GAME = 0, EDITOR, DEBUG };
      enum EProjection { ORTHOGRAPHIC = 1, PERSPECTIVE = 2, };
    protected:
      
// @TODO debugables for camera
      // sys::map<uint,CSymbol> mSymbols;
      // axies
        // - geometry (3 lines, 6 vertices) // empty: draw 6 indices w/o inputs, default data can be in the shader
        // - geometru (3 triangles facing camera)
        // - variables (uniforms) // use uniforms to update positions
      // cage (aabb) // geometry (cuboid)
      // icon // = geometry (rect square) + image (texture) of the icon
      // frustum
      
      
      
      
      EScope mScope {EScope::GAME}; // | EDITOR | DEBUG
      
      glm::vec3 mTarget  { glm::O};
      glm::vec3 mForward {-glm::Z}; // v(0,0,-1)
      glm::vec3 mRight   { glm::X}; // v(1,0,0)
      glm::vec3 mUp      { glm::Y}; // v(0,1,0)
      
      glm::real mFOV   {static_cast<glm::real>( 90.000f)}; // 
      glm::real mRatio {static_cast<glm::real>(  800.f/600.f)}; // = 800/600 = 1.333f
      glm::real mNear  {static_cast<glm::real>(  0.100f)};
      glm::real mFar   {static_cast<glm::real>(100.000f)};
      
      glm::mat4 mP;
      glm::mat4 mV;
    public:
      using TNode<ENode::BASIC>::TNode;
      /* NCamera{scope} */
      TNode(EScope tScope=EScope::GAME);
      /* NCamera{fov,ratio,near,far,scope} */
      TNode(const glm::vec3& tTarget, const glm::real tFOV=90.f, const glm::real tRatio=1.333f, const glm::real tNear=0.01f, const glm::real tFar=100.f, EScope tScope=EScope::GAME);
      TNode(                          const glm::real tFOV=90.f, const glm::real tRatio=1.333f, const glm::real tNear=0.01f, const glm::real tFar=100.f, EScope tScope=EScope::GAME);
    public: // getters
      virtual inline bool isCamera() const override final { return true; }
      virtual inline ENode getType() const override final { return ENode::CAMERA; }
      /* get absolute target // accounting for parents movement */
      inline       glm::vec3  getTarget() const { return getPosition() + mForward; }
      inline const glm::vec3& getUp() const { return mUp; } 
      inline const glm::vec3& getForward() const { return mForward; } 
      /* glm::frustum = cym::CCamera::getFrustum() */
      glm::frustum getFrustum() {
        setTarget(mTarget);
        // variables
        const glm::vec3  tPosition {getPosition()};
        const glm::vec3& tRight    {mRight}; // v(1,0,0)
        const glm::real  thf       {std::tan(glm::radians(mFOV / glm::TWO))};
        // near w&h
        const glm::real  tNearH {glm::TWO * thf * mNear};
        const glm::real  tNearW {tNearH * mRatio};
        // far w&h
        const glm::real  tFarH  {glm::TWO * thf * mFar};
        const glm::real  tFarW  {tFarH * mRatio};
        // center of near & far planes 
        const glm::vec3  tNearC {tPosition + mForward * mNear};
        const glm::vec3  tFarC  {tPosition + mForward * mFar};
        // more variables
        const glm::vec3  tNearU {mUp *    (tNearH / glm::TWO)};
        const glm::vec3  tNearR {tRight * (tNearW / glm::TWO)};
        const glm::vec3  tFarU  {mUp *    (tFarH / glm::TWO)};
        const glm::vec3  tFarR  {tRight * (tFarW / glm::TWO)};        
        
        // yFac = tanf(FoV * PI/360.0f);
        // xFac = yFac*aspectRatio;
        // 
        // Vector3 Forward, Right, Up; //Simply the three columns from your transformation matrix (or the inverse of your view matrix)
        // 
        // Vector3 farLeftTop = Position + Forward*far - far*Right*xFac*far + Up*yFac*far;
        // Vector3 farRightTop = Position + Forward*far + far*Right*xFac*far + Up*yFac*far;
        // Vector3 farLeftBottom = Position + Forward*far - far*Right*xFac*far - Up*yFac*far;
        // Vector3 farLeftBottom = Position + Forward*far + far*Right*xFac*far - Up*yFac*far;
        // corners
        return {sys::array<glm::vec3,8> {
          // LBN = Cnear - (up * (Hnear / 2)) - (right * (Wnear /2))
          tNearC - tNearU - tNearR, // tNearC - (mUp * (tNearH / two)) - (tRight * (tNearW / two)),
          // RBN = Cnear + (up * (Hnear / 2)) + (right * (Wnear / 2))
          tNearC - tNearU + tNearR, // tNearC - (mUp * (tNearH / two) + (tRight * (tNearW / two))),
          // LTN = Cnear + (up * (Hnear / 2)) - (right * (Wnear / 2))
          tNearC + tNearU - tNearR, // tNearC + (mUp * (tNearH / two) - (tRight * (tNearW / two))),
          // RTN = Cnear + (up * (Hnear / 2)) + (right * (Wnear / 2))
          tNearC + tNearU + tNearR, // tNearC + (mUp * (tNearH / two) + (tRight * (tNearW / two))),
          // LBF = Cfar - (up * (Hfar / 2)) - (right * (Wfar / 2))
          tFarC  - tFarU  - tFarR,
          // RBF = Cfar - (up * (Hfar / 2)) + (right * (Wfar / 2))
          tFarC  - tFarU  + tFarR,
          // LTF = Cfar + (up * (Hfar / 2)) - (right * (Wfar / 2))
          tFarC  + tFarU  - tFarR,
          // RTF = Cfar + (up * (Hfar / 2)) + (right * (Wfar / 2))
          tFarC  + tFarU  + tFarR }};
        
        // return glm::frustum{getP()};
      }
      /* get projection matrix */
      inline const glm::mat4& getP() {
        if (isDirty()) {
          mP = glm::perspective(mFOV, mRatio, mNear, mFar);
        }
        return mP; 
      }
      /* get view matrix */
      inline const glm::mat4& getV() { 
        // bascially do a glm::lookat(...)
        if (isDirty()) {
          setTarget(mTarget);
          
          // const glm::quat Q {glm::normalize(getOrientation())};
          // const glm::mat4 R {glm::asMatrix(Q)};
          // const glm::vec3 P {getPosition()}; 
          // const glm::mat4 T {glm::translate(-P)};
          //
          // mV = R * T;
          
          // const glm::vec3  tPosition {getPosition()};
          // const glm::vec3& tTarget {mForward};
          // const glm::vec3& tUp {mUp};
          // mV = glm::lookat(tPosition, tTarget, tUp);
          
          const glm::vec3  p {getPosition()};
          const glm::vec3& f {mForward}; 
          const glm::vec3& s {mRight};
          const glm::vec3& u {mUp};
          mV = glm::mat4{glm::vec4(/* m.0   */s.x,/* m.1  */ u.x,/* m.2  */-f.x, glm::ZERO), // r0 |  sx   sy   sz -(s*p) |
                         glm::vec4(/* m.4   */s.y,/* m.5  */ u.y,/* m.6  */-f.y, glm::ZERO), // r1 |  ux   uy   uz -(u*p) |
                         glm::vec4(/* m.8   */s.z,/* m.9  */ u.z,/* m.10 */-f.z, glm::ZERO), // r2 | -fx  -fy  -fz  (f*p) |
                         glm::vec4(-glm::dot(s,p),-glm::dot(u,p), glm::dot(f,p),  glm::ONE)};// r3 |   0    0    0      1 |

          

          //         math::quat Q = mOrientation;
          //         Q.inverse();
          //         mViewMatrix = Q.asMatrix();
          //         
          //         math::vec3 v = -mPosition;
          //         math::mat4 m = mViewMatrix;
          //         mViewMatrix[3] = (m[0] * v[0]) + (m[1] * v[1]) + (m[2] * v[2]) + m[3];
          //         
          //         mViewMatrix = math::scale(-1.0f) * mViewMatrix; //@FIX: Handedness fix
          
// @todo: create mV from orientation
//           mV = getOrientation().inverse().toMatrix();
          // mV = glm::translate(mV, getPosition());
          
          
          // glm::vec3 tPosition {getPosition()};
        }
        return mV; 
      }
      /* get combined P & V matrices   */
      inline       glm::mat4 getPV() { return getP() * getV(); }
    public: // setters,dirty
      /* set orientation, apply rotation */
      virtual inline void setOrientation(const glm::quat& Q) override { mOrientation.identity(); rotate(Q); }
      /* set camera target, after inserting it in the scene */
      inline       void       setTarget(const glm::vec3& tTarget) {
// @todo: assert "is part of a scene or is inside an entity"?
        mForward = glm::normalize(tTarget - getPosition());
        mRight   = glm::normalize(glm::cross(mForward, glm::Y));
        mUp      = glm::cross(mRight,mForward);
        mTarget  = tTarget;
      }
      /* set ratio // dirty */
      inline void setRatio(const glm::real r) { mRatio = r; mDirty = true; }
      /* set fov // dirty */
      inline void setFOV(const glm::real f) { mFOV = f; mDirty = true; }
      /* set near */
      inline void setNear(const glm::real n) { mNear = n; mDirty = true; }
      /* set far */
      inline void setFar(const glm::real f) { mFar = f; mDirty = true; }
    public: // actions
// @todo: cache PV
// @todo: cache frustum
// @todo: use isDirty() to decide to re-calculate PV & frustum 
// @todo: after each action update mV & mP
      /* normalize all internal vectors */
      void normalize() {
        mRight.normalize();
        mUp.normalize();
        mForward.normalize();
        mOrientation.normalize();
        
        mRight = glm::cross(mForward, mUp);
        mUp    = glm::cross(mRight, mForward);
      }
      /* move local (using left,up,forward) */
      inline void move(const glm::real tRight/*x*/, const glm::real tUp/*y*/, const glm::real tForward/*-z*/) {
        mPosition += tRight   * mRight;
        mPosition += tUp      * mUp;
        mPosition += tForward * mForward;
        mDirty     = true;
      } 
      /* zoom */
      inline void zoom(const glm::real tZoom) {
        mFOV -= tZoom;
        glm::clamp(mFOV, static_cast<glm::real>(1.f), static_cast<glm::real>(110.f));
        mDirty = true;
      }
      /* rotate using quaternion */
      inline void rotate(const glm::quat& Q) {
        mRight   = glm::normalize(glm::rotate(Q, mRight));
        mUp      = glm::normalize(glm::rotate(Q, mUp));
        mForward = glm::normalize(glm::rotate(Q, mForward));
        
        mOrientation = glm::normalize(Q * mOrientation);
        mDirty       = true;
      }
      /* rotate using angle & axis (local) */
      inline void rotate(const glm::real tDeg, const glm::vec3& tAxis) {
        rotate(glm::quat{tDeg, glm::normalize(tAxis)});
      }
      /* rotate x */
      virtual inline void pitch(const glm::real deg) override {
        glm::quat Q {deg, mRight};
        // 
        mUp          = glm::normalize(glm::rotate(Q, mUp));
        mForward     = glm::normalize(glm::rotate(Q, mForward));
        // quat
        mOrientation = glm::normalize(Q * mOrientation);
        // dirty
        mDirty = true;
      }
      /* rotate y */
      virtual inline void yaw(const glm::real deg) override {
        // quat
        glm::quat Q{deg, mUp};
        // 
        mRight   = glm::normalize(glm::rotate(Q, mRight));
        mForward = glm::normalize(glm::rotate(Q, mForward));
        // quat
        mOrientation = glm::normalize(Q * mOrientation);
        // dirty
        mDirty = true;
      }
      /* rotate z */
      virtual inline void roll(const glm::real deg) override {
        // quat
        glm::quat Q{deg, mForward};
        // vectors
        mUp    = glm::normalize(glm::rotate(Q, mUp));
        mRight = glm::normalize(glm::rotate(Q, mRight));
        // quat
        mOrientation = glm::normalize(Q * mOrientation);
        // dirty
        mDirty = true;
      }
  }; typedef TNode<ENode::CAMERA> NCamera;
  
  template<> class TNode<ENode::FORCE> : public TNode<ENode::BASIC> {
    protected:
    //force descriptor
    public:
      virtual inline bool isForce() const override final { return true; }
      virtual inline ENode getType() const override { return ENode::FORCE; }
  }; typedef TNode<ENode::FORCE> NForce;
  
  template<> class TNode<ENode::DRAWABLE> : public TNode<ENode::BASIC> {
    public:
      using TNode<ENode::BASIC>::TNode;
    public:
      virtual inline bool  isDrawable() const override final { return true; }
      virtual inline ENode getType()    const override { throw sys::exception("NOT IMPLEMENTED",__FILE__,__LINE__); }
  };
  
  template<> class TNode<ENode::MODEL> : public TNode<ENode::DRAWABLE> {
    protected:
      
// @TODO debugables for model
      // sys::map<uint,CSymbol> mSymbols;
      // axies
        // - geometry (3 lines, 6 vertices) // empty: draw 6 indices w/o inputs, default data can be in the shader
        // - geometry (3 triangles facing camera)
        // - variables (uniforms) // use uniforms to update positions
      // cage (aabb) // geometry (cuboid)
      // icon // = geometry (rect square) + image (texture) of the icon
      
      
      
      sys::spo<CGeometry> mGeometry;
// @todo: move collider at scene(node) level, as a component/plugin (for physics)?!
    //cym::CCollider mCollider;
    public:
      using TNode<ENode::DRAWABLE>::TNode;
      /* node from geometry */
      TNode(sys::spo<CGeometry> pGeometry);
      /* node from geometry w/ custom name */
      TNode(const sys::string& tName, sys::spo<CGeometry> pGeometry);
    public:
      virtual inline bool  isModel() const override final { return true; }
      virtual inline ENode getType() const override { return ENode::MODEL; }
    public:
      inline void                setGeometry(sys::spo<CGeometry> pGeometry) { mGeometry = pGeometry; mAABB = pGeometry->getAABB(); }
      inline decltype(mGeometry) getGeometry() const { return mGeometry; }
  }; typedef TNode<ENode::MODEL> NModel;
  
  template<> class TNode<ENode::EMITTER> : public TNode<ENode::DRAWABLE> {
    protected:
    // emitter descriptor
    public:
      using TNode<ENode::DRAWABLE>::TNode;
    public:
      virtual inline bool isEmitter() const override final { return true; }
      virtual inline ENode getType() const override { return ENode::EMITTER; }
  }; typedef TNode<ENode::EMITTER> NEmitter;
  
  // tree ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CResult {
      friend class CScene;
      friend class COctree;
      friend class CCell;
      friend class CQuery;
    protected:
      sys::vector<sys::spo<TNode<ENode::ENTITY>>> mNodes;
    public:
      /* return found nodes */
      inline const decltype(mNodes)& getNodes() const { return mNodes; }
      /* return found nodes */
      inline const decltype(mNodes)& getEntities() const { return mNodes; }
      /* return found drawable (model,emitter) nodes */
      inline const sys::vector<sys::spo<TNode<ENode::DRAWABLE>>> getDrawables() {
        sys::vector<sys::spo<TNode<ENode::DRAWABLE>>> tDrawables;
        // for each node:scene in mNodes -> for each node:? in node:scene  
        for (auto& tNode : mNodes) for (auto& [tName,tChild] : tNode->mNodes) if (tChild->isDrawable()) {
          tDrawables.push_back(sys::static_pointer_cast<TNode<ENode::DRAWABLE>>(tChild)); 
        }
        return tDrawables;
      }
      /* return found model nodes */
      inline const sys::vector<sys::spo<TNode<ENode::MODEL>>> getModels() {
        sys::vector<sys::spo<TNode<ENode::MODEL>>> tModels;
        for (auto& tNode : mNodes) for (auto& [tName,tChild] : tNode->mNodes) if (tChild->isModel()) {
          tModels.push_back(sys::static_pointer_cast<TNode<ENode::MODEL>>(tChild)); 
        } 
        return tModels;
      }
      /* return geometries from found nodes */
      inline const sys::vector<sys::spo<CGeometry>> getGeometries() {
        sys::vector<sys::spo<CGeometry>> tGeometries;
        for (auto& tNode : mNodes) for (auto& [tName,tChild] : tNode->mNodes) if (tChild->isModel()) {
          auto tModel = sys::static_pointer_cast<TNode<ENode::MODEL>>(tChild);
          tGeometries.push_back(tModel->getGeometry()); 
        } else if (tChild->isEmitter()) {
          auto tEmitter = sys::static_pointer_cast<TNode<ENode::EMITTER>>(tChild);
          // @todo: push emitter's geometry here
        }
        return tGeometries;
      }
  };
  
  class CQuery {
      friend class CScene;
      friend class COctree;
      friend class CCell;
      friend class CResult;
    public:
      using ENode = ENode;
      enum class EOrder { NONE = -1, FRONT_TO_BACK, FB = FRONT_TO_BACK, BACK_TO_FRONT, BF = BACK_TO_FRONT, };
    public:
      sys::spo<glm::frustum> mFrustum; // defaults to empty = not ued
      EOrder                 mOrder {EOrder::NONE};
      ENode                  mType  {ENode::BASIC};
      int                    mLimit {-1};
    private:
      sys::spo<CResult> mResult;
    public:
      CQuery() : mResult{new CResult} { }
      CQuery(const glm::frustum& tFrustum) : mFrustum{new glm::frustum{tFrustum}}, mResult{new CResult} { }
      ~CQuery() = default;
    public:
      inline bool                hasFrustum() const { return mFrustum != nullptr; }
      inline const glm::frustum& getFrustum() const { return *mFrustum; }
      inline EOrder              getOrder()   const { return mOrder; }
      inline ENode               getType()    const { return mType; }
      inline int                 getLimit()   const { return mLimit; }
  };
  
// @todo: class CData { enum class EType : uint { MAIN = 0, LEFT, DOWN, BACK, RIGHT, TOP, FRONT, } };
  // +-----------------------DATA
  // |  +-------DATA         |
  // |  | +---+ | +---CELL   |
  // |  | | C | | | C |      |
  // |  | +---+ | +---+      |
  // | +--------|-------DATA |
  // | || +---+ | +---+ |    |
  // | || | C | | | C | |    | 
  // | || +---+ | +---+ |    |
  // | |+-------+     D |    |
  // | +----------------+  D |
  // +-----------------------+
  
  class CCell {
      friend class CNode;
      friend class COctree;
      friend class CScene;
      friend class CQuery;
      friend class CResult;
    public:
       enum EType { LDB/*left-down-back*/=0, RDB, LTB, RTB, LDF, RDF, LTF, RTF/*right-top-front*/, ROOT=9};
    protected:
      static constexpr EType kTypes[8] { LDB/*0*/, RDB/*1*/, LTB/*2*/, RTB/*3*/, LDF/*4*/, RDF/*5*/, LTF/*6*/, RTF/*7*/ };
      static constexpr uint  kMaxDepth {128}; // max 128 cells deep  
    protected:
      uint                                        mDepth {0};
      EType                                       mType;
      glm::aabb                                   mAABB;
// @todo: glm::aabb mRelative (to the parent) = max aabb , mAbsolute = (to the nodes) = min aabb (just wrapping the nodes);
// @todo: octree space (an 1/8th) needs:
  // -> mMaxAABB // AABB from splitting (assigned on creation, from parent)
  // -> mMinAABB // AABB from elements inside it (min CONNOT be > max), like an element bounding box
      sys::wpo<CCell>                             mRoot;
      sys::array<sys::spo<CCell>,8>               mCells; // 1/8th of aabb // main, top, DOWN, front, back, left, right
      sys::vector<sys::spo<TNode<ENode::ENTITY>>> mNodes;   // data (if too big for children & too small for this.mParent
// @todo: multiple LEAVES: sys::array<sys::spo<CLeaf>,7> mLeaves; // hold data
    protected:
      /* create root-level cell, depth = 0 */
      CCell();
      /* create child cell, w/ type, calculate aabb based on type */
      CCell(sys::wpo<CCell> tRoot, EType tType);
      /* create child cell, w/ pre-calculated aabb */
      CCell(sys::wpo<CCell> tRoot, const glm::aabb& tAABB, EType tType);
    public:
      ~CCell() = default;
    public:
      friend std::ostream& operator <<(std::ostream&, const CCell&);
      friend const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel& type, const CCell& cell);
    public:
      inline bool isRoot() const { return mRoot == nullptr; /*OR mType == EType::ROOT*/ }
      inline const decltype(mNodes)& getNodes() const { return mNodes; }
      inline const glm::aabb& getAABB() const { return mAABB; }
    public:
      /* pull&return all nodes from self & all children, used when extending root's AABB */
      sys::vector<sys::spo<TNode<ENode::ENTITY>>> cull();
      /* push tNode to this cell (or its children), tForce it if already compared AABB's */
      void push(sys::spo<TNode<ENode::ENTITY>> tNode, bool tForce = false);
      /* find scene nodes using a CQuery + glm::frustum */
      sys::spo<CResult> find(const CQuery& tQuery);
  };
  
// @todo: CCellManager need something to re-use cells (so u don't keep allocating memory)
  
  // scene ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  /*TNode<ENode::SCENE>*/ class CScene : /*public TNode<ENode::BASIC>,*/ public cym::CResource {
      friend class CSceneLoader;
      friend class CSceneManager;
    protected:
      sys::spo<cym::CNode> mNode;
      sys::spo<cym::CCell> mCell;
    public:
      CScene(const sys::string& tName = "default");
      CScene(sys::spo<CSceneLoader>);
      ~CScene();
    public:
      friend std::ostream& operator <<(std::ostream&, const CScene&);
      friend const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel&, const CScene&);
    public:
      /* return the root node (never null) */
      inline sys::spo<CNode> getRoot() const { return mNode; }
    public:
      /* load using a loader */
      virtual void load(sys::spo<CSceneLoader>) final;
      /* find scene nodes using a CQuery + glm::frustum */
      sys::spo<CResult> find(const CQuery&);
      /* CScene::push(cym::TNode<ENode::MODEL>&&) // add node (of type) to scene */
      template<const ENode E> sys::spo<TNode<ENode::ENTITY>> push(TNode<E>&& rNode, const glm::xform& tXForm = glm::ZERO) {
        SYS_LOG_NFO("cym::CScene::push(cym::TNode<E>&&, glm::xform)::" << this);
        // create a node:scene
        sys::spo<TNode<E>>             tNode   {new TNode<E>{std::move(rNode)}};
        sys::spo<TNode<ENode::ENTITY>> tEntity {new TNode<ENode::ENTITY>{tNode->getName(), glm::ZERO, tXForm}};
        // attach tNode to node:scene
        tEntity->push(tNode);
        // insert node:entity at CScene:node (xml's start/root node) 
        mNode->push(tEntity);
        // insert node:entity in CScene:cell (scene's octree-like structure),
        mCell->push(tEntity);
        // return the entity node
        return tEntity;
      }
      /* CScene::push(new cym::TNode<ENode::MODEL>{IGeometry}) // add node (of type) to scene */
      template<const ENode E> sys::spo<TNode<ENode::ENTITY>> push(TNode<E>* pNode, const glm::xform& tXForm = glm::ZERO) {
        SYS_LOG_NFO("cym::CScene::push(cym::TNode<E>*, glm::xform&)::" << this);
        // create a node:scene
        sys::spo<TNode<E>>             tNode   {pNode};
        sys::spo<TNode<ENode::ENTITY>> tEntity {new TNode<ENode::ENTITY>{tNode->getName(), glm::ZERO, tXForm}};
        // attach tNode to node:scene
        tEntity->push(tNode);
        // insert node:entity at CScene:node (xml's start/root node) 
        mNode->push(tEntity);
        // insert node:entity in CScene:cell (scene's octree-like structure),
        mCell->push(tEntity);
        // return the entity node
        return tEntity;
      }
      /* CScene::push(sys::spo<cym::TNode<ENode::MODEL>>{IGeometry}) // add node (of type) to scene */
      template<const ENode E> sys::spo<TNode<ENode::ENTITY>> push(sys::spo<TNode<E>> tNode, const glm::xform& tXForm = glm::ZERO) {
        SYS_LOG_NFO("cym::CScene::push(sys::spo<cym::TNode<"<< E <<">>, glm::xform&, sys::spo<cym::TNode<E>>)::" << this);
        // create a node:scene
        sys::spo<TNode<ENode::ENTITY>> tEntity {new TNode<ENode::ENTITY>{tNode->getName(), glm::ZERO, tXForm}};
        // attach tNode to node:entity
        tEntity->push(tNode);
        // insert node:entity at CScene:node (xml's start/root node) 
        mNode->push(tEntity);
        
// @todo: what if tNode aabb is 0 ?, what will ->push(tNode) + expand(tNode->mAABB) do/?!
  // or, the camera's (entity) aabb/extent is determined by position + target?! // if camera moves => cell tree => dirty
  // or, by the frustum?!                                              // (same)
  // or, keep it 0 and insert it into first CCell
  // or, keep it 0 and insert it into tEntity's parent cell (if entity at root level, leave it there)
        
        // insert node:entity in CScene:cell (scene's octree-like structure),
        mCell->push(tEntity);
        // return the entity node
        return tEntity;
      }
      /* add model to scene through a node, return the node:scene owner */
      sys::spo<TNode<ENode::ENTITY>> push(sys::spo<CGeometry>, const glm::xform& = glm::ZERO);
  };
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CSceneLoader : public CResourceLoader {
      friend class CScene;
      friend class CSceneManager;
    public:
      using CResourceLoader::CResourceLoader;
      inline CSceneLoader(const sys::string& tName) : CResourceLoader(tName) { SYS_LOG_NFO("cym::CSceneLoader::CSceneLoader(sys::string&)::" << this);  }
      inline ~CSceneLoader() { SYS_LOG_NFO("cym::CSceneLoader::~CSceneLoader()::" << this); }
    public:
      virtual inline void load(sys::spo<CResourceLoader>) { throw sys::exception("CSceneLoader::load() NOT overriden!",__FILE__,__LINE__);  };
    public:
      template<typename T> inline static sys::spo<TSceneLoader<T>> from(const T& tSource) { return new TSceneLoader<T>{tSource}; }
      template<typename T, typename... Args> inline static sys::string name(const T& tSource, Args&&... args) { return TSceneLoader<T>::name(tSource, std::forward<Args>(args)...); }
  };
  
  template<typename T> class TSceneLoader : public CSceneLoader { 
    public:
    //virtual inline T& getSource();
  };
  
  template<> class TSceneLoader<sys::file> : public CSceneLoader {
      friend class CGeometryCodec;
    protected:
      sys::CFile mFile;
    public:
      inline TSceneLoader(const sys::file& tFile) : CSceneLoader(tFile.path()), mFile{tFile} { };
    public:
      inline static sys::string name(const sys::file& tFile) { return tFile.path(); }
      virtual void load(sys::spo<CResourceLoader>) override;
    public:
      inline sys::file& getFile() { return mFile; }
  };
  
  // managers ////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CSceneManager : public cym::TResourceManager<CScene>, public sys::TSingleton<CSceneManager> {
      friend class CScene;
      friend class CSceneLoader;
    protected:
      sys::map<sys::string,sys::spo<CScene>> mScenes;
    public:
      CSceneManager();
      ~CSceneManager();
    public:
      /*  */
      static void save(sys::spo<CScene> pScene) {
        static auto pThis {cym::CSceneManager::getSingleton()};
        SYS_LOG_NFO("cym::CSceneManager::save(sys::spo<CScene>)::" << pThis);
        pThis->mScenes.insert(std::pair(pScene->mName, pScene));
      }
      /*  */
      static sys::spo<CScene> load(sys::spo<CSceneLoader> pSceneLoader) {
        static auto self {cym::CGeometryManager::getSingleton()};
        SYS_LOG_NFO("cym::CSceneManager::load(sys::spo<CSceneLoader>)::" << self);
        
        if (!pSceneLoader) return nullptr;
        
        sys::spo<CScene> pScene {new CScene{pSceneLoader->getName()}};
        
        sys::async([pScene, pSceneLoader](){
          
          // loads using codes or other TSceneLoader::load() 
          pSceneLoader->load(pSceneLoader);
          
          // process additional stuff (sub loaders)
// @todo: something here?! (ex: for CGeometry sub-meshes are loaded)
          
          // finaly load everyting into pScene
          pScene->load(pSceneLoader);
          
        }, sys::EAsync::SPAWN);
        
        CSceneManager::save(pScene);
        
        return pScene;
      }
      /*  */
      static sys::spo<CScene> load(const char* tName) {
        return CSceneManager::load(std::string{tName});
      }
      /*  */
      static sys::spo<CScene> load(const sys::string& tName) {
        static auto self {cym::CSceneManager::getSingleton()};
        SYS_LOG_NFO("cym::CSceneManager::load(sys::string&)::" << self);
        sys::spo<CScene> pScene;
        // 
        if (!sys::find(tName, self->mScenes, pScene)) {
          pScene = new CScene;
          CSceneManager::save(pScene);
        }
        // 
        return pScene;
      }
      /*  */
      template<typename T, typename... Args> static sys::spo<CScene> load(const T& tSource, Args&&... args) {
        static auto self {cym::CSceneManager::getSingleton()};
        SYS_LOG_NFO("cym::CSceneManager::load(T&,Args&&)::" << self);
        
        sys::spo<CScene> pScene {new CScene};
        
// @todo: move to CSceneManager::load(pSceneLoader)
        CSceneManager::save(pScene);
        
// @todo: pScene = CSceneManager::load(tLoader);
        
        
      // @todo: loadScene ///////////////////////////////////////////////
        // for each element:node (root) in element:node.children
          // child = loadNode(element)
          // scene->root->nodes += child // & update scene->root->aabb
        
      // @todo: loadNode(element) ////////////////////////////////////////
        // parent = new CNode(type)
        // if type = scene // load unit
          // unit = loadUnit()
          // parent->unit = unit
              
          // for each element:node (root) in element:node.children
            // root = new CNode(root) // current root
            // for each element:node (joint|node|scene) in element:root 
              // child = loadNode(element)
              // root->nodes += child // & update root->aabb
            // parent->nodes += root // & update parent->aabb
            
          // @todo: add/push to octree->root using parent->aabb
            

                        
            
              
              
        // if type = joint // link joint
          // parent->link = findJoint()
          
          // for each element:node (joint|basic|scene) in element:joint 
            // child = loadNode(element)
            // parent->nodes += child // & update parent->aabb
          
        // else (basic)
          // for each element:node (joint|basic|scene) in element:joint 
            // child = loadNode(element)
            // parent->nodes += child // & update parent->aabb
              
      // @todo: loadUnit() /////////////////////////////////////////////////
        // unit = new CUnit
        // for each element:entity in element:unit
          // entity = loadEntity()
          // unit->entities += enitity
          
      // @todo: loadEntity() //////////////////////////////////////////////
        // entity = new CEntity(model)
        // model = CGeometryLoader::load(element:model->file)
        // entity->model = model
        // entity->aabb = model->aabb
        // for each mesh in geometry
          // material = CMaterialManager::load(element:material->file)
            // for each channel in material
              // case DIFFUSE:
                // texture = CTextureManager::load(element:texture->file)
                // material->channels[DIFFUSE]->texture = texture
              // case AMBIENT:
                // ...
          // mesh->material = material
          
      
        
        
        
        
        
        return pScene;
      }
  };
  
  class CNodeManager: public cym::TResourceManager<CNode> {
    protected:
      sys::vector<sys::spo<CNode>> mNodes;
    public:
      CNodeManager();
      ~CNodeManager();
    public:
  };
}

#endif //__cym_cscene_hpp__
