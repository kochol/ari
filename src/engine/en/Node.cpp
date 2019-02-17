#include "Node.hpp"

namespace ari
{
	namespace en
	{
		void Node::AddChild(Node * _child, ComponentId::Enum _id)
		{
			if (!m_mChilds.Contains(_id))
				m_mChilds.Add(_id, Oryol::Array<Node*>());

			m_mChilds[_id].Add(_child);
		}

		void Node::RemoveChild(Node * _child, ComponentId::Enum _id)
		{
			auto& v = m_mChilds[_id];
			v.EraseSwap(v.FindIndexLinear(_child, 0, v.Size() - 1));
		}

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
