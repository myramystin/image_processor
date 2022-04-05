#include "abstract_image.h"
#include "image.h"
#include "exception.h"

AbstractImage* CreateImage(const std::string& input_filename) {
    if(input_filename.substr(input_filename.size() - 4, 4) == ".bmp") {
        return new BmpImage(input_filename);
    }
    throw image_file_exceptions::InvalidInputFilename();
}
