#pragma once

#include "ComponentId.hpp"
#include "Core/Containers/Map.h"
#include "Core/Containers/Array.h"

namespace ari
{
	namespace en
	{
		class Node
		{			
		public:
			virtual ~Node() = default;

			void AddChild(Node* _child, ComponentId::Enum _id);

			void RemoveChild(Node* _child, ComponentId::Enum _id);

			bool HasChildWithId(ComponentId::Enum _id) const;

			const Oryol::Array<Node*>& GetChildren(ComponentId::Enum _id);

		private:

			Oryol::Map<ComponentId::Enum, Oryol::Array<Node*>>	m_mChilds;

		};
		
	} // en
	
} // ari
