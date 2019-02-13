#pragma once

#include <Core/Containers/StaticArray.h>
#include <Core/Containers/Queue.h>
#include <Core/Assertion.h>

namespace ari
{
	namespace core
	{
		template<class T, int Size>
		class ObjectPool
		{
			public:

			// The array Pool
			Oryol::StaticArray<T, Size> Pool;

			int Size() const
			{
				return m_iSize;
			}

			//! Returns the next free index inside the Pool to use.
			int GetFreeIndex()
			{
				m_iSize++;
				o_assert(m_iSize <= Pool.Size());

				if (!m_qFreeSlots.Empty())
				{
					return m_qFreeSlots.Dequeue();
				}

				return m_iSize;
			}

			//! Add a free slot to the Pool
			void Remove(int _index)
			{
				m_iSize--;
				o_assert(m_iSize >= 0);
				m_qFreeSlots.Enqueue(_index);
			}

			protected:

				int						m_iSize = 0;
				Oryol::Queue<int>		m_qFreeSlots;
		};

	} // core
	
} // ari
