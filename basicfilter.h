#pragma once
#include "additional.h"
#include <memory>
#include "image_processing/image_holder.h"

class BasicFilter {
public:

    virtual void Apply(ImageHolder* img) = 0;
    virtual ~BasicFilter() = default;
};