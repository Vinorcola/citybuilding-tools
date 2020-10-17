#include "sgimage.h"

#include <QtCore/QFile>
#include <QtCore/QDataStream>

#include "display/BinaryFormatter.hpp"

enum {
	ISOMETRIC_TILE_WIDTH = 58,
	ISOMETRIC_TILE_HEIGHT = 30,
	ISOMETRIC_TILE_BYTES = 1800,
	ISOMETRIC_LARGE_TILE_WIDTH = 78,
	ISOMETRIC_LARGE_TILE_HEIGHT = 40,
	ISOMETRIC_LARGE_TILE_BYTES = 3200
};

class SgImageRecord {
public:
	SgImageRecord(QDataStream *stream, bool includeAlpha) {
		*stream >> offset;
		*stream >> length;
		*stream >> uncompressed_length;
        *stream >> __unknown_a;
		*stream >> invert_offset;
		*stream >> width;
		*stream >> height;
        *stream >> __unknown_b;
        *stream >> __unknown_c;
        *stream >> __unknown_d;
        *stream >> __unknown_e;
        *stream >> __unknown_f;
        *stream >> position_offset_x;
        *stream >> position_offset_y;
        *stream >> __unknown_i;
        *stream >> __unknown_j;
        *stream >> __unknown_k;
        *stream >> __unknown_l;
		*stream >> type;
		stream->readRawData(flags, 4);
        *stream >> bitmap_id;
        *stream >> __unknown_m;
        *stream >> __unknown_n;
        *stream >> __unknown_o;
        *stream >> __unknown_p;
		
		if (includeAlpha) {
			*stream >> alpha_offset;
			*stream >> alpha_length;
		} else {
			alpha_offset = alpha_length = 0;
		}
	}
	
	quint32 offset;
	quint32 length;
	quint32 uncompressed_length;
    quint32 __unknown_a; // 4 zero bytes
	qint32 invert_offset;
	qint16 width;
	qint16 height;
    qint16 __unknown_b; // Unknown short
    qint16 __unknown_c; // Unknown short
    quint16 __unknown_d;// 22 unknown bytes, mostly zero
    quint16 __unknown_e;
    quint16 __unknown_f;
    qint16 position_offset_x;
    qint16 position_offset_y;
    quint16 __unknown_i;
    quint32 __unknown_j;
    quint32 __unknown_k;
    quint16 __unknown_l;
    quint16 type;
    char flags[4]; // 4 flag/option-like bytes
    quint8 bitmap_id;
    quint8 __unknown_m;// 3 bytes
    quint8 __unknown_n;
    quint8 __unknown_o;
    quint32 __unknown_p; // 4 zero bytes
	/* For D6 and up SG3 versions: alpha masks */
	quint32 alpha_offset;
	quint32 alpha_length;
};

SgImage::SgImage(int id, QDataStream *stream, bool includeAlpha)
	: parent(NULL)
{
	imageId = id;
	record = workRecord = new SgImageRecord(stream, includeAlpha);
	if (record->invert_offset) {
		invert = true;
	} else {
		invert = false;
	}
}

SgImage::~SgImage() {
	if (record) delete record;
	// workRecord is deleted by whoever owns it
}

qint32 SgImage::invertOffset() const {
	return record->invert_offset;
}

int SgImage::bitmapId() const {
	if (workRecord) return workRecord->bitmap_id;
	return record->bitmap_id;
}

QString SgImage::description() const {
	return QString("%0x%1")
		.arg(workRecord->width)
		.arg(workRecord->height);
}

QString SgImage::fullDescription() const {
	return QString("ID %7: offset %0, length %1, width %2, height %3, type %5, %6")
		.arg(workRecord->offset)
		.arg(workRecord->length)
		.arg(workRecord->width)
		.arg(workRecord->height)
		.arg(workRecord->type)
		.arg(workRecord->flags[0] ? "external" : "internal")
        .arg(imageId);
}

