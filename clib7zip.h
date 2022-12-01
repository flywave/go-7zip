#pragma once

#include "PropID.h"

#if !__cplusplus
typedef int bool;
#define false 0
#define true 1
#endif
#include <wchar.h>

#ifndef _WIN32

#define __int64 long long int
#endif

#define c7zip_EXPORT

/**
 * Items that return bool, true == success, false== failure
 * Items that return int (as opposed to unsigned int, or __int64), 0 == success,
 * non-zero == failure
 */

typedef enum {
  ErrorCode_Begin,

  NO_ERROR = ErrorCode_Begin,
  UNKNOWN_ERROR,
  NOT_INITIALIZE,
  NEED_PASSWORD,
  NOT_SUPPORTED_ARCHIVE,

  ErrorCode_End
} ErrorCodeEnum;

// Types
typedef void c7z_Object;
typedef void c7z_ObjPtrArr; // Object Pointer Array, aka a list of
                            // c7z_Objects/C7ZipObjects
typedef void c7z_ArchiveItem;
typedef void c7z_InStream;
typedef void c7z_MultiVolume;
typedef void c7z_OutStream;
typedef void c7z_Archive;
typedef void c7z_Library;

// Object

// ArchiveItem
c7zip_EXPORT void free_C7ZipArchiveItem(c7z_ArchiveItem *self);

c7zip_EXPORT const wchar_t *c7zItm_GetFullPath(c7z_ArchiveItem *self);
c7zip_EXPORT unsigned __int64 c7zItm_GetSize(c7z_ArchiveItem *self);
c7zip_EXPORT bool c7zItm_IsDir(c7z_ArchiveItem *self);
c7zip_EXPORT bool c7zItm_IsEncrypted(c7z_ArchiveItem *self);
c7zip_EXPORT unsigned int c7zItm_GetArchiveIndex(c7z_ArchiveItem *self);
c7zip_EXPORT bool c7zItm_GetUInt64Property(c7z_ArchiveItem *self,
                                           int propertyIndex,
                                           unsigned __int64 *val);
c7zip_EXPORT bool c7zItm_GetFileTimeProperty(c7z_ArchiveItem *self,
                                             int propertyIndex,
                                             unsigned __int64 *val);
c7zip_EXPORT bool c7zItm_GetStringProperty(c7z_ArchiveItem *self,
                                           int propertyIndex, wchar_t **val);
c7zip_EXPORT bool c7zItm_GetBoolProperty(c7z_ArchiveItem *self,
                                         int propertyIndex, bool *val);

// InStream
c7zip_EXPORT c7z_InStream *create_c7zInSt_Filename(const char *filename);
c7zip_EXPORT void free_C7ZipInStream(c7z_InStream *stream);
c7zip_EXPORT const wchar_t *c7zInSt_GetExt(c7z_InStream *self);

c7zip_EXPORT int c7zInSt_Read(c7z_InStream *self, void *data, unsigned int size,
                              unsigned int *processedSize);
c7zip_EXPORT int c7zInSt_Seek(c7z_InStream *self, __int64 offset,
                              unsigned int seekOrigin,
                              unsigned __int64 *newPosition);
c7zip_EXPORT int c7zInSt_GetSize(c7z_InStream *self, unsigned __int64 *size);

// OutStream
c7zip_EXPORT int c7zOutSt_Write(c7z_OutStream *self, const void *data,
                                unsigned int size, unsigned int *processedSize);
c7zip_EXPORT int c7zOutSt_Seek(c7z_OutStream *self, __int64 offset,
                               unsigned int seekOrigin,
                               unsigned __int64 *newPosition);
c7zip_EXPORT int c7zOutSt_SetSize(c7z_OutStream *self, unsigned __int64 size);

// Archive
c7zip_EXPORT void free_C7ZipArchive(c7z_Archive *self);

c7zip_EXPORT bool c7zArc_GetItemCount(c7z_Archive *self,
                                      unsigned int *pNumItems);

c7zip_EXPORT bool c7zArc_GetItemInfo(c7z_Archive *self, unsigned int index,
                                     c7z_ArchiveItem **ppArchiveItem);
c7zip_EXPORT bool c7zArc_ExtractByIndex(c7z_Archive *self, unsigned int index,
                                        c7z_OutStream *pOutStream);
c7zip_EXPORT bool c7zArc_ExtractByIndexPW(c7z_Archive *self, unsigned int index,
                                          c7z_OutStream *pOutStream,
                                          const wchar_t *password);
c7zip_EXPORT bool c7zArc_ExtractByItem(c7z_Archive *self,
                                       const c7z_ArchiveItem *pArchiveItem,
                                       c7z_OutStream *pOutStream);

c7zip_EXPORT void c7zArc_Close(c7z_Archive *self); // frees the pointer

c7zip_EXPORT bool c7zArc_GetUInt64Property(c7z_Archive *self, int propertyIndex,
                                           unsigned __int64 *const val);
c7zip_EXPORT bool c7zArc_GetBoolProperty(c7z_Archive *self, int propertyIndex,
                                         bool *const val);
c7zip_EXPORT bool c7zArc_GetStringProperty(c7z_Archive *self, int propertyIndex,
                                           wchar_t **val);
c7zip_EXPORT bool c7zArc_GetFileTimeProperty(c7z_Archive *self,
                                             int propertyIndex,
                                             unsigned __int64 *const val);

// Library
c7zip_EXPORT c7z_Library *create_C7ZipLibrary();
c7zip_EXPORT void free_C7ZipLibrary(c7z_Library *self);
c7zip_EXPORT bool c7zLib_Initialize(c7z_Library *self);
c7zip_EXPORT void c7zLib_Deinitialize(c7z_Library *self);
c7zip_EXPORT bool c7zLib_GetSupportedExts(c7z_Library *self,
                                          const wchar_t ***exts, size_t *size);
c7zip_EXPORT void free_extarr(const wchar_t **exts);
c7zip_EXPORT bool c7zLib_OpenArchive(c7z_Library *self, c7z_InStream *pInStream,
                                     c7z_Archive **ppArchive);
c7zip_EXPORT bool c7zLib_IsInitialized(c7z_Library *self);
c7zip_EXPORT ErrorCodeEnum c7zLib_GetLastError(c7z_Library *self);
