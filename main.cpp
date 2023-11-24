#include <Windows.h>
#include <cstdint>
#include <cstddef>

namespace offset
{
	constexpr std::ptrdiff_t playerent = 0x10F4F4;

	constexpr std::ptrdiff_t health = 0xF8;

	constexpr std::ptrdiff_t arAmmo = 0x150;
	constexpr std::ptrdiff_t pistolAmmo = 0x13C;
	constexpr std::ptrdiff_t dualPistolAmmo = 0x15C;
	constexpr std::ptrdiff_t hasDualPistol = 0x10C;
	constexpr std::ptrdiff_t grenades = 0x158;
}

void infAmmo()
{

	// Addresses

	const auto client = reinterpret_cast<std::uintptr_t>(GetModuleHandle("ac_client.exe"));

	const auto playerent = *reinterpret_cast<std::uintptr_t*>(client + offset::playerent);

	const auto health = *reinterpret_cast<std::int32_t*>(playerent + offset::health);

	auto ar = reinterpret_cast<std::int32_t*>(playerent + offset::arAmmo);

	auto pistol = reinterpret_cast<std::int32_t*>(playerent + offset::pistolAmmo);
	auto dualPistol = reinterpret_cast<std::int32_t*>(playerent + offset::dualPistolAmmo);

	auto hasDualPistol = reinterpret_cast<std::int32_t*>(playerent + offset::hasDualPistol);

	auto grenades = reinterpret_cast<std::int32_t*>(playerent + offset::grenades);

	int value = 999;

	// Loop

	while (true)
	{
		if (health > 0)
		{
			*ar = value;
			*grenades = value;

			if(*hasDualPistol == 1)
				*dualPistol = value;
			else
				*pistol = value;
		}

		Sleep(1);
	}
}

// Dll Entry Point

int __stdcall DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(instance);
		const HANDLE thread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(infAmmo), instance, 0, nullptr);

		if (thread)
			CloseHandle(thread);
	}
	return 1;
}