#ifndef PARSER_H
#define PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../error_enums.h"
#include "../mesh_data.h"

ModelLoadingError parseObjFile(const char *filename, MeshData *data);

#ifdef __cplusplus
}
#endif

#endif
