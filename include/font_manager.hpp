#pragma once
/**
 * @file font_manager.hpp
 * @brief Font Manager
 */
#ifndef FONT_MANAGER_HPP
#define FONT_MANAGER_HPP

#include <sftd.h>

class FontManager
{
	public:
		FontManager(void);
		~FontManager(void);

		Result load(void);

	private:
		bool loadFonts(void);
};

#endif // FONT_MANAGER_HPP
