#ifndef udBlockRenderContext_h__
#define udBlockRenderContext_h__

//! @file udBlockRenderContext.h
//! The **udBlockRenderContext** object provides an interface to render Nuclideon Unlimited Detail models, with callbacks to enable GPU renderering.
//! It provides the ability to render by colour, intensity or classification; additionally allowing the user to query a specific pixel for information about the pointcloud data.

#include "udDLLExport.h"
#include "udError.h"
#include "udMath.h"
#include "udPointBuffer.h"
#include "udRenderContext.h"

#ifdef __cplusplus
extern "C" {
#endif

  struct udRenderContext;
  struct udRenderView;
  struct udRenderTarget;
  struct udRenderInstance;
  struct udRenderSettings;

  //!
  //! @struct udBlockRenderDrawList
  //! Passed by the block renderer to the implementation to define what parts of the block need to be rendered
  //!
  struct udBlockRenderDrawList
  {
    uint32_t crc;                 //!< A crc representing inputs to the drawlist (eg listMask or geometry), allowing callers to cache if necessary
    uint16_t listMask;            //!< When non-zero, the divisions the mask used to create the drawlist (with adjacent divisions merged), zero indicates non-merged/filtered list
    uint16_t drawCount;           //!< Number of drawcalls to complete this block

    //!
    //! @struct DrawCall
    //! Stores the internal state of the draw call
    //! 
    struct DrawCall
    {
      uint16_t start;             //!< Starting index in the vertex buffer
      uint16_t count;             //!< Number of points for this call
      uint16_t mask;              //!< Mask of division this call is relevant to (bitwise and with supplied divisionMask to determine draw/skip)
    } draws[1];
#ifdef __cplusplus
    static uint32_t GetSize(int _drawCount) { return (uint32_t)(sizeof(udBlockRenderDrawList) + ((_drawCount - 1) * sizeof(draws[0]))); }
#endif
  };

  //!
  //! @struct udBlockRenderVertexData
  //! Stores the vertex data needed to render a block
  //!
  struct udBlockRenderVertexData
  {
    void *pBlock;                               //!< Pointer to internal block memory
    const struct udPointBufferU64 *pPointBuffer;//!< Pointer to points data
    double unitOctreeMultiplier;                //!< Multiplier to take from integer octee space to 0..1 octree space
    double nodeSize;                            //!< Generally the w component for the size of the node (1.0 == root, 0.5 = level 1, 0.25, etc)
    double childSize;                           //!< nodeSize * 0.5 Currently legacy, with intent to switch everything to nodeSize
    udDouble4x4 modelToBlock;                   //!< Matrix to take a block from model space, to block space
    double distEye;                             //!< Distance of this block to the camera (in eye space)
  };

  //!
  //! @struct udBlockRenderModel
  //! Exposes data required to render a model
  //!
  struct udBlockRenderModel
  {
    struct udRenderModel *pRenderModel;     //!< Pointer to internal model

    udDouble4x4 world;           //!< World Matrix
    udDouble4x4 worldView;       //!< World-View Matrix
    udDouble4x4 projection;      //!< Projection Matrix
    udDouble4x4 wvps;            //!< World-View-Projection-Screen Matrix

    udDouble4 frustumPlanes[6];  //!< Cached view frustum planes
    udDouble3 eyePosMS;          //!< Position of the eye in model space
    udDouble3 cameraForward;     //!< Forward vector of the camera in model space
    udDouble3 cameraFacingDiag;  //!< Vector that when transformed will be a diagonal line in screen space
  };

  //!
  //! @struct udBlockRenderInfo
  //! Structure to hold rendering info for a single drawcall
  //!
  struct udBlockRenderInfo
  {
    struct udBlockRenderDrawList *pDrawList;  //!< The draw list defining which points of the block are to be rendered
    double blockPriority;                     //!< The priority of the block
    enum udRenderContextPointMode pointMode;  //!< points/rectangles/cubes
    uint16_t divisionsMask;                   //!< divisions mask, identifying which portions of the block are to be rendered
  };

  //!
  //! @struct udBlockRenderGPUInterface
  //! Structure that stores user-defined rendering callbacks (optional and required)
  //!
  struct udBlockRenderGPUInterface
  {
    void (*pBeginRender)(void *pGPUContext, const struct udRenderView *pView, uint32_t width, uint32_t height); //!< Called when rendering begins
    void (*pEndRender)(void *pGPUContext); //!< Called when rendering ends

    enum udError(*pCreateVertexBuffer)(void *pGPUContext, const struct udBlockRenderModel *pModel, const struct udBlockRenderVertexData vertexData, void **ppVertexBuffer); //!< Called when vertex buffer is ready to be created
    enum udError(*pUploadVertexBuffer)(void *pGPUContext, const struct udBlockRenderModel *pModel, void *pVertexBuffer, void *pVoxelShaderData);  //!< Called when vertex buffer is ready to upload to GPU
    enum udError(*pRenderVertexBuffer)(void *pGPUContext, const struct udBlockRenderModel *pModel, void *pVertexBuffer, void *pVoxelShaderData, const struct udBlockRenderInfo *pInfo);  //!< Called when vertex buffer is to be rendered
    enum udError(*pDestroyVertexBuffer)(void *pGPUContext, void *pVertexBuffer);  //!< Called when vertex buffer is to be destroyed

    void *pGPUContext; //!< Internal pointer to user-defined storage
  };

  //!
  //! Retrieves a voxel position in model space.
  //!
  //! @param pData The block vertex data to query.
  //! @param index The voxel index.
  //! @return The voxel position in model space
  //!
  UDSDKDLL_API udDouble3 udBlockRenderVertexData_GetFloatPosition(const struct udBlockRenderVertexData *pData, uint32_t index);

  //!
  //! Create an instance of `udBlockRenderContext` for rendering.
  //!
  //! @param pGPUInterface The pointer of the user-defined callbacks interface.
  //! @return A udError value based on the result of the render context creation.
  //!
  UDSDKDLL_API enum udError udBlockRenderContext_Init(struct udBlockRenderGPUInterface *pGPUInterface);

  //!
 //! Destroy the instance of the renderer.
 //!
 //! @param ppRenderer The pointer pointer of the udRenderContext. This will deallocate the instance of udRenderContext.
 //! @return A udError value based on the result of the render context destruction.
 //!
  UDSDKDLL_API enum udError udBlockRenderContext_Deinit();

  //!
  //! Render the models from the perspective of `pRenderView`.
  //!
  //! @param pRenderer The renderer to render the scene.
  //! @param pRenderView The view to render from with the render buffers associated with it being filled out.
  //! @param pModels The array of models to use in render.
  //! @param modelCount The amount of models in pModels.
  //! @param pRenderOptions Additional render options.
  //! @return A udError value based on the result of the render.
  //!
  UDSDKDLL_API enum udError udBlockRenderContext_Render(struct udRenderContext *pRenderer, struct udRenderTarget *pRenderView, struct udRenderInstance *pModels, int modelCount, struct udRenderSettings *pRenderOptions);

  //!
  //! Get the unique user-defined id of the supplied model.
  //!
  //! @param pBlockRenderModel The model whose id will be returned
  //! @return The unique id of the model.
  //!
  UDSDKDLL_API uint32_t udRenderContext_GetModelId(const struct udBlockRenderModel *pBlockRenderModel);

  //!
  //! Get the voxel shader function pointer
  //!
  //! @param pBlockRenderModel The model whose voxel shader function will be returned
  //! @return The voxel shader function of the model.
  //!
  UDSDKDLL_API uint32_t udRenderContext_GetVoxelShader(const struct udBlockRenderModel *pBlockRenderModel);

  //!
  //! Locks an Unlimited Detail block, preventing it from being freed by the streamer.
  //!
  //! @param pBlock A pointer to an internal Unlimited Detail block.
  //! @return A udError value indicating the result of the lock update.
  //!
  UDSDKDLL_API enum udError udRenderContext_LockBlock(void *pBlock);

  //!
  //! Unlocks an Unlimited Detail block, allowing the streamer to free it.
  //!
  //! @param pBlock A pointer to an internal Unlimited Detail block.
  //! @return A udError value indicating the result of the lock update.
  //!
  UDSDKDLL_API enum udError udRenderContext_UnlockBlock(void *pBlock);

#ifdef __cplusplus
}
#endif

#endif // udBlockRenderContext_h__
