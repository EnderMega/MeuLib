#pragma once

#pragma region Extra
#ifdef NCONSTEXPR
#define CONSTEXPR
#else
#define CONSTEXPR constexpr
#endif
#pragma endregion
