#ifndef Resource_HPP
#define Resource_HPP

#include "../../common.h"

namespace engine {

/**
 * Encapsulates asset I/O.
 */
class Resource {

public:

	Resource(AAssetManager* assetManager, const char* path);

	virtual ~Resource();

	virtual int32_t read(void* buffer, size_t count);

private:

	AAsset* _asset;
};

}

#endif