QString SgImage::binaryDescription() const
{
    QString content;
    content += BinaryFormatter::format("offset", workRecord->offset) + "\n";
    content += BinaryFormatter::format("length", workRecord->length) + "\n";
    content += BinaryFormatter::format("uncompressed_length", workRecord->uncompressed_length) + "\n";
    content += BinaryFormatter::format("__unknown_a", workRecord->__unknown_a) + "\n";
    content += BinaryFormatter::format("invert_offset", workRecord->invert_offset) + "\n";
    content += BinaryFormatter::format("width", workRecord->width) + "\n";
    content += BinaryFormatter::format("height", workRecord->height) + "\n";
    content += BinaryFormatter::format("__unknown_b", workRecord->__unknown_b) + "\n";
    content += BinaryFormatter::format("__unknown_c", workRecord->__unknown_c) + "\n";
    content += BinaryFormatter::format("__unknown_d", workRecord->__unknown_d) + "\n";
    content += BinaryFormatter::format("__unknown_e", workRecord->__unknown_e) + "\n";
    content += BinaryFormatter::format("__unknown_f", workRecord->__unknown_f) + "\n";
    content += BinaryFormatter::format("position_offset_x", workRecord->position_offset_x) + "\n";
    content += BinaryFormatter::format("position_offset_y", workRecord->position_offset_y) + "\n";
    content += BinaryFormatter::format("__unknown_i", workRecord->__unknown_i) + "\n";
    content += BinaryFormatter::format("__unknown_j", workRecord->__unknown_j) + "\n";
    content += BinaryFormatter::format("__unknown_k", workRecord->__unknown_k) + "\n";
    content += BinaryFormatter::format("__unknown_l", workRecord->__unknown_l) + "\n";
    content += BinaryFormatter::format("type", workRecord->type) + "\n";
    content += BinaryFormatter::format("flag 1", workRecord->flags[0]) + "\n";
    content += BinaryFormatter::format("flag 2", workRecord->flags[1]) + "\n";
    content += BinaryFormatter::format("flag 3", workRecord->flags[2]) + "\n";
    content += BinaryFormatter::format("flag 4", workRecord->flags[3]) + "\n";
    content += BinaryFormatter::format("bitmap_id", workRecord->bitmap_id) + "\n";
    content += BinaryFormatter::format("__unknown_m", workRecord->__unknown_m) + "\n";
    content += BinaryFormatter::format("__unknown_n", workRecord->__unknown_n) + "\n";
    content += BinaryFormatter::format("__unknown_o", workRecord->__unknown_o) + "\n";
    content += BinaryFormatter::format("__unknown_p", workRecord->__unknown_p) + "\n";
    content += BinaryFormatter::format("alpha_offset", workRecord->alpha_offset) + "\n";
    content += BinaryFormatter::format("alpha_length", workRecord->alpha_length) + "\n";

    return content;
}

void SgImage::setInvertImage(SgImage *invert) {
	this->workRecord = invert->record;
}

void SgImage::setParent(SgBitmap *parent) {
	this->parent = parent;
}

QString SgImage::errorMessage() const {
    return error;
}

void SgImage::setError(const QString &message) {
    qDebug(message.toLatin1().constData());
	error = message;
}

QImage SgImage::getImage() {
	// START DEBUG ((
	/*
	if ((imageId >= 359 && imageId <= 368) || imageId == 459) {
		qDebug("Record %d", imageId);
		qDebug("  offet %d; length %d; length2 %d", record->offset, record->length, record->uncompressed_length);
		qDebug("  invert %d; width %d; height %d", record->invert_offset, record->width, record->height);
		qDebug("  type %d; flags %d %d %d %d; bitmap %d", record->type,
			record->flags[0], record->flags[1], record->flags[2], record->flags[3], record->bitmap_id);
	}
	*/
	// END DEBUG ))
	// Trivial checks
	if (!parent) {
		setError("Image has no bitmap parent");
		return QImage();
	}
	if (workRecord->width <= 0 || workRecord->height <= 0) {
		setError(QString("Width or height invalid (%0 x %1)")
			.arg(workRecord->width).arg(workRecord->height));
		return QImage();
	} else if (workRecord->length <= 0) {
		setError("No image data available");
		return QImage();
	}
	
	quint8 *buffer = fillBuffer();
	if (buffer == NULL) {
		qDebug("Unable to load buffer"); // error already set in fillBuffer()
		return QImage();
	}
	
	QImage result(workRecord->width, workRecord->height, QImage::Format_ARGB32);
	result.fill(0); // Transparent black
	
	switch (workRecord->type) {
		case 0:
		case 1:
		case 10:
		case 12:
		case 13:
			loadPlainImage(&result, buffer);
			break;
		
		case 30:
			loadIsometricImage(&result, buffer);
			break;
		
		case 256:
		case 257:
		case 276:
			loadSpriteImage(&result, buffer);
			break;
		
		default:
			qWarning("Unknown image type: %d", workRecord->type);
			break;
	}
	
	if (workRecord->alpha_length) {
		quint8 *alpha_buffer = &(buffer[workRecord->length]);
		loadAlphaMask(&result, alpha_buffer);
	}
	
	delete[] buffer;
	
	if (invert) {
		return result.mirrored(true, false);
	}
    return result;
}

