//
//  CubeMap.hpp
//  20-RefractionMapping
//
//  Created by Ryosuke Nakajima on 2017/05/30.
//
//

#pragma once

#include "ofMain.h"

class CubeMap {
public:
    void setFromImages(int size, ofImage img_px, ofImage img_nx,
                       ofImage img_py, ofImage img_ny,
                       ofImage img_pz, ofImage img_nz);
    void bind();
    void unbind();
    
private:
    unsigned int textureObject;
    
};
