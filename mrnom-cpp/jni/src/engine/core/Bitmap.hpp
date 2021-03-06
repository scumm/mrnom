#ifndef BITMAP_HPP
#define BITMAP_HPP

#include "../../common.h"

namespace engine {

/**
 * Picture data container.
 */
class Bitmap {

public:

	Bitmap(int32_t  width, int32_t  height,
	       int32_t  format, uint8_t* pixels);

	virtual ~Bitmap();

	/**
	 * Horizontal length.
	 */
	int32_t getWidth() const;

	/**
	 * Vertical length.
	 */
	int32_t getHeight() const;

	/**
	 * Pixel format.
	 */
	int32_t getFormat() const;

	/**
	 * Pixel data (byte array).
	 */
	uint8_t* getPixels() const;

private:

	int32_t _width;
	int32_t _height;
	int32_t _format;

	// owned pointer
	uint8_t* _pixels;
};

}

#endif
