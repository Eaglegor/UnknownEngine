#pragma once

#include <InlineSpecification.h>
#include <Vectors/Vector3.h>
#include <OgreVector3.h>

namespace UnknownEngine
{
 namespace Graphics
 {
   class OgreVector3Converter
   {
   public:
     static Ogre::Vector3 toOgreVector(const Math::Vector3& vector)
     {
       return Ogre::Vector3(vector.x(), vector.y(), vector.z());
     }
     static Math::Vector3 fromOgreVector(const Ogre::Vector3& vector)
     {
       return Math::Vector3(vector.x, vector.y, vector.z);
     }
   };
 }
}