#include "jnpch.h"
#include "Entity.h"

namespace Janus {
	Entity::Entity(entt::entity handle, Scene* Scene)
		: m_EntityHandle(handle), m_Scene(Scene) {

	}
}