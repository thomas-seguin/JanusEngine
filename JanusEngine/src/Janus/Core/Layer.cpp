#include "jnpch.h"
#include "Layer.h"

namespace Janus {
	Layer::Layer(const std::string& debugname)
		: m_DebugName(debugname) {}

	Layer::~Layer() {}
}