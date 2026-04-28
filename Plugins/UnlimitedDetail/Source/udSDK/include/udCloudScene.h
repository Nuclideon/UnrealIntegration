#ifndef udCloudScene_h__
#define udCloudScene_h__

//! @file udCloudScene.h
//! The udCloudScene object provide an interface for accessing data of Scenes hosted in udCloud

#include <stdint.h>

//!
//! @struct udCloudScene
//! This represents a udCloud Scene
//! 
struct udCloudScene
{
  char *pName; //!< The name of the Scene
  char ID[64]; //!< The sceneid from udCloud
  char orgID[64]; //!< The workspace it belongs to from udCloud
  char projID[64]; //!< The project it belongs to from udCloud
  double created; //!< The time this scene was created
  double lastUpdated; //!< The time this scene was last updated
  double deletedTime; //!< The time this scene was deleted
  uint32_t isShared; //!< Is the scene shared
};

#endif //udCloudScene_h__
