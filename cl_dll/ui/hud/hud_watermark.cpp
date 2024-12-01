// OpenAG
#include "hud.h"
#include "cl_util.h"
#include "parsemsg.h"
#include "build_info.h"

int CHudWatermark::Init()
{
	m_iFlags = 0;

	hud_watermark = CVAR_CREATE("hud_watermark", "0", FCVAR_ARCHIVE);

	gHUD.AddHudElem(this);
	return 0;
}

int CHudWatermark::VidInit()
{
	m_iFlags |= HUD_ACTIVE;
	refresh_draw_until = true;

	return 1;
}

int CHudWatermark::Draw(float time)
{
	if (hud_watermark->value == 0.0f)
		return 0;

	if (refresh_draw_until || (draw_until > gHUD.m_flTime + 15.0f)) {
		refresh_draw_until = false;
		draw_until = gHUD.m_flTime + 15.0f;
	}

	if (gHUD.m_flTime >= draw_until) {
		m_iFlags &= ~HUD_ACTIVE;
		return 0;
	}

	int r, g, b;
	UnpackRGB(r, g, b, gHUD.m_iDefaultHUDColor);

	char str[256];
	sprintf(str, "^2Client^1-Mod^7: ^2built ^1%s^7, ^2commit ^1%s^7, ^2architecture ^1%s^7, ^2platform ^1%s\n",
		BuildInfo::GetDate(),
		BuildInfo::GetCommitHash(),
		BuildInfo::GetArchitecture(),
		BuildInfo::GetPlatform()
	);
	gHUD.DrawHudStringWithColorTags(ScreenWidth / 20, gHUD.m_scrinfo.iCharHeight, str, r, g, b);
	gHUD.DrawHudStringWithColorTags(ScreenWidth / 20, gHUD.m_scrinfo.iCharHeight * 2, "^1t.me/Elinsrc^2 / ^1github.com/Elinsrc", r, g, b);
	gHUD.DrawHudStringWithColorTags(ScreenWidth / 20, gHUD.m_scrinfo.iCharHeight * 3, "^1t.me/HalfLifeCollectiveChat", r, g, b);
	gHUD.DrawHudStringWithColorTags(ScreenWidth / 20, gHUD.m_scrinfo.iCharHeight * 4, BuildInfo::GetGitHubLink(), r, g, b);
	sprintf(str, "^2To disable this message, type in the console ^1hud_watermark 0");
	gHUD.DrawHudStringWithColorTags(ScreenWidth / 20, gHUD.m_scrinfo.iCharHeight * 6, str, r, g, b);

	return 0;
}