QPoint SgImage::getPositionOffset() const
{
    return { workRecord->__unknown_h, workRecord->__unknown_g };
}

quint8* SgImage::fillBuffer() {
	QFile *file = parent->openFile(workRecord->flags[0]);
	if (file == NULL) {
		setError("Unable to open 555 file");
		return NULL;
	}
	
	int data_length = workRecord->length + workRecord->alpha_length;
	if (data_length <= 0) {
		qDebug("Data length: %d", data_length); // not an error per se
	}
	char *buffer = new char[data_length];
	if (buffer == NULL) {
		setError(QString("Cannot allocate %0 bytes of memory").arg(data_length));
		return NULL;
	}
	
	// Somehow externals have 1 byte added to their offset
	file->seek(workRecord->offset - workRecord->flags[0]);
	
	int data_read = (int)file->read(buffer, data_length);
	if (data_length != data_read) {
		if (data_read + 4 == data_length && file->atEnd()) {
			// Exception for some C3 graphics: last image is 'missing' 4 bytes
			buffer[data_read] = buffer[data_read+1] = 0;
			buffer[data_read+2] = buffer[data_read+3] = 0;
		} else {
			setError(QString("Unable to read %0 bytes from file (read %1 bytes)")
				.arg(data_length).arg(data_read));
			delete[] buffer;
			return NULL;
		}
	}
	return (quint8*) buffer;
}

void SgImage::loadPlainImage(QImage *img, quint8 *buffer) {
	// Check whether the image data is OK
	if (workRecord->height * workRecord->width * 2 != (int)workRecord->length) {
		setError("Image data length doesn't match image size");
		return;
	}
	
	int i = 0;
	for (int y = 0; y < (int)workRecord->height; y++) {
		for (int x = 0; x < (int)workRecord->width; x++, i+= 2) {
			set555Pixel(img, x, y, buffer[i] | (buffer[i+1] << 8));
		}
	}
}

void SgImage::loadIsometricImage(QImage *img, quint8 *buffer) {
	
	writeIsometricBase(img, buffer);
	writeTransparentImage(img, &buffer[workRecord->uncompressed_length],
		workRecord->length - workRecord->uncompressed_length);
}

void SgImage::loadSpriteImage(QImage *img, quint8 *buffer) {
	writeTransparentImage(img, buffer, workRecord->length);
}

void SgImage::loadAlphaMask(QImage *img, const quint8 *buffer) {
	int i = 0;
	int x = 0, y = 0, j;
	int width = img->width();
	int length = workRecord->alpha_length;
	
	while (i < length) {
		quint8 c = buffer[i++];
		if (c == 255) {
			/* The next byte is the number of pixels to skip */
			x += buffer[i++];
			while (x >= width) {
				y++; x -= width;
			}
		} else {
			/* `c' is the number of image data bytes */
			for (j = 0; j < c; j++, i++) {
				setAlphaPixel(img, x, y, buffer[i]);
				x++;
				if (x >= width) {
					y++; x = 0;
				}
			}
		}
	}
}

