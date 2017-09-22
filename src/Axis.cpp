#include "Axis.h"
#include "ngl/Material.h"
#include "ngl/Camera.h"
#include <QDebug>

//----------------------------------------------------------------------------------------------------------------------
Axis::Axis(std::string _shaderName, ngl::Real _scale )
{
  m_shaderName=_shaderName;
  m_scale=_scale;

  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
  prim->createCylinder("nglAXISCylinder",0.02f,2,60,60);
  prim->createCone("nglAXISCone",0.05f,0.2f,30,30);
}

void Axis::loadMatricesToShader()
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat4 M;
  M=m_globalMouseTx*m_transform.getMatrix();
  MV=  m_cam->getViewMatrix()*M;
  MVP= m_cam->getProjectionMatrix()*MV;
 // MVP= m_transform.getMatrix() * m_cam->getVPMatrix();
  shader->setUniform("MVP",MVP);
}

//----------------------------------------------------------------------------------------------------------------------
void Axis::draw(const ngl::Mat4 &_globalTx )
{
  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
  // grab an instance of the shader manager
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  m_globalMouseTx=_globalTx;
  (*shader)[m_shaderName]->use();
  // Rotation based on the mouse position for our global
  // transform

  shader->setUniform("Colour",1.0f,0.0f,0.0f,1.0f);
  m_transform.setScale(m_scale,m_scale,m_scale*2);
  m_transform.setPosition(ngl::Vec3(m_scale,0,0));
  m_transform.setRotation(0,90,0);
  loadMatricesToShader();
  prim->draw("nglAXISCylinder");

  m_transform.setPosition(ngl::Vec3(m_scale,0,0));
  m_transform.setRotation(0,90,0);
  loadMatricesToShader();
  prim->draw("nglAXISCone");
  m_transform.setPosition(ngl::Vec3(-m_scale,0,0));
  m_transform.setRotation(0,-90,0);
  loadMatricesToShader();
  prim->draw("nglAXISCone");

  // y axis
   shader->setUniform("Colour",0.0f,1.0f,0.0f,1.0f);
   m_transform.setScale(m_scale,m_scale,m_scale*2);
   m_transform.setPosition(ngl::Vec3(0,-m_scale,0));
   m_transform.setRotation(90,0,0);
   loadMatricesToShader();
   prim->draw("nglAXISCylinder");

   m_transform.setPosition(ngl::Vec3(0,m_scale,0));
   m_transform.setRotation(-90,0,0);
   loadMatricesToShader();
   prim->draw("nglAXISCone");
   m_transform.setPosition(ngl::Vec3(0,-m_scale,0));
   m_transform.setRotation(90,0,0);
   loadMatricesToShader();
   prim->draw("nglAXISCone");

//     // z axis
   shader->setUniform("Colour",0.0f,0.0f,1.0f,1.0f);
   m_transform.setScale(m_scale,m_scale,m_scale*2);
   m_transform.setPosition(ngl::Vec3(0,0,m_scale));
   m_transform.setRotation(0,0,-90);
   loadMatricesToShader();
   prim->draw("nglAXISCylinder");

   m_transform.setPosition(ngl::Vec3(0,0,m_scale));
   loadMatricesToShader();
   prim->draw("nglAXISCone");
   m_transform.setPosition(ngl::Vec3(0,0,-m_scale));
   m_transform.setRotation(180,0,0);
   loadMatricesToShader();
   prim->draw("nglAXISCone");

}
//----------------------------------------------------------------------------------------------------------------------
