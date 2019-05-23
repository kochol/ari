#pragma once

#include "ComponentId.hpp"
#include "Core/Containers/Map.h"
#include "Core/Containers/Array.h"
#include "ComponentHandle.hpp"

namespace ari
{
	namespace en
	{
		class Node
		{			
		public:
			virtual ~Node() = default;

			template<class T>
			void AddChild(ComponentHandle<T> _child);	

			template<class T>
			void RemoveChild(ComponentHandle<T> _child);

			bool HasChildWithId(ComponentId::Enum _id) const;

			const Oryol::Array<Node*>& GetChildren(ComponentId::Enum _id);

		private:

			Oryol::Map<ComponentId::Enum, Oryol::Array<Node*>>	m_mChilds;

		};
		
		template<class T>
		void Node::AddChild(ComponentHandle<T> _child)
		{
			if (!m_mChilds.Contains(_child.Id))
				m_mChilds.Add(_child.Id, Oryol::Array<Node*>());

			m_mChilds[_child.Id].Add(_child.Component);
		}

		template<class T>
		void Node::RemoveChild(ComponentHandle<T> _child)
		{
			auto& v = m_mChilds[_child.Id];
			v.EraseSwap(v.FindIndexLinear(_child.Component, 0, v.Size() - 1));
		}

	} // en
	
} // ari
