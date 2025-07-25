#include <Graphics/RenderStates.hpp>

#include <Graphics/View.hpp>
#include <Math/Transform3.hpp>


gfx::RenderStates::RenderStates():
	m_view(View()),
	m_transform(mth::Transform3::getIdentity()),
	m_texture(0),
	m_shader(nullptr) {}