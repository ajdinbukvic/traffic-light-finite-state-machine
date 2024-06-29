#pragma once
#include <map>
enum class Stanje {
	MIROVANJE,
	CRVENO,
	CRVENO_ZUTO,
	ZELENO,
	ZUTO,
	ZUTO_BLINKAJUCE
};

static std::map<std::string, Stanje> stanjaString = {
	{"MIROVANJE", Stanje::MIROVANJE},
	{"CRVENO", Stanje::CRVENO},
	{"CRVENO_ZUTO", Stanje::CRVENO_ZUTO},
	{"ZELENO", Stanje::ZELENO},
	{"ZUTO", Stanje::ZUTO},
	{"ZUTO_BLINKAJUCE", Stanje::ZUTO_BLINKAJUCE}
};