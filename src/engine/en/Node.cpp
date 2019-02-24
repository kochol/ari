#include "Node.hpp"

namespace ari
{
	namespace en
	{
		bool Node::HasChildWithId(ComponentId::Enum _id) const
		{
			return m_mChilds.Contains(_id);
		}

		const Oryol::Array<Node*>& Node::GetChildren(ComponentId::Enum _id)
		{
			return m_mChilds[_id];
		}

	} // en
	
} // ari
