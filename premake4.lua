solution "opentp"
	configurations {"debug", "release"}

	language "C++"

	includedirs {"opentp/opentp/include"}

	links {
			"boost_system",
			"boost_filesystem",
			"boost_program_options",
			"png"
	}

	project "opentp"
		kind "StaticLib"

		files {"opentp/opentp/source/**.cpp"}

	project "opentp-tool"
		kind "ConsoleApp"

		files {"opentp/opentp-tool/source/**.cpp"}

		links {"libopentp"}
