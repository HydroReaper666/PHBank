#pragma once
/**
 * @file save.hpp
 */
#ifndef SAVE_HPP
#define SAVE_HPP

#include <3ds/types.h>

#define BOX_ROW_PKM_COUNT 5
#define BOX_COL_PKM_COUNT 6
#define BOX_PKM_COUNT BOX_ROW_PKM_COUNT * BOX_COL_PKM_COUNT
#define PC_BOX_COUNT 31 // 0x1f
#define BANK_BOX_COUNT 100 // 0x64
#define PKM_COUNT 721

#define PKM_SIZE 0xe8 // 232
#define BOX_SIZE PKM_SIZE * BOX_PKM_COUNT
#define PC_SIZE BOX_SIZE * PC_BOX_COUNT
#define BANK_SIZE BOX_SIZE * BANK_BOX_COUNT
#define PCNAME_SIZE 0x22


#define PC_XY_OFFSET 0x22600
#define PC_ORAS_OFFSET 0x33000
#define PCNAME_XY_OFFSET 0x4400
#define PCNAME_ORAS_OFFSET 0x4400
#define TRAINERCARD_XY_OFFSET 0x14000
#define TRAINERCARD_ORAS_OFFSET 0x14000
#define POKEDEX_XY_OFFSET 0x15000
#define POKEDEX_ORAS_OFFSET 0x15000
#define POKEDEXLANG_XY_OFFSET POKEDEX_XY_OFFSET + 0x3c8
#define POKEDEXLANG_ORAS_OFFSET POKEDEX_ORAS_OFFSET + 0x400
#define ENCOUNTERCOUNT_ORAS_OFFSET POKEDEX_ORAS_OFFSET + 0x686
#define BANK_PKBK_OFFSET 0x100

#define SAVEDATA_XY_SIZE 0x65600 // 0x34ad0 (PC size)
#define SAVEDATA_ORAS_SIZE 0x76000 // 0x34ad0 (PC size)
#define BANKDATA_PKBK_SIZE 0xaa000 // 0xa9ec0 (Bank size)


#define EK6_SIZE PKM_SIZE
#define PK6_SIZE PKM_SIZE

#define PK_SPECIES_SIZE 20
#define PK_ITEM_SIZE 20


typedef u8 ek6_t;
typedef u8 pk6_t;

struct pkm_s
{
	ek6_t* ek6 = NULL; // Pointer to MainBuffer
	pk6_t* pk6 = NULL; // Pointer to OwnBuffer
	bool moved : 1;
	bool modified : 1;
	bool isShiny : 1;
	
	u16 speciesID;
	u8* species;
	u16 itemID;
	u8* item;
	// T O D O !!

	pkm_s() : moved {false}, modified {false} {}
};

struct box_s
{
	pkm_s slot[BOX_PKM_COUNT];
};

struct pc_s
{
	box_s box[PC_BOX_COUNT];
};

struct bk_s
{
	box_s box[BANK_BOX_COUNT];
};


struct PACKED dex_s
{
	bool owned : 1;
	bool ownedMale : 1;
	bool ownedFemale : 1;
	bool ownedShinyMale : 1;
	bool ownedShinyFemale : 1;
	bool encounteredMale : 1;
	bool encounteredFemale : 1;
	bool encounteredShinyMale : 1;
	bool encounteredShinyFemale : 1;
	bool langJapanese : 1;
	bool langEnglish : 1;
	bool langFrench : 1;
	bool langItalian : 1;
	bool langGerman : 1;
	bool langSpanish : 1;
	bool langKorean : 1;
	bool foreignXY : 1;
	u16 dexNavCount : 15;
};

struct pokedex_s
{
	dex_s dexes[0x60 * 8]; // [PKM_COUNT]
};


struct savedata_s
{
	pc_s pc;
	pokedex_s pokedex;
	u16 TID; // 0x0
	u16 SID; // 0x2
	u16 TSV;
	u8 OTGender; // 0x05
	u8 OTName[0x1a / 2]; // 0x48
	u8 GEORegion; // 0x26
	u8 GEOCountry; // 0x27
};

struct bankdata_s
{
	bk_s bk;
};


typedef u8 savebuffer_t[SAVEDATA_ORAS_SIZE];
typedef u8 bankbuffer_t[BANKDATA_PKBK_SIZE];


namespace Game
{
	enum gameVersion_e
	{
		None = 0x0,
		X = 1 << 0,
		Y = 1 << 1,
		XY = X | Y,
		OR = 1 << 2,
		AS = 1 << 3,
		ORAS = OR | AS,
	};

	inline bool is(gameVersion_e g1, gameVersion_e g2) { return (g1 & g2); }
};

typedef Game::gameVersion_e GameVersion;

typedef u32 saveConst_t;

namespace SaveConst
{
	const saveConst_t XY_size = 0x65600;
	const saveConst_t XY_offsetTrainerCard = 0x14000;
	const saveConst_t XY_offsetPCName = 0x4400;
	const saveConst_t XY_offsetPC = 0x22600;
	const saveConst_t ORAS_size = 0x76000;
	const saveConst_t ORAS_offsetTrainerCard = 0x14000;
	const saveConst_t ORAS_offsetPCName = 0x4400;
	const saveConst_t ORAS_offsetPC = 0x33000;

	const saveConst_t BANK_size = 0xaa000;
	const saveConst_t BANK_offsetBK = 0x100;
}

#endif // SAVE_HPP