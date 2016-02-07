#include "pokedex.hpp"
#include "pokemon.hpp"

namespace Pokedex
{
	bool add(pkm_s* pkm)
	{
		return true;
	}

	static s32 getFormDexOffsetXY(pkm_s* pkm)
	{
		s32 offset = 0;

		switch (pkm->speciesID)
		{
			case 460: offset += 2; // Abomasnow
			case 448: offset += 2; // Lucario
			case 445: offset += 2; // Garchomp
			case 381: offset += 2; // Latios
			case 380: offset += 2; // Latias
			case 359: offset += 2; // Absol
			case 354: offset += 2; // Banette
			case 310: offset += 2; // Manetric
			case 308: offset += 2; // Medicham
			case 306: offset += 2; // Aggron
			case 303: offset += 2; // Mawile
			case 257: offset += 2; // Blaziken
			case 248: offset += 2; // Tyranitar
			case 229: offset += 2; // Houndoom
			case 214: offset += 2; // Heracros
			case 212: offset += 2; // Scizor
			case 181: offset += 3; // Ampharos
			case 150: offset += 2; // Mewtwo
			case 142: offset += 2; // Aerodactyl
			case 130: offset += 2; // Gyarados
			case 127: offset += 2; // Pinsir
			case 115: offset += 2; // Kangaskhan
			case  94: offset += 2; // Gengar
			case  65: offset += 2; // Alakazam
			case   9: offset += 2; // Blastoise
			case   6: offset += 3; // Charizard
			case   3: offset += 2; // Venusaur
			case 716: offset += 2; // Xerneas
			case 681: offset += 4; // Aegislash
			case 711: offset += 4; // Gourgeist
			case 710: offset += 5; // Pumpkaboo
			case 671: offset += 6; // Florges
			case 670: offset += 5; // Floette
			case 669: offset += 20; // Flabébé
			case 666: offset += 2; // Vivillion
			case 645: offset += 2; // Landorus
			case 641: offset += 2; // Tornadus
			case 642: offset += 2; // Thundurus
			case 647: offset += 3; // Keldeo
			case 646: offset += 2; // Kyurem
			case 550: offset += 2; // Basculin
			case 555: offset += 2; // Darmanitan
			case 648: offset += 4; // Meloetta
			case 586: offset += 4; // Sawsbuck
			case 585: offset += 2; // Deerling
			case 421: offset += 4; // Cherrim
			case 351: offset += 3; // Castform
			case 413: offset += 3; // Wormadam
			case 412: offset += 2; // Burmy
			case 423: offset += 2; // Gastrodon
			case 422: offset += 6; // Shellos
			case 479: offset += 2; // Rotom
			case 487: offset += 2; // Giratina
			case 492: offset += 4; // Shaymin
			case 386: offset += 28; // Deoxys
			case 201: offset += 0; // Unown
			break; default: offset = -1;
		}

		return offset;
	}

