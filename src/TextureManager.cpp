#include <Graphics/TextureManager.hpp>

#include <Math/Vec2.hpp>

#include <glad/glad.h>
#include <string>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


std::vector<gfx::TextureId> gfx::TextureManager::m_textures;
std::vector<gfx::TextureManager::TextureData> gfx::TextureManager::m_textures_data;


void gfx::TextureManager::initialize() {}

void gfx::TextureManager::finalize()
{
	glDeleteTextures(m_textures.size(), m_textures.data());
}


bool gfx::TextureManager::bind(TextureId uid)
{
	if (uid == 0) {glBindTexture(GL_TEXTURE_2D, 0); return true;}

	for (unsigned int i = 0; i < m_textures.size(); i++)
		if (uid == m_textures[i])
		{
			glBindTexture(GL_TEXTURE_2D, uid);
			return true;
		}
	return false;
}


gfx::TextureId gfx::TextureManager::loadFromFile(std::string path)
{
	static constexpr int modes[] = {0, 0, 0, GL_RGB, GL_RGBA};
    TextureId uid;
    TextureData data;

	unsigned char *image_data = stbi_load(path.c_str(), &(data.width), &(data.height), &(data.channels), 0);
	const GLenum mode = modes[data.channels];
	
	std::cout << data.width << " " << data.height << " " << data.channels << std::endl;
    if (image_data == nullptr)
    	return 0;

	glGenTextures(1, &uid);
	glBindTexture(GL_TEXTURE_2D, uid);
	glTexImage2D(GL_TEXTURE_2D, 0, mode, data.width, data.height, 0, mode, GL_UNSIGNED_BYTE, image_data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(image_data);
	glBindTexture(GL_TEXTURE_2D, 0);

    m_textures.push_back(uid);
    m_textures_data.push_back(data);
	return uid;
}