void SgImage::writeIsometricBase(QImage *img, const quint8 *buffer) {
	int i = 0, x, y;
	int width, height, height_offset;
	int size = workRecord->flags[3];
	int x_offset, y_offset;
	int tile_bytes, tile_height, tile_width;
	
	width = img->width();
	height = (width + 2) / 2; /* 58 -> 30, 118 -> 60, etc */
	height_offset = img->height() - height;
	y_offset = height_offset;
	
	if (size == 0) {
		/* Derive the tile size from the height (more regular than width) */
		/* Note that this causes a problem with 4x4 regular vs 3x3 large: */
		/* 4 * 30 = 120; 3 * 40 = 120 -- give precedence to regular */
		if (height % ISOMETRIC_TILE_HEIGHT == 0) {
			size = height / ISOMETRIC_TILE_HEIGHT;
		} else if (height % ISOMETRIC_LARGE_TILE_HEIGHT == 0) {
			size = height / ISOMETRIC_LARGE_TILE_HEIGHT;
		}
	}
	if (size == 0) {
		setError(QString("Unknown isometric tile size: height %0").arg(height));
		return;
	}
	
	/* Determine whether we should use the regular or large (emperor) tiles */
	if (ISOMETRIC_TILE_HEIGHT * size == height) {
		/* Regular tile */
		tile_bytes  = ISOMETRIC_TILE_BYTES;
		tile_height = ISOMETRIC_TILE_HEIGHT;
		tile_width  = ISOMETRIC_TILE_WIDTH;
	} else if (ISOMETRIC_LARGE_TILE_HEIGHT * size == height) {
		/* Large (emperor) tile */
		tile_bytes  = ISOMETRIC_LARGE_TILE_BYTES;
		tile_height = ISOMETRIC_LARGE_TILE_HEIGHT;
		tile_width  = ISOMETRIC_LARGE_TILE_WIDTH;
	} else {
		setError(QString("Unknown tile size: %0 (height %1, width %2, size %3)")
			.arg(2 * height / size).arg(height).arg(width).arg(size));
		return;
	}
	
	/* Check if buffer length is enough: (width + 2) * height / 2 * 2bpp */
	if ((width + 2) * height != (int)workRecord->uncompressed_length) {
		setError(QString(
			"Data length doesn't match footprint size: %0 vs %1 (%2) %3")
			.arg((width + 2) * height)
			.arg(workRecord->uncompressed_length)
			.arg(workRecord->length)
			.arg(workRecord->invert_offset));
		return;
	}
	
	i = 0;
	for (y = 0; y < (size + (size - 1)); y++) {
		x_offset = (y < size ? (size - y - 1) : (y - size + 1)) * tile_height;
		for (x = 0; x < (y < size ? y + 1 : 2 * size - y - 1); x++, i++) {
			writeIsometricTile(img, &buffer[i * tile_bytes],
				x_offset, y_offset, tile_width, tile_height);
			x_offset += tile_width + 2;
		}
		y_offset += tile_height / 2;
	}
	
}

void SgImage::writeIsometricTile(QImage *img, const quint8 *buffer,
		int offset_x, int offset_y, int tile_width, int tile_height) {
	int half_height = tile_height / 2;
	int x, y, i = 0;
	
	for (y = 0; y < half_height; y++) {
		int start = tile_height - 2 * (y + 1);
		int end = tile_width - start;
		for (x = start; x < end; x++, i += 2) {
			set555Pixel(img, offset_x + x, offset_y + y,
				(buffer[i+1] << 8) | buffer[i]);
		}
	}
	for (y = half_height; y < tile_height; y++) {
		int start = 2 * y - tile_height;
		int end = tile_width - start;
		for (x = start; x < end; x++, i += 2) {
			set555Pixel(img, offset_x + x, offset_y + y,
				(buffer[i+1] << 8) | buffer[i]);
		}
	}
}

void SgImage::writeTransparentImage(QImage *img, const quint8 *buffer, int length) {
	int i = 0;
	int x = 0, y = 0, j;
	int width = img->width();
	
	while (i < length) {
		quint8 c = buffer[i++];
		if (c == 255) {
			/* The next byte is the number of pixels to skip */
			x += buffer[i++];
			while (x >= width) {
				y++; x -= width;
			}
		} else {
			/* `c' is the number of image data bytes */
			for (j = 0; j < c; j++, i += 2) {
				set555Pixel(img, x, y, buffer[i] | (buffer[i+1] << 8));
				x++;
				if (x >= width) {
					y++; x = 0;
				}
			}
		}
	}
}

void SgImage::set555Pixel(QImage *img, int x, int y, quint16 color) {
	if (color == 0xf81f) {
		return;
	}
	
	quint32 rgb = 0xff000000;
	
	// Red: bits 11-15, should go to bits 17-24
	rgb |= ((color & 0x7c00) << 9) | ((color & 0x7000) << 4);
	
	// Green: bits 6-10, should go to bits 9-16
	rgb |= ((color & 0x3e0) << 6) | ((color & 0x300));
	
	// Blue: bits 1-5, should go to bits 1-8
	rgb |= ((color & 0x1f) << 3) | ((color & 0x1c) >> 2);
	
	img->setPixel(x, y, rgb);
}

void SgImage::setAlphaPixel(QImage *img, int x, int y, quint8 color) {
	/* Only the first five bits of the alpha channel are used */
	quint8 alpha = ((color & 0x1f) << 3) | ((color & 0x1c) >> 2);
	
	img->setPixel(x, y, (alpha << 24) | (img->pixel(x, y) & 0xffffff));
}
