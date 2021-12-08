// modified from https://github.com/vgteam/vg/blob/master/src/version.cpp

#include "version.hpp"

// Get the git version macro from the build system
#include "../include/seqwish_git_version.hpp"

#include <iostream>
#include <sstream>

// If the seqwish_GIT_VERSION deosn't exist at all, define a placeholder
// This lets us be somewhat robust to undeterminable versions
#ifndef SEQWISH_GIT_VERSION
#define SEQWISH_GIT_VERSION "not-from-git"
#endif

// Define a way to quote macro values.
// See https://stackoverflow.com/a/196093
//#define QUOTE(arg) #arg
// We need another level to get the macro's value and not its name.
//#define STR(macro) QUOTE(macro)

namespace seqwish {

	using namespace std;

// Define all the strings as the macros' values
	const string Version::VERSION = SEQWISH_GIT_VERSION;

// Keep the list of codenames.
// Add new codenames here
	const unordered_map<string, string> Version::codenames = {
			{"v0.1", "initial release"},
			{"v0.2", "parallel union find / transclosure"},
			{"v0.2.1", "unstable point release"},
			{"v0.4", "improving stability"},
			{"v0.4.1", "complete correction of range compression in union find"},
			{"v0.5", "repeat limitation"},
			{"0.6", "std::thread our way through things"},
			{"v0.6.1", "simplify paths in GFA"},
			{"v0.7", "memory safety and minor improvements"},
			{"v0.7.1", "seqwish 0.7.1 - Sicurezza"},
			{"v0.7.2", "seqwish 0.7.2 - Diffidenza"}
			// Add more codenames here
	};

	string Version::get_version() {
		return VERSION;
	}

	string Version::get_release() {
		auto dash = VERSION.find('-');
		if (dash == -1) {
			// Pure tag versions have no dash
			return VERSION;
		} else {
			// Otherwise it is tag-count-hash and the tag describes the release
			return VERSION.substr(0, dash);
		}
	}

	string Version::get_codename() {
		auto release = get_release();

		auto found = codenames.find(release);

		if (found == codenames.end()) {
			// No known codename for this release.
			// Return an empty string so we can just not show it.
			return "";
		} else {
			// We have a known codename!
			return found->second;
		}
	}

	string Version::get_short() {
		stringstream s;
		s << VERSION;

		auto codename = get_codename();
		if (!codename.empty()) {
			// Add the codename if we have one
			s << " \"" << codename << "\"";
		}

		return s.str();
	}

}
