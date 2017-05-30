//
//  CubeMap.cpp
//  18-CubeEnvironmentMapping
//
//  Created by Ryosuke Nakajima on 2017/05/28.
//
//

#include "CubeMap.hpp"

void CubeMap::setFromImages(int size, ofImage img_px, ofImage img_nx, ofImage img_py, ofImage img_ny, ofImage img_pz, ofImage img_nz)
{
    glGenTextures(1, &textureObject);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureObject);
    
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_px.getPixels().getData());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_nx.getPixels().getData());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_py.getPixels().getData());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_ny.getPixels().getData());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_pz.getPixels().getData());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_nz.getPixels().getData());
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void CubeMap::bind()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureObject);
}

void CubeMap::unbind()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0 );
}