	static s32 getFormDexOffsetORAS(pkm_s* pkm)
	{
		s32 offset = 0;

		switch (pkm->speciesID)
		{
			case 676: offset += 5; // Furfrou
			case 649: offset += 18; // Genesect
			case 493: offset += 2; // Arceus
			case 383: offset += 2; // Groudon
			case 382: offset += 2; // Kyogre
			case 719: offset += 2; // Diancie
			case 531: offset += 2; // Audino
			case 475: offset += 2; // Gallade
			case 428: offset += 2; // Lopunny
			case 384: offset += 2; // Rayquaza
			case 376: offset += 2; // Metagross
			case 373: offset += 2; // Salamence
			case 362: offset += 2; // Glalie
			case 334: offset += 2; // Altaria
			case 323: offset += 2; // Camerupt
			case 319: offset += 2; // Sharpedo
			case 302: offset += 2; // Sableye
			case 360: offset += 2; // Swampert
			case 254: offset += 2; // Sceptile
			case 208: offset += 2; // Steelix
			case  80: offset += 2; // Slowbro
			case  18: offset += 2; // Pidgeot
			case  15: offset += 2; // Beedrill
			case 720: offset += 6; // Hoopa
			case  25: offset += 2; // Pikachu
			// case  25: offset += 1; // Hoopa
			// case  25: offset += 5; // Cosplay Pikachu
			// case  25: offset += 1; // Unused (Cosplay Pikachu)
			// case  25: offset += 2; // Pikachu
			case 460: offset += 2; // Abomasnow
			case 448: offset += 2; // Lucario
			case 445: offset += 2; // Garchomp
			case 381: offset += 2; // Latios
			case 380: offset += 2; // Latias
			case 359: offset += 2; // Absol
			case 354: offset += 2; // Banette
			case 310: offset += 2; // Manetric
			case 308: offset += 2; // Medicham
			case 306: offset += 2; // Aggron
			case 303: offset += 2; // Mawile
			case 257: offset += 2; // Blaziken
			case 248: offset += 2; // Tyranitar
			case 229: offset += 2; // Houndoom
			case 214: offset += 2; // Heracros
			case 212: offset += 2; // Scizor
			case 181: offset += 3; // Ampharos
			case 150: offset += 2; // Mewtwo
			case 142: offset += 2; // Aerodactyl
			case 130: offset += 2; // Gyarados
			case 127: offset += 2; // Pinsir
			case 115: offset += 2; // Kangaskhan
			case  94: offset += 2; // Gengar
			case  65: offset += 2; // Alakazam
			case   9: offset += 2; // Blastoise
			case   6: offset += 3; // Charizard
			case   3: offset += 2; // Venusaur
			case 716: offset += 2; // Xerneas
			case 681: offset += 4; // Aegislash
			case 711: offset += 4; // Gourgeist
			case 710: offset += 5; // Pumpkaboo
			case 671: offset += 6; // Florges
			case 670: offset += 5; // Floette
			case 669: offset += 20; // Flabébé
			case 666: offset += 2; // Vivillion
			case 645: offset += 2; // Landorus
			case 641: offset += 2; // Tornadus
			case 642: offset += 2; // Thundurus
			case 647: offset += 3; // Keldeo
			case 646: offset += 2; // Kyurem
			case 550: offset += 2; // Basculin
			case 555: offset += 2; // Darmanitan
			case 648: offset += 4; // Meloetta
			case 586: offset += 4; // Sawsbuck
			case 585: offset += 2; // Deerling
			case 421: offset += 4; // Cherrim
			case 351: offset += 3; // Castform
			case 413: offset += 3; // Wormadam
			case 412: offset += 2; // Burmy
			case 423: offset += 2; // Gastrodon
			case 422: offset += 6; // Shellos
			case 479: offset += 2; // Rotom
			case 487: offset += 2; // Giratina
			case 492: offset += 4; // Shaymin
			case 386: offset += 28; // Deoxys
			case 201: offset += 0; // Unown
			break; default: offset = -1;
		}

		return offset;
	}

	static inline bool getOffsetBit(u8* buf, u32 off, u32 bit)
	{
		return (buf[off+(bit/8)] >> (bit%8)) & 0x1;
	}

	static inline void setOffsetBit(u8* buf, u32 off, u32 bit, bool v)
	{
		buf[off+(bit/8)] = (buf[off+(bit/8)] & ~(0x1 << (bit%8))) | (v << (bit%8));
	}

	void importToXY(savebuffer_t sav, pkm_s* pkm)
	{
		bool isShiny = Pokemon::isShiny(pkm);
		u8 formID = Pokemon::formID(pkm);

		// Formdex
		if (formID > 0)
		{
			s32 formdexOffset = getFormDexOffsetXY(pkm);

			if (formdexOffset >= 0)
			{
				formdexOffset += SaveConst::XY_offsetDex + (isShiny ? 0x380 : 0x368);

				if (isShiny)
				{
					setOffsetBit(sav, formdexOffset, formID, true);
				}
				else
				{
					setOffsetBit(sav, formdexOffset, formID, true);
				}

				// TODO: Displayed form flag
			}
		}

		// TODO: Owned flag/Encountered flag/Displayed flag
	}

	void importToORAS(savebuffer_t sav, pkm_s* pkm)
	{
		bool isShiny = Pokemon::isShiny(pkm);
		u8 formID = Pokemon::formID(pkm);

		// Formdex
		if (formID > 0)
		{
			s32 formdexOffset = getFormDexOffsetORAS(pkm);

			if (formdexOffset >= 0)
			{
				formdexOffset += SaveConst::XY_offsetDex + (isShiny ? 0x38E : 0x368);

				if (isShiny)
				{
					setOffsetBit(sav, formdexOffset, formID, true);
				}
				else
				{
					setOffsetBit(sav, formdexOffset, formID, true);
				}

				// TODO: Displayed form flag
			}
		}

		// TODO: Owned flag/Encountered flag/Displayed flag
	}
}