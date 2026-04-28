#ifndef udUtil_h__
#define udUtil_h__

//! @file udUtil.h
//! Helper functions for diverse use cases

#include "udError.h"

#ifdef __cplusplus
extern "C" {
#endif

  //!
  //! Extract Images from an e57 file
  //!
  //! @param pFileName The e57 filename
  //! @param pFolderName The folder to extract the images into
  //! @param ppMetaData Optional char* filled withmetadata from exported images (paths, position, rotation, shape) as JSON
  //! @return A udError value based on the result of the extraction
  //!
  UDSDKDLL_API enum udError udUtil_E57ExtractImages(const char *pFileName, const char *pFolderName, const char **ppMetaData);

#ifdef __cplusplus
}
#endif

#endif // udUtil_h__
