#include "EditorSettings.hpp"
#include <JsonCast.h>
#include "sx/io.h"
#include "Core/Log.h"
#include "sx/lin-alloc.h"

namespace ari
{
	namespace sh
	{
		EditorSettings & EditorSettings::Get()
		{
			static EditorSettings settings;
			return settings;
		}

		void EditorSettings::Save()
		{
			json root;
			to_json(root, Get());

			sx_file_writer writer;
			if (sx_file_open_writer(&writer, "editor_settings.json"))
			{
				auto s = root.dump();
				sx_file_write(&writer, s.c_str(), (int)s.length());
				sx_file_close_writer(&writer);
			}
			else
				Oryol::Log::Error("Can't write to editor_settings.json file.");

		} // Save

		void EditorSettings::Load()
		{
			auto mem = sx_file_load_text(sx_alloc_malloc, "editor_settings.json");
			if (mem == nullptr)
				return;

			json root = json::parse((char*)mem->data);
			from_json(root, Get());

			sx_mem_destroy_block(mem);

		} // Load


	} // shiva

} // ari